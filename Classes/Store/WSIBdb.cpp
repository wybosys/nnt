
# include "Core.h"
# include "WSIBdb.h"

WSI_BEGIN_HEADER_C

# ifdef DB_UNKNOWN
#   undef DB_UNKNOWN
# endif

# include <bdb/db.h>

WSI_END_HEADER_C

WSI_BEGIN_CXX 
WSI_BEGIN_NS(store)

WSIDECL_PRIVATE_BEGIN_CXX(Bdb)

//! db handle.
DB* db;

//! db path.
core::string dbpath;

void init()
{
    this->db = NULL;
    d_owner->readonly = false;
    d_owner->dup = false;

# ifdef WSI_DEBUG

	if (DB_VERSION_MAJOR < 5)
		trace_msg("bdb is too older.");

# endif

}

void dealloc()
{
    this->close();
}

void sync()
{
    db->sync(db, 0);
}

void close()
{
    if (db) {
        this->sync();
        db->close(db, 0);
        db = NULL;
    }
}

bool delete_db()
{
    if (db == NULL)
        return false;
    
    // close db.
    close();
    
    // remove.
    DB* agent = NULL;
    if (db_create(&agent, NULL, 0) != 0)
    {
        trace_msg("failed to create agent bdb.");
        return false;
    }
    
    if (agent->remove(agent, dbpath.c_str(), NULL, 0) != 0)
    {
        trace_msg("failed to delete db.");
        return false;
    }
    
    // had free while remove.
    //agent->close(agent, DB_NOSYNC);

    return true;
}

bool open(char const* url)
{
    // create db
    if (db) {
        this->close();
    }    
    
    if (db_create(&db, NULL, 0) != 0) 
    {
        trace_msg("failed to create bdb.");
        return false;
    }
    
    int ret = 0;
    
    if (d_owner->dup)
    {
        ret = db->set_flags(db, DB_DUP);
        
        if (ret != 0)
        {
            this->close();
            return false;
        }
    }

    // open db
    ret = db->open(db,
                   NULL,
                   url,
                   NULL,
                   DB_BTREE,
                   (d_owner->readonly ? DB_RDONLY : DB_CREATE),
                   0);
    
    if (ret != 0) 
    {      
        this->close();
        return false;
    }
    
    dbpath = url;
    
    return true;   
}

WSIDECL_PRIVATE_END_CXX

core::string Bdb::identity = "bdb";

IDBMS* Bdb::dbmsInstance()
{
    return new Bdb;
}

Bdb::Bdb()
{
    WSIDECL_PRIVATE_CONSTRUCT(Bdb);
}

Bdb::~Bdb()
{
    WSIDECL_PRIVATE_DESTROY();
}

bool Bdb::connect(connection_info const& info)
{
    return d_ptr->open(info.url.c_str());
}

bool Bdb::put(core::data const& data, core::data const& key)
{
    return this->put((void*)data.bytes(), data.length(), (void*)key.bytes(), key.length());
}

bool Bdb::put(void* data, uint dlen, void* key, uint klen)
{
    DBT dbkey, dbval;
    memset(&dbkey, 0, sizeof(DBT));
    memset(&dbval, 0, sizeof(DBT));
    dbkey.data = key;
    dbkey.size = klen;
    dbval.data = data;
    dbval.size = dlen;
    if (dup)
    {
        DBC *cursor = NULL;
        DBT tmpval;
        memset(&tmpval, 0, sizeof(DBT));
        int ret = d_ptr->db->cursor(d_ptr->db, NULL, &cursor, 0);
        if (ret)
            return false;
        ret = cursor->get(cursor, &dbkey, &tmpval, DB_SET);
        if (ret)
        {
            ret = d_ptr->db->put(d_ptr->db, NULL, &dbkey, &dbval, DB_OVERWRITE_DUP);
        }
        else 
        {
            ret = cursor->put(cursor, &dbkey, &dbval, DB_AFTER);
        }
        cursor->close(cursor);
        return ret == 0;
    }
    int ret = d_ptr->db->put(d_ptr->db, NULL, &dbkey, &dbval, DB_OVERWRITE_DUP);
    return ret == 0;
}

bool Bdb::over(core::data const& data, core::data const& key)
{
    return this->over((void*)data.bytes(), data.length(), (void*)key.bytes(), key.length());
}

bool Bdb::over(void* data, uint dlen, void* key, uint klen)
{
    DBT dbkey, dbval;
    memset(&dbkey, 0, sizeof(DBT));
    memset(&dbval, 0, sizeof(DBT));
    dbkey.data = key;
    dbkey.size = klen;
    dbval.data = data;
    dbval.size = dlen;
    
    DBT tmpval;
    memset(&tmpval, 0, sizeof(DBT));
    
    DBC* cursor = NULL;
    if (d_ptr->db->cursor(d_ptr->db, NULL, &cursor, 0))
        return false;
    if (cursor->get(cursor, &dbkey, &tmpval, DB_SET))
    {
        int ret = d_ptr->db->put(d_ptr->db, NULL, &dbkey, &dbval, DB_OVERWRITE_DUP);
        cursor->close(cursor);
        return ret == 0;
    }

    int ret = cursor->put(cursor, &dbkey, &dbval, DB_CURRENT);
    return ret == 0;
}

bool Bdb::del(const core::data &key)
{
    return this->del((void*)key.bytes(), key.length());
}

bool Bdb::del(void *key, uint klen)
{
    DBT dbkey, dbval;
    memset(&dbkey, 0, sizeof(DBT));
    memset(&dbval, 0, sizeof(DBT));
    dbkey.data = key;
    dbkey.size = klen;
    dbval.flags = DB_DBT_MALLOC;
    int ret;
    // for each data
    DBC *cursor = NULL;
    ret = d_ptr->db->cursor(d_ptr->db, NULL, &cursor, 0);
    if (ret)
    {
        return false;
    }
    ret = cursor->get(cursor, &dbkey, &dbval, DB_SET);
    if (ret == DB_NOTFOUND)
    {
        return false;
    }
    cursor->del(cursor, 0);
    cursor->close(cursor);
    return true;
}

bool Bdb::get(core::data const& key, core::data& data)
{
    void* rda = NULL;
    uint rsz = 0;
    if (!this->get((void*)key.bytes(), key.length(), &rda, &rsz))
        return false;
    
    data = core::data((byte*)rda, rsz);
    data.set_release(true);

    return true;
}

bool Bdb::get(void* key, uint klen, void** data, uint* pdlen)
{
    DBT dbkey, dbval;
    memset(&dbkey, 0, sizeof(DBT));
    memset(&dbval, 0, sizeof(DBT));
    dbkey.data = key;
    dbkey.size = klen;
    dbval.flags = DB_DBT_MALLOC;
    int ret;
    // for each data
    DBC *cursor = NULL;
    ret = d_ptr->db->cursor(d_ptr->db, NULL, &cursor, 0);
    if (ret)
    {
        return false;
    }
    ret = cursor->get(cursor, &dbkey, &dbval, DB_SET);
    if (ret == DB_NOTFOUND)
    {
        return false;
    }
    *data = dbval.data;
    *pdlen = dbval.size;
    cursor->close(cursor);
    return true;
}

void Bdb::walk(DBMSNoSqlWalkFunc func)
{
    DBC *cursor;
    DBT key, data;
    memset(&key, 0, sizeof(DBT));
    memset(&data, 0, sizeof(DBT));
    d_ptr->db->cursor(d_ptr->db, NULL, &cursor, 0);
    while (0 == (cursor->get(cursor, &key, &data, DB_NEXT)))
    {
        if (false == (*func)(key.data, key.size, data.data, data.size))
        {
            break;
        }
    }
    cursor->close(cursor);
}

static bool delete_cursor(void* k, void* d, void* c)
{
    DBC* cursor = (DBC*)c;
    if (cursor->del(cursor, 0) != 0)
    {
        trace_msg("failed to remove bdb cursor.");
    }
    return true;
}

void Bdb::clear()
{
    _walk(delete_cursor);
    sync();
}

void Bdb::_walk(BDBWalkFunc func)
{
    DBC *cursor;
    DBT key, data;
    memset(&key, 0, sizeof(DBT));
    memset(&data, 0, sizeof(DBT));
    d_ptr->db->cursor(d_ptr->db, NULL, &cursor, 0);
    while (0 == (cursor->get(cursor, &key, &data, DB_NEXT)))
    {
        if (false == (*func)(&key, &data, cursor))
        {
            break;
        }
    }
    cursor->close(cursor);
}

typedef struct {
    DBC *cursor;
    DBT key, data;
} WSIBdbIterator;

void* Bdb::iterator_begin()
{
    WSIBdbIterator *iter = (WSIBdbIterator*)malloc(sizeof(WSIBdbIterator));
    memset(iter, 0, sizeof(WSIBdbIterator));
    if (d_ptr->db->cursor(d_ptr->db, NULL, &iter->cursor, 0))
    {
        free(iter);
        return 0;
    }
    void* ret = this->iterator_next(iter);
    if (ret == nil)
    {
        free(iter);
        return 0;
    }
    return ret;
}

void* Bdb::range_begin(void* key, uint klen)
{
    WSIBdbIterator *iter = (WSIBdbIterator*)malloc(sizeof(WSIBdbIterator));
    memset(iter, 0, sizeof(WSIBdbIterator));
    
    iter->key.data = key;
    iter->key.size = klen;
    
    if (d_ptr->db->cursor(d_ptr->db, NULL, &iter->cursor, 0)) 
    {
        free(iter);
        return 0;
    }
    
    if (iter->cursor->get(iter->cursor, &iter->key, &iter->data, DB_SET))
    {
        free(iter);
        return 0;
    }
    return iter;
}

void* Bdb::iterator_next(void* _iter)
{
    WSIBdbIterator *iter = (WSIBdbIterator*)_iter;
    if (0 == (iter->cursor->get(iter->cursor, &iter->key, &iter->data, DB_NEXT))) {
        return iter;
    }
    return 0;
}

void* Bdb::range_next(void* _iter)
{
    WSIBdbIterator *iter = (WSIBdbIterator*)_iter;
    if (0 == (iter->cursor->get(iter->cursor, &iter->key, &iter->data, DB_NEXT_DUP))) {
        return iter;
    }
    return 0;  
}

void Bdb::iterator_end(void* iter)
{
    free(iter);
}

void Bdb::iterator_retrive(void* _iter, void** key, uint* klen, void** data, uint* dlen)
{
    WSIBdbIterator* iter = (WSIBdbIterator*)_iter;
    if (key && klen)
    {
        *key = iter->key.data;
        *klen = iter->key.size;
    }
    
    if (data && dlen)
    {
        *data = iter->data.data;
        *dlen = iter->data.size;
    }
}

void Bdb::sync()
{
    d_ptr->sync();
}

void Bdb::close()
{
    d_ptr->close();
}

bool Bdb::delete_db()
{
    return d_ptr->delete_db();
}

WSI_BEGIN_NS(test)

bool Bdb::prepare()
{
    _db = new store::Bdb;
    connection_info cn;
    cn.url = "~ut-bdb.db";
    if (_db->connect(cn))
        return true;
    safe_delete(_db);
    return false;
}

void Bdb::collect()
{
    _db->delete_db();
    safe_delete(_db);
}

bool Bdb::run()
{
    assert(_db->put(core::type_cast<core::data>("ABC"), core::type_cast<core::data>("ABC")));
    step();
    
    core::data val;
    _db->get(core::type_cast<core::data>("ABC"), val);
    assert(val == core::type_cast<core::data>("ABC"));
    step();
    
    return true;
}

WSI_END_NS

WSI_END_NS 
WSI_END_CXX

WSI_BEGIN_C

::wsi::store::test::Bdb* UTBdb()
{
    return new ::wsi::store::test::Bdb;
}

WSI_END_C
