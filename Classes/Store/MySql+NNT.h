
# ifndef __NNT_STORE_MYSQL_EEDC4DE034804536A8DF51B9D9FDBC71_H_INCLUDED
# define __NNT_STORE_MYSQL_EEDC4DE034804536A8DF51B9D9FDBC71_H_INCLUDED

# ifdef NNT_CXX

# include "DBMSqlAbstract.h"

NNT_BEGIN_HEADER_CXX 
NNT_BEGIN_NS(store)

NNTCLASS(MySql);

NNTDECL_PRIVATE_HEAD_CXX(MySql);

class MySql
: public DBMSqlAbstract
{
    NNTDECL_PRIVATE_CXX(MySql);
    NNTDECL_NOCOPY(MySql);
    
public:
    
    NNTDECL_DBMS_DRIVER;
    
    MySql();
    ~MySql();
    
public:
    
    virtual bool connect(connection_info const&);
    virtual void close();
    
    virtual DBMSqlDatatable* exec(core::string const& sql);    
    virtual DBMSqlDatatable* exec(core::string const& sql, params_type const& params);
    
};

class MySqlDatatable
: public DBMSqlDatatable
{
public:
    MySqlDatatable(void* res);
    ~MySqlDatatable();
    
public:
    virtual void update();
    
protected:
    void *_res;
};

class MySqlDatatableSTMT
: public DBMSqlDatatable
{
public:
    MySqlDatatableSTMT(void* stmt);
    ~MySqlDatatableSTMT();
    
public:
    virtual void update();
    
protected:
    void *_stmt;
};

NNT_END_NS 
NNT_END_HEADER_CXX

# endif

# endif