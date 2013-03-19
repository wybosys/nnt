
# ifndef __WSI_STORE_MYSQL_EEDC4DE034804536A8DF51B9D9FDBC71_H_INCLUDED
# define __WSI_STORE_MYSQL_EEDC4DE034804536A8DF51B9D9FDBC71_H_INCLUDED

# ifdef WSI_CXX

# include "DBMSqlAbstract.h"

WSI_BEGIN_HEADER_CXX 
WSI_BEGIN_NS(store)

WSICLASS(MySql);

WSIDECL_PRIVATE_HEAD_CXX(MySql);

class MySql
: public DBMSqlAbstract
{
    WSIDECL_PRIVATE_CXX(MySql);
    WSIDECL_NOCOPY(MySql);
    
public:
    
    WSIDECL_DBMS_DRIVER;
    
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

WSI_END_NS 
WSI_END_HEADER_CXX

# endif

# endif