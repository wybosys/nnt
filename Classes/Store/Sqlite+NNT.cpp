
# include "Core.h"
# include "Sqlite+NNT.h"

NNT_BEGIN_HEADER_C

# include "../../contrib/sqlite/sqlite3.h"

NNT_END_HEADER_C

NNT_BEGIN_CXX 
NNT_BEGIN_NS(store)

NNTDECL_PRIVATE_BEGIN_CXX(Sqlite)

void init()
{
    d_owner->readonly = true;
    d_owner->creatable = false;
    
    sqlite3_initialize();
    db = NULL;
    mtx = sqlite3_mutex_alloc(SQLITE_MUTEX_FAST);
}

void dealloc()
{    
    this->close();
    sqlite3_mutex_free(mtx);
    sqlite3_shutdown();
}

void close()
{
    if (db)
        sqlite3_close(db);
    db = NULL;
}

void lock()
{
    sqlite3_mutex_enter(mtx);
}

void unlock()
{
    sqlite3_mutex_leave(mtx);
}

sqlite3 *db;
sqlite3_mutex *mtx;

NNTDECL_PRIVATE_END_CXX

core::string Sqlite::identity = "sqlite";

IDBMS* Sqlite::dbmsInstance()
{
    return new Sqlite;
}

Sqlite::Sqlite()
{
    NNTDECL_PRIVATE_CONSTRUCT(Sqlite);
}

Sqlite::~Sqlite()
{
    NNTDECL_PRIVATE_DESTROY();
}

bool Sqlite::connect(connection_info const& info)
{
    d_ptr->lock();
    
    sqlite3* db = NULL;
    
    int flag = this->readonly ? SQLITE_OPEN_READONLY : (SQLITE_OPEN_READWRITE | (this->creatable ? SQLITE_OPEN_CREATE : 0));
    
    int sta = sqlite3_open_v2(info.url.c_str(),
                              &db,
                              flag,
                              NULL);
    if (sta != SQLITE_OK)
    {
        trace_msg(sqlite3_errmsg(db));
        d_ptr->unlock();
        return false;
    }
    
    d_ptr->close();
    d_ptr->db = db;
    
    d_ptr->unlock();
    return true;
}

void Sqlite::close()
{
    d_ptr->close();
}

static int sqlite_exec_simple(void* arg, int ncols, char** vals, char** cols)
{
    SLDatabase* dt = (SLDatabase*)arg;
    if (dt->cols().size() == 0)
        dt->update_cols(ncols, cols);
    dt->add_row(ncols, vals);
    return 0;
}

DBMSqlDatatable* Sqlite::exec(core::string const& sql)
{
    char* errmsg = NULL;
    SLDatabase* dt = new SLDatabase;
    
    int sta = sqlite3_exec(d_ptr->db,
                           sql.c_str(),
                           sqlite_exec_simple,
                           dt,
                           &errmsg);
    
    if (sta != SQLITE_OK)
    {
        zero_drop(dt);
        trace_msg(errmsg);
        sqlite3_free(errmsg);
        return NULL;
    }
    
    return dt;
}

DBMSqlDatatable* Sqlite::exec(core::string const& sql, params_type const& params)
{
    sqlite3_stmt* stmt = NULL;
    char const* tail = NULL;
    int sta = sqlite3_prepare(d_ptr->db,
                              sql.c_str(),
                              sql.length(),
                              &stmt,
                              &tail);
    if (SQLITE_OK != sta)
    {
        trace_msg(tail);
        return NULL;
    }
    
    // success.
    // bind params.
    for (core::counter<params_type::const_iterator> each = params.begin();
         each != params.end();
         ++each)
    {
        core::string const& name = each->first;
        variant_t const& var = each->second;
        int const pos = sqlite3_bind_parameter_index(stmt, name.c_str());
        if (pos == 0)
            continue;
        switch (var.vt)
        {
            default: break;
            case variant_t::VT_SIGNEDCHAR: case variant_t::VT_UNSIGNEDCHAR:
            case variant_t::VT_SIGNEDINT: case variant_t::VT_UNSIGNEDINT:
            case variant_t::VT_SIGNEDSHORT: case variant_t::VT_UNSIGNEDSHORT:
                sqlite3_bind_int(stmt, pos, (int)var); break;
            case variant_t::VT_SIGNEDLONG: case variant_t::VT_UNSIGNEDLONG:
                sqlite3_bind_int64(stmt, pos, (long)var); break;
            case variant_t::VT_FLOAT:
                sqlite3_bind_double(stmt, pos, (float)var); break;
            case variant_t::VT_DOUBLE:
                sqlite3_bind_double(stmt, pos, (double)var); break;
            case variant_t::VT_PCHAR: case variant_t::VT_DATA:
                sqlite3_bind_text(stmt, pos, (char const*)var.address(), var.size(), NULL); break;
        }
    }
    
    // exec.
    SLDatabaseSTMT* dt = NULL;
    sta = sqlite3_step(stmt);
    if (sta == SQLITE_ROW)
    {
        dt = new SLDatabaseSTMT(stmt);
        dt->update();
    }
    
    return dt;
}

void* Sqlite::origin() const
{
    return d_ptr->db;
}

void Sqlite::set_key(core::string const& key)
{
    sqlite3_key(d_ptr->db, key.c_str(), key.length());
}

SLDatabase::SLDatabase()
{
    PASS;
}

SLDatabase::~SLDatabase()
{
    PASS;
}

void SLDatabase::update_cols(uint _ncols, char **_cols)
{
    cols_type& cols = this->_cols;
    cols.resize(_ncols);
    
    for (uindex idx = 0; idx < _ncols; ++idx)
        cols[idx] = new variant_t(_cols[idx], core::copy);
}

void SLDatabase::add_row(uint ncells, char **cells)
{
    rows_type& rows = this->_rows;
    row_type* row = new row_type;
    row->resize(ncells);
    
    for (uindex idx = 0; idx < ncells; ++idx)
        (*row)[idx] = new variant_t(cells[idx], core::copy);
    
    rows.push_back(row);
}

SLDatabaseSTMT::SLDatabaseSTMT(void* stmt)
: _stmt(stmt)
{
    PASS;
}

SLDatabaseSTMT::~SLDatabaseSTMT()
{
    sqlite3_finalize((sqlite3_stmt*)_stmt);
}

void SLDatabaseSTMT::update()
{
    sqlite3_stmt* stmt = (sqlite3_stmt*)_stmt;
    
    // clear.
    this->clear();
    
    // add cols.
    uint const ncols = sqlite3_column_count(stmt);
    rows_type& rows = this->_rows;
    cols_type& cols = this->_cols;
    cols.resize(ncols);
    
    for (uint idx = 0; idx < ncols; ++idx)
    {
        char const* name = sqlite3_column_name(stmt, idx);
        cols[idx] = new variant_t(name, core::copy);
    }
    
    // add rows.
    int sta = 0;
    do
    {
        row_type* row = new row_type;
        row->resize(ncols);
        
        for (uindex idx = 0; idx < ncols; ++idx)
        {
            char const* val = (char const*)sqlite3_column_text(stmt, idx);
            (*row)[idx] = new variant_t(val, core::copy);
        }
        
        rows.push_back(row);
        
    } while (sta == SQLITE_ROW);
}

NNT_END_NS 
NNT_END_CXX