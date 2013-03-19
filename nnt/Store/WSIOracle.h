
# ifndef __WSI_STORE_ORACLE_9C35EB00E9794A82B62C4EB94269D3D5_H_INCLUDED
# define __WSI_STORE_ORACLE_9C35EB00E9794A82B62C4EB94269D3D5_H_INCLUDED

# ifdef WSI_CXX

# include "./DBMSqlAbstract.h"

WSI_BEGIN_HEADER_CXX 
WSI_BEGIN_NS(store)

WSIDECL_PRIVATE_HEADER_CXX(Oracle);

class Oracle
: public DBMSqlAbstract
{
    WSIDECL_PRIVATE_CXX(Oracle);
    WSIDECL_NOCOPY(Oracle);
    
public:
    
    WSIDECL_DBMS_DRIVER;
    
    Oracle();
    virtual ~Oracle();
    
public:
    
    virtual bool connect(connection_info const&);
    virtual void close();
    
    virtual DBMSqlDatatable* exec(core::string const& sql);    
    virtual DBMSqlDatatable* exec(core::string const& sql, params_type const& params);
    
};

WSI_BEGIN_NS(test)

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

WSI_END_NS

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif