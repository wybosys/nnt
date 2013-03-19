
# include "Core.h"
# include "NNTPostgreSql.h"
# include "../Cross/NetAddress.h"

NNT_BEGIN_HEADER_C

# include <postgresql/libpq-fe.h>

NNT_END_HEADER_C

NNT_BEGIN_CXX 
NNT_BEGIN_NS(store)

NNTDECL_PRIVATE_BEGIN_CXX(PostgreSql)

void init()
{
    pg = NULL;
}

void dealloc()
{
    this->close();
}

void close()
{
    if (pg)
    {
        PQfinish(pg);
        pg = NULL;
    }
}

PGconn* pg;

NNTDECL_PRIVATE_END_CXX

core::string PostgreSql::identity = "postgresql";

IDBMS* PostgreSql::dbmsInstance()
{
    return new PostgreSql;
}

PostgreSql::PostgreSql()
{
    NNTDECL_PRIVATE_CONSTRUCT(PostgreSql);
}

PostgreSql::~PostgreSql()
{
    NNTDECL_PRIVATE_DESTROY();
}

bool PostgreSql::connect(const ::nnt::store::connection_info & info)
{
    this->close();
    
    const uint sz = 6;
    char const* keys[sz] = {0};
    char const* values[sz] = {0};
    uint idx = 0;
    
    cross::NetAddress addr(info.url);
    
    // 0
    if (addr.addr_type == cross::NetAddress::ADDRESS_NAME)
        keys[idx] = "host";
    else 
        keys[idx] = "hostaddr";
    values[idx++] = addr.address.c_str();
    
    // 1
    keys[idx] = "port";
    values[idx++] = addr.addport.c_str();
    
    // 2
    keys[idx] = "dbname";
    values[idx++] = info.database.c_str();
    
    // 3
    keys[idx] = "user";
    values[idx++] = info.user.c_str();
    
    // 4
    keys[idx] = "password";
    values[idx++] = info.passwd.c_str();
    
    PGconn* conn = PQconnectdbParams(keys, values, 0);
    if (CONNECTION_OK != PQstatus(conn))
    {
        PQfinish(conn);
        return false;
    }
    
    d_ptr->pg = conn;
    
    return true;
}

void PostgreSql::close()
{
    d_ptr->close();
}

DBMSqlDatatable* PostgreSql::exec(const core::string &sql)
{
    PGresult* res = PQexec(d_ptr->pg, sql.c_str());
    PgSqlDatatable* dt = NULL;
    
    switch (PQresultStatus(res))
    {
        default: break;
        case PGRES_COMMAND_OK: break;
        case PGRES_TUPLES_OK: 
        {
            dt = new PgSqlDatatable(res);      
            dt->update();
        } break;
    };
    
    if (dt == NULL)
        PQclear(res);
    
    return dt;
}

DBMSqlDatatable* PostgreSql::exec(const core::string &sql, const params_type &params)
{
    usize const sz_params = params.size();
    if (0 == sz_params)
        return this->exec(sql);
    
    params_type str_params = params;
    
    //Oid* pm_types = (Oid*)malloc(sz_params * sizeof(Oid));
    char const* *pm_vals = (char const* *)malloc(sz_params * sizeof(char const*));
    int* pm_lens = (int*)malloc(sz_params * sizeof(int));
    int* pm_fmts = (int*)malloc(sz_params * sizeof(int));
    
    for (core::counter<params_type::iterator> each = str_params.begin();
         each != str_params.end();
         ++each)
    {
        variant_t& var = each->second;
        var.stringize();
        
        pm_vals[each.count] = (char const*)var;
        pm_lens[each.count] = var.size();
        pm_fmts[each.count] = 0;
    }
    
    PGresult* res = PQexecParams(d_ptr->pg,
                                 sql.c_str(),
                                 sz_params,
                                 NULL,
                                 pm_vals,
                                 pm_lens,
                                 pm_fmts,
                                 0);
    
    //free(pm_types);
    free(pm_vals);
    free(pm_lens);
    free(pm_fmts);
    
    PgSqlDatatable* dt = NULL;
    switch (PQresultStatus(res))
    {
        default: 
            trace_msg(PQresultErrorMessage(res));
            break;
        case PGRES_COMMAND_OK: break;
        case PGRES_TUPLES_OK: 
        {
            dt = new PgSqlDatatable(res);      
            dt->update();
        } break;
    };
    
    if (dt == NULL)
        PQclear(res);
    else if (dt->rows().size() == 0)
        zero_drop(dt);
    
    return dt;
}

PgSqlDatatable::PgSqlDatatable(void* res)
: _res(res)
{
    PASS;
}

PgSqlDatatable::~PgSqlDatatable()
{
    PQclear((PGresult*)_res);
}

void PgSqlDatatable::update()
{
    PGresult* res = (PGresult*)_res;

    // clear.
    this->clear();
    
    // update.
    rows_type& rows = this->_rows;
    cols_type& cols = this->_cols;
    
    uint const ncols = PQnfields(res);
    uint const nrows = PQntuples(res);
    cols.resize(ncols);
    rows.resize(nrows);
    
    // add cols.
    for (uint idx = 0; idx < ncols; ++idx)
    {
        char const* colname = PQfname(res, idx);
        cols[idx] = new variant_t(colname, core::copy);
    }
    
    // add rows.
    for (uint idx = 0; idx < nrows; ++idx)
    {
        DBMSqlDatatable::row_type* row = new DBMSqlDatatable::row_type();
        row->resize(ncols);
        
        for (uint jdx = 0; jdx < ncols; ++jdx)
        {
            char const* val = PQgetvalue(res, idx, jdx);
            (*row)[jdx] = new variant_t(val, core::copy);
        }
        
        rows[idx] = row;
    }
}

NNT_END_NS 
NNT_END_CXX
