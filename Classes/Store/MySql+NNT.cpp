
# include "Core.h"
# include "MySql+NNT.h"
# include "../Cross/NetAddress.h"

NNT_BEGIN_HEADER_C
# include <mysql/mysql.h>
# include <mysql/errmsg.h>
NNT_END_HEADER_C

# ifdef NNT_MSVC
# pragma comment (lib, "libmysql.lib")
# endif

NNT_BEGIN_CXX 
NNT_BEGIN_NS(store)

NNTDECL_PRIVATE_BEGIN_CXX(MySql)

void init()
{
    hdl = mysql_init(NULL);
}

void dealloc()
{
    if (hdl)
        mysql_close(hdl);
}

MYSQL* hdl;

NNTDECL_PRIVATE_END_CXX

core::string MySql::identity = "mysql";

IDBMS* MySql::dbmsInstance()
{
    return new MySql;
}

MySql::MySql()
{
    NNTDECL_PRIVATE_CONSTRUCT(MySql);
}

MySql::~MySql()
{
    NNTDECL_PRIVATE_DESTROY();
}

bool MySql::connect(connection_info const& info)
{    
	cross::NetAddress addr(info.url);
    MYSQL* h = mysql_real_connect(d_ptr->hdl, 
                                  addr.address.c_str(),
                                  info.user.c_str(), 
                                  info.passwd.c_str(),
                                  info.database.c_str(),
                                  addr.port,
                                  NULL,
                                  0);
    if (h != d_ptr->hdl)
        return false;
    return true;
}

void MySql::close()
{
    if (d_ptr->hdl)
    {
        mysql_close(d_ptr->hdl);
        d_ptr->hdl = NULL;
    }
}

DBMSqlDatatable* MySql::exec(const core::string &sql)
{
    int sta = mysql_query(d_ptr->hdl, sql.c_str());
    if (sta)
        return NULL;
    MYSQL_RES* res = mysql_store_result(d_ptr->hdl);
    
    my_ulonglong const nrows = mysql_num_rows(res);
    my_ulonglong const ncols = mysql_num_fields(res);
    
    DBMSqlDatatable* dt = NULL;
    if (nrows && ncols)
    {
        dt = new MySqlDatatable(res);    
        dt->update();
    }
    else
    {    
        mysql_free_result(res);
    }
    
    return dt;
}

static enum_field_types mysql_buffer_type(variant_t const& var)
{
    enum_field_types type = MYSQL_TYPE_NULL;
    switch (var.vt)
    {
        default: break;
        case variant_t::VT_SIGNEDCHAR: case variant_t::VT_UNSIGNEDCHAR:
            type = MYSQL_TYPE_TINY; break;
        case variant_t::VT_SIGNEDSHORT: case variant_t::VT_UNSIGNEDSHORT:
            type = MYSQL_TYPE_SHORT; break;
        case variant_t::VT_SIGNEDINT: case variant_t::VT_UNSIGNEDINT:
            type = MYSQL_TYPE_LONG; break;
        case variant_t::VT_FLOAT:
            type = MYSQL_TYPE_FLOAT; break;
        case variant_t::VT_DOUBLE:
            type = MYSQL_TYPE_DOUBLE; break;
        case variant_t::VT_PCHAR:
            type = MYSQL_TYPE_STRING; break;
        case variant_t::VT_DATA:
            type = MYSQL_TYPE_BLOB; break;
    }
    return type;
}

DBMSqlDatatable* MySql::exec(const core::string &sql, params_type const &params)
{
    MYSQL_STMT* stmt = mysql_stmt_init(d_ptr->hdl);
    int sta = mysql_stmt_prepare(stmt, sql.c_str(), sql.length());
    if (sta)
    {
        trace_msg(mysql_error(d_ptr->hdl));
        mysql_stmt_close(stmt);
        return NULL;
    }
                
    // bind param.
    MYSQL_BIND* binds = (MYSQL_BIND*)calloc(sizeof(MYSQL_BIND), params.size());
    for (core::counter<params_type::const_iterator> each = params.begin();
         each != params.end(); 
         ++each)
    {        
        MYSQL_BIND& bind = binds[each.count];
        variant_t const& var = each->second;
        
        bind.buffer_type = mysql_buffer_type(var);
        bind.buffer = var.address();
        bind.buffer_length = var.size();
    }
    sta = mysql_stmt_bind_param(stmt, binds);
    if (sta)
    {
        free(binds);
        trace_msg(mysql_error(d_ptr->hdl));
        mysql_stmt_close(stmt);
        return NULL;
    }
    
    // exe.
    sta = mysql_stmt_execute(stmt);
    if (sta)
    {
        free(binds);
        trace_msg(mysql_error(d_ptr->hdl));
        mysql_stmt_close(stmt);
        return NULL;
    }
    
    MySqlDatatableSTMT* dt = new MySqlDatatableSTMT(stmt);
    dt->update();
    
    if (dt->rows().size() == 0)
        zero_drop(dt);
    
    free(binds);
    return dt;
}

MySqlDatatable::MySqlDatatable(void* res)
: _res(res)
{
    PASS;
}

MySqlDatatable::~MySqlDatatable()
{
    mysql_free_result((MYSQL_RES*)_res);
}

void MySqlDatatable::update()
{
    MYSQL_RES* res = (MYSQL_RES*)_res;
    
    // clear.
    this->clear();        
    
    // get all records.
    my_ulonglong const nrows = mysql_num_rows(res);
    my_ulonglong const ncols = mysql_num_fields(res);
    
    rows_type& rows = this->_rows;
    cols_type& cols = this->_cols;
    cols.resize((usize)ncols);
    rows.resize((usize)nrows);
    
    // add cols.
    for (uindex idx = 0; idx < ncols; ++idx)
    {
        MYSQL_FIELD* field = mysql_fetch_field(res);
        cols[idx] = new variant_t(field->name, core::copy, field->name_length);
    }
    
    // add rows.
    for (uindex idx = 0; idx < nrows; ++idx)
    {
        DBMSqlDatatable::row_type* row = new DBMSqlDatatable::row_type();
        row->resize((usize)ncols);
        
        MYSQL_ROW drow = mysql_fetch_row(res);            
        for (uindex jdx = 0; jdx < ncols; ++jdx)
        {
            (*row)[jdx] = new variant_t(drow[jdx], core::copy);
        }
        
        rows[idx] = row;
    }

}

MySqlDatatableSTMT::MySqlDatatableSTMT(void* stmt)
: _stmt(stmt)
{
    PASS;   
}

MySqlDatatableSTMT::~MySqlDatatableSTMT()
{
    mysql_stmt_close((MYSQL_STMT*)_stmt);
}

void MySqlDatatableSTMT::update()
{
    MYSQL_STMT* stmt = (MYSQL_STMT*)_stmt;
    
    // clear.
    this->clear();        
    
    // update.
    MYSQL_RES* res_meta = mysql_stmt_result_metadata(stmt);
    if (res_meta == NULL)
        return;
        
    // get all records.    
    usize const ncols = mysql_num_fields(res_meta);
    
    rows_type& rows = this->_rows;
    cols_type& cols = this->_cols;
    cols.resize(ncols);
    //rows.resize(nrows);
    
    for (uint idx = 0; idx < ncols; ++idx)
    {
        MYSQL_FIELD* field = mysql_fetch_field(res_meta);
        cols[idx] = new variant_t(field->name, core::copy, field->name_length);
    }
    
    MYSQL_BIND* bind_cols = (MYSQL_BIND*)calloc(sizeof(MYSQL_BIND), ncols);
    my_bool* is_nulls = (my_bool*)calloc(sizeof(bool), ncols);
    ulong* lengths = (ulong*)calloc(sizeof(ulong), ncols);
    for (uindex idx = 0; idx < ncols; ++idx)
    {
        MYSQL_BIND& bind = bind_cols[idx];
        bind.length = lengths + idx;
        bind.is_null = is_nulls + idx;
    }
    
    my_ulonglong nrows;
    
    if (mysql_stmt_bind_result(stmt, bind_cols))
        goto LBL_RETURN;
    
    if (mysql_stmt_store_result(stmt))
        goto LBL_RETURN;
    
    nrows = mysql_stmt_num_rows(stmt);
    rows.reserve((usize)nrows);
    
    // load all rows.
    while (MYSQL_NO_DATA != mysql_stmt_fetch(stmt))
    {
        row_type* row = new row_type;
        row->resize(ncols);
        
        for (uint idx = 0; idx < ncols; ++idx)
        {
            if (is_nulls[idx])
                (*row)[idx] = new variant_t();
            else 
            {
                ulong len = lengths[idx];
                void* data = malloc(len);

                MYSQL_BIND& bind = bind_cols[idx];
                bind.buffer = data;
                bind.buffer_length = len;
                mysql_stmt_fetch_column(stmt, &bind, idx, 0);
                
                (*row)[idx] = new variant_t((char const*)data, core::assign, len);
            }
        }
        
        rows.push_back(row);
    }
    
LBL_RETURN:
    ::free(is_nulls);
    ::free(lengths);
    ::free(bind_cols);
}

NNT_END_NS 
NNT_END_CXX
