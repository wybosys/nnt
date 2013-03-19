
# ifndef __NNT_STORE_POSTGRESQL_BE680F3FC7A24546B6143954727126E7_H_INCLUDED
# define __NNT_STORE_POSTGRESQL_BE680F3FC7A24546B6143954727126E7_H_INCLUDED

# ifdef NNT_CXX

# include "./DBMSqlAbstract.h"

NNT_BEGIN_HEADER_CXX 
NNT_BEGIN_NS(store)

NNTDECL_PRIVATE_HEADER_CXX(PostgreSql)

class PostgreSql
: public DBMSqlAbstract
{
    NNTDECL_PRIVATE_CXX(PostgreSql);
    NNTDECL_NOCOPY(PostgreSql);
        
public:
    
    NNTDECL_DBMS_DRIVER;
    
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

NNT_END_NS 
NNT_END_HEADER_CXX

# endif

# endif