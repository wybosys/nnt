
# include "sqlite3.h"
# include "btreeInt.h"

extern int sqlite3CodecAttach(sqlite3* db, int ndb, void const* pkey, int lkey);
extern void sqlite3CodecGetKey(sqlite3* db, int ndb, void** ppkey, int* plkey);
extern void sqlite3_activate_see();

static int sqlite3_key_interop(sqlite3* db, void const* pkey, int lkey)
{
    return sqlite3CodecAttach(db, 0, pkey, lkey);
}

static int sqlite3_rekey_interop(sqlite3* db, void const* pkey, int lkey)
{
    Btree* pbt = db->aDb[0].pBt;
    Pager* p = sqlite3BtreePager(pbt);
    return SQLITE_OK;
}

int sqlite3CodecAttach(sqlite3* db, int ndb, void const* pkey, int lkey)
{
    return SQLITE_OK;
}

void sqlite3CodecGetKey(sqlite3* db, int ndb, void** ppkey, int* plkey)
{
    *ppkey = 0;
    *plkey = 0;
}

void sqlite3_activate_see()
{

}

int sqlite3_key(sqlite3* db, void const* pkey, int lkey)
{
    return sqlite3_key_interop(db, pkey, lkey);
}

int sqlite3_rekey(sqlite3* db, void const* pkey, int lkey)
{
    return sqlite3_rekey_interop(db, pkey, lkey);
}