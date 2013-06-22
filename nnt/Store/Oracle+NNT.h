
# ifndef __NNT_STORE_ORACLE_9C35EB00E9794A82B62C4EB94269D3D5_H_INCLUDED
# define __NNT_STORE_ORACLE_9C35EB00E9794A82B62C4EB94269D3D5_H_INCLUDED

# ifdef NNT_CXX

# include "./DBMSqlAbstract.h"

NNT_BEGIN_HEADER_CXX 
NNT_BEGIN_NS(store)

NNTDECL_PRIVATE_HEAD_CXX(Oracle);

class Oracle
: public DBMSqlAbstract
{
    NNTDECL_PRIVATE_CXX(Oracle);
    NNTDECL_NOCOPY(Oracle);
    
public:
    
    NNTDECL_DBMS_DRIVER;
    
    Oracle();
    virtual ~Oracle();
    
public:
    
    virtual bool connect(connection_info const&);
    virtual void close();
    
    virtual DBMSqlDatatable* exec(core::string const& sql);    
    virtual DBMSqlDatatable* exec(core::string const& sql, params_type const& params);
    
};

NNT_BEGIN_NS(test)

class Oracle
: public ut::Case
{
public:
    
    Oracle() : ut::Case("ORACLE") {}
    
    virtual bool prepare();
    virtual void collect();
    virtual bool run();
    
public:
    
    connection_info cntinfo;
    
protected:
    
    store::Oracle* _ora;
    
};

NNT_END_NS

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif