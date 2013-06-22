
# ifndef __NNT_STORE_SQLSERVER_98BA43078ABB4C30950B8730C3F5E9F8_H_INCLUDED
# define __NNT_STORE_SQLSERVER_98BA43078ABB4C30950B8730C3F5E9F8_H_INCLUDED

# ifdef NNT_CXX

# include "DBMSqlAbstract.h"

NNT_BEGIN_HEADER_CXX 
NNT_BEGIN_NS(store)

NNTCLASS(SqlServer);
NNTCLASS(MSSqlDatatable);

NNTDECL_PRIVATE_HEAD_CXX(SqlServer);

class SqlServer
: public DBMSqlAbstract
{
    NNTDECL_PRIVATE_CXX(SqlServer);
    NNTDECL_NOCOPY(SqlServer);
    
public:
    
    NNTDECL_DBMS_DRIVER;
    
    SqlServer();
    ~SqlServer();
    
public:
    
    virtual core::string urlize(connection_info const&) const;
    virtual bool connect(connection_info const&);
    virtual void close();
    
    virtual DBMSqlDatatable* exec(core::string const& sql);    
    virtual DBMSqlDatatable* exec(core::string const& sql, params_type const& params);
    
};

class MSSqlDatatable
: public DBMSqlDatatable
{
public:
    MSSqlDatatable(void* proc);
    ~MSSqlDatatable();

public:
    virtual void update();
    
protected:
    void* _proc;
};

NNT_BEGIN_NS(test)

class Mssql
	: public ut::Case
{
public:

	Mssql() : ut::Case("MS SQL Server") {}

	virtual bool prepare();
	virtual void collect();
	virtual bool run();

protected:

	store::SqlServer* _db;

};

NNT_END_NS

NNT_END_NS 
NNT_END_HEADER_CXX

NNT_BEGIN_HEADER_C

NNTAPI(::nnt::store::test::Mssql*) UTMssql();

NNT_END_HEADER_C

# endif

# endif