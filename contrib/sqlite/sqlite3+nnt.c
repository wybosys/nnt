
# include "Core.h"
# include "sqlite3.h"
# include "sqlite3.c"
# include "sqlite3+nnt.h"
# include "../../Classes/Security/AES+NNT.h"

const char sqlite3_version[] = SQLITE_VERSION;

extern int sqlite3CodecAttach(sqlite3* db, int ndb, void const* skey, int lkey);
extern void sqlite3CodecGetKey(sqlite3* db, int ndb, void** pskey, int* plkey);
extern void sqlite3_activate_see();
extern void sqlite3PagerSetCodec(
                                 Pager *pPager,
                                 void *(*xCodec)(void*,void*,Pgno,int),
                                 void (*xCodecSizeChng)(void*,int,int),
                                 void (*xCodecFree)(void*),
                                 void *pCodec
                                 );
extern void* sqlite3PagerXCodec(void*, void*, Pgno, int);
extern void sqlite3PagerXCodecSizeChanged(void*, int, int);
extern void sqlite3PagerXCodecFree(void*);

typedef struct
{
    void* key;
    size_t pager_size;
    Pager* pager;
}
sqlite3_crypto_t;

typedef void* (*func_new_t)();
static func_new_t func_new;

typedef void (*func_free_t)(void*);
static func_free_t func_free;

typedef void (*func_set_padding_t)(void*, int);
static func_set_padding_t func_set_padding;

typedef void (*func_swap_rw_t)(void*);
static func_swap_rw_t func_swap_rw;

typedef int (*func_set_key_t)(void*, void const*, size_t);
static func_set_key_t func_set_key;

typedef int (*func_encrypt_t)(void*, void const*, size_t, void**, size_t*);
static func_encrypt_t func_encrypt;

typedef int (*func_decrypt_t)(void*, void const*, size_t, void**, size_t*);
static func_decrypt_t func_decrypt;

typedef void (*func_set_enkey_t)(void*, void const*);
static func_set_enkey_t func_set_enkey;

typedef void (*func_set_dekey_t)(void*, void const*);
static func_set_dekey_t func_set_dekey;

static void sqlite3_crypto_openssl()
{
    func_new = (func_new_t)&aes_new;
    func_free = (func_free_t)&aes_free;
    func_set_padding = (func_set_padding_t)&aes_set_padding;
    func_swap_rw = (func_swap_rw_t)&aes_swap_rw;
    func_set_key = (func_set_key_t)&aes_set_key;
    func_encrypt = (func_encrypt_t)&aes_encrypt;
    func_decrypt = (func_decrypt_t)&aes_decrypt;
    func_set_enkey = (func_set_enkey_t)&aes_set_enkey;
    func_set_dekey = (func_set_dekey_t)&aes_set_dekey;
}

static void sqlite3_crypto_ns()
{
# ifdef NNT_MACH
    
    func_new = (func_new_t)&nsaes_new;
    func_free = (func_free_t)&nsaes_free;
    func_set_padding = (func_set_padding_t)&nsaes_set_padding;
    func_swap_rw = (func_swap_rw_t)&nsaes_swap_rw;
    func_set_key = (func_set_key_t)&nsaes_set_key;
    func_encrypt = (func_encrypt_t)&nsaes_encrypt;
    func_decrypt = (func_decrypt_t)&nsaes_decrypt;
    func_set_enkey = (func_set_enkey_t)&nsaes_set_enkey;
    func_set_dekey = (func_set_dekey_t)&nsaes_set_dekey;
    
# endif
}

static void sqlite3_free_crypto(sqlite3_crypto_t* cpt)
{
    func_free(cpt->key);
    free(cpt);
}

static sqlite3_crypto_t* sqlite3_new_crypto(void const* skey, int lkey)
{
    sqlite3_crypto_t* cpt = (sqlite3_crypto_t*)calloc(1, sizeof(sqlite3_crypto_t));
    cpt->key = func_new();
    if (func_set_key(cpt->key, skey, lkey) != 0) {
        sqlite3_free_crypto(cpt);
        return NULL;
    }
    func_set_padding(cpt->key, false);
    return cpt;
}

static int sqlite3_crypto_encrypt(sqlite3_crypto_t* cpt, void* indata, size_t inlen, void** outdata, size_t* outlen)
{
    return func_encrypt(cpt->key, indata, inlen, outdata, outlen);
}

static int sqlite3_crypto_decrypt(sqlite3_crypto_t* cpt,void* indata, size_t inlen, void** outdata, size_t* outlen)
{
    return func_decrypt(cpt->key, indata, inlen, outdata, outlen);
}

static int sqlite3_key_interop(sqlite3* db, void const* skey, int lkey)
{
    return sqlite3CodecAttach(db, 0, skey, lkey);
}

static int sqlite3_rekey_interop(sqlite3* db, void const* skey, int lkey)
{
    Btree* pbt = db->aDb[0].pBt;
	Pager *p = sqlite3BtreePager(pbt);
    
    sqlite3_crypto_t* oldcrypt = sqlite3PagerGetCodec(p);
    sqlite3_crypto_t* newcrypt = sqlite3_new_crypto(skey, lkey);
    
    func_set_dekey(newcrypt->key, TRIEXP(oldcrypt, oldcrypt->key, NULL));
    
	int rc = sqlite3BtreeBeginTrans(pbt, 1);
    
	if (rc == SQLITE_OK)
	{
        newcrypt->pager = p;
        sqlite3PagerSetCodec(p,
                             sqlite3PagerXCodec, sqlite3PagerXCodecSizeChanged, sqlite3PagerXCodecFree,
                             newcrypt);
        
		// Rewrite all the pages in the database using the new encryption key
		Pgno nPage;
		Pgno nSkip = PAGER_MJ_PGNO(p);
        
		sqlite3PagerPagecount(p, (int*)&nPage);
        
		for(Pgno n = 1;
            rc == SQLITE_OK && n <= nPage;
            ++n)
		{
			if (n == nSkip)
                continue;
            
            DbPage* pPage = NULL;
            sqlite3PagerGet(p, n, &pPage);

            if (pPage == NULL)
                continue;
            
            rc = sqlite3PagerWrite(pPage);
            sqlite3PagerUnref(pPage);
		}
	}
    
    if (rc != SQLITE_OK)
    {
        // failed, rooback
        sqlite3BtreeRollback(pbt, SQLITE_OK);
        sqlite3_free_crypto(newcrypt);
    }
    else
    {
        rc = sqlite3BtreeCommit(pbt);
    }

	return rc;
}

void* sqlite3PagerXCodec(void* codec, void* data, Pgno pno, int nmode)
{
    sqlite3_crypto_t* cpt = (sqlite3_crypto_t*)codec;
    if (cpt == NULL)
        return data;
    
    void* buf = NULL;
    size_t lbuf;
    
    switch (nmode)
    {
        default: break;
        case 0: // undo a "case 7" journal file encryption
        case 2: // reload a page
        case 3: // load page
        {
            if (sqlite3_crypto_decrypt(cpt, data, cpt->pager_size, &buf, &lbuf) == 0)
                memcpy(data, buf, cpt->pager_size);
        } break;
        case 6: // encrypt a page for the main database file
        {
            sqlite3_crypto_encrypt(cpt, data, cpt->pager_size, &buf, &lbuf);
        } break;
        case 7: // encrypt a page for the journal file
        {
            func_swap_rw(cpt->key);
            sqlite3_crypto_encrypt(cpt, data, cpt->pager_size, &buf, &lbuf);
            func_swap_rw(cpt->key);
        } break;
    }
    
    return buf == NULL ? data : buf;
}

void sqlite3PagerXCodecSizeChanged(void* codec, int size, int reverse)
{
    sqlite3_crypto_t* cpt = (sqlite3_crypto_t*)codec;
    cpt->pager_size = size;
}

void sqlite3PagerXCodecFree(void* codec)
{
    sqlite3_crypto_t* cpt = (sqlite3_crypto_t*)codec;
    sqlite3_free_crypto(cpt);
}

int sqlite3CodecAttach(sqlite3* db, int ndb, void const* skey, int lkey)
{
    if (!skey || !lkey)
        return SQLITE_OK;

    sqlite3_crypto_t* cpt = NULL;

    if (db->aDb == NULL)
        return SQLITE_ERROR;

    // create key.
    cpt = sqlite3_new_crypto(skey, lkey);
    if (cpt == NULL)
        return SQLITE_ERROR;
    
    Btree* bt = db->aDb[ndb].pBt;
    Pager* pg = sqlite3BtreePager(bt);
    
    cpt->pager = pg;
    sqlite3PagerSetCodec(pg,
                         sqlite3PagerXCodec, sqlite3PagerXCodecSizeChanged, sqlite3PagerXCodecFree,
                         cpt);

    return SQLITE_OK;
}

void sqlite3CodecGetKey(sqlite3* db, int ndb, void** pskey, int* plkey)
{
    *pskey = 0;
    *plkey = 0;
}

void sqlite3_activate_see()
{

}

int sqlite3_key(sqlite3* db, void const* skey, int lkey)
{
    sqlite3_crypto_openssl();
    return sqlite3_key_interop(db, skey, lkey);
}

int sqlite3_rekey(sqlite3* db, void const* skey, int lkey)
{
    sqlite3_crypto_openssl();
    return sqlite3_rekey_interop(db, skey, lkey);
}

# ifdef NNT_MACH

int sqlite3_ns_key(sqlite3* db, void const* skey, int lkey)
{
    sqlite3_crypto_ns();
    return sqlite3_key_interop(db, skey, lkey);
}

int sqlite3_ns_rekey(sqlite3* db, void const* skey, int lkey)
{
    sqlite3_crypto_ns();
    return sqlite3_rekey_interop(db, skey, lkey);
}

# endif
