
# include "Core.h"
# include "sqlite3.h"
# include "sqlite3.c"
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

# if defined(NNT_MACH)

#   define sqlite_aes_t nsaes_t
#   define sqlite_aes_free nsaes_free
#   define sqlite_aes_new nsaes_new
#   define sqlite_aes_set_key nsaes_set_key
#   define sqlite_aes_encrypt nsaes_encrypt
#   define sqlite_aes_decrypt nsaes_decrypt
#   define sqlite_aes_swap_rw nsaes_swap_rw

# else

#   define sqlite_aes_t aes_t
#   define sqlite_aes_free aes_free
#   define sqlite_aes_new aes_new
#   define sqlite_aes_set_key aes_set_key
#   define sqlite_aes_encrypt aes_encrypt
#   define sqlite_aes_decrypt aes_decrypt
#   define sqlite_aes_swap_rw aes_swap_rw

# endif

typedef struct
{
    sqlite_aes_t* key;
    size_t pager_size;
    Pager* pager;
} sqlite3_crypto_t;

static void sqlite3_free_crypto(sqlite3_crypto_t* cpt)
{
    sqlite_aes_free(cpt->key);
    free(cpt);
}

static sqlite3_crypto_t* sqlite3_new_crypto(void const* skey, int lkey)
{
    sqlite3_crypto_t* cpt = (sqlite3_crypto_t*)calloc(1, sizeof(sqlite3_crypto_t));
    cpt->key = sqlite_aes_new();
    if (sqlite_aes_set_key(cpt->key, skey, lkey) != 0) {
        sqlite3_free_crypto(cpt);
        return NULL;
    }
    return cpt;
}

static int sqlite3_crypto_encrypt(sqlite3_crypto_t* cpt, void* indata, size_t inlen, void** outdata, size_t* outlen)
{
    return sqlite_aes_encrypt(cpt->key, indata, inlen, outdata, outlen);
}

static int sqlite3_crypto_decrypt(sqlite3_crypto_t* cpt,void* indata, size_t inlen, void** outdata, size_t* outlen)
{
    return sqlite_aes_decrypt(cpt->key, indata, inlen, outdata, outlen);
}

static int sqlite3_key_interop(sqlite3* db, void const* skey, int lkey)
{
    return sqlite3CodecAttach(db, 0, skey, lkey);
}

static int sqlite3_rekey_interop(sqlite3* db, void const* skey, int lkey)
{
    return SQLITE_ERROR;
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
            sqlite_aes_swap_rw(cpt->key);
            sqlite3_crypto_encrypt(cpt, data, cpt->pager_size, &buf, &lbuf);
            sqlite_aes_swap_rw(cpt->key);
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
    return sqlite3_key_interop(db, skey, lkey);
}

int sqlite3_rekey(sqlite3* db, void const* skey, int lkey)
{
    return sqlite3_rekey_interop(db, skey, lkey);
}
