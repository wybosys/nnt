
# ifndef __WSI_STORE_POSTGRESQL_BE680F3FC7A24546B6143954727126E7_H_INCLUDED
# define __WSI_STORE_POSTGRESQL_BE680F3FC7A24546B6143954727126E7_H_INCLUDED

# ifdef WSI_CXX

# include "./DBMSqlAbstract.h"

WSI_BEGIN_HEADER_CXX 
WSI_BEGIN_NS(store)

WSIDECL_PRIVATE_HEADER_CXX(PostgreSql)

class PostgreSql
: public DBMSqlAbstract
{
    WSIDECL_PRIVATE_CXX(PostgreSql);
    WSIDECL_NOCOPY(PostgreSql);
        
public:
    
    WSIDECL_DBMS_DRIVER;
    
    PostgreSql();
    ~PostgreSql();
    
public:
    
    virtual bool connect(connection_info const&);
    virtual void close();
    
    virtual DBMSqlDatatable* exec(core::string const& sql);    
    virtual DBMSqlDatatable* exec(core::string const& sql, params_type const& params);
    
};

class PgSqlDatatable
: public DBMSqlDatatable
{
public:
    PgSqlDatatable(void* res);
    ~PgSqlDatatable();
    
public:
    virtual void update();
    
protected:
    void* _res;
};

WSI_END_NS 
WSI_END_HEADER_CXX

# endif

# endif