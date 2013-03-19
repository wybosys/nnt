
# ifndef __WSI_STORE_SQLSERVER_98BA43078ABB4C30950B8730C3F5E9F8_H_INCLUDED
# define __WSI_STORE_SQLSERVER_98BA43078ABB4C30950B8730C3F5E9F8_H_INCLUDED

# ifdef WSI_CXX

# include "DBMSqlAbstract.h"

WSI_BEGIN_HEADER_CXX 
WSI_BEGIN_NS(store)

WSICLASS(SqlServer);
WSICLASS(MSSqlDatatable);

WSIDECL_PRIVATE_HEAD_CXX(SqlServer);

class SqlServer
: public DBMSqlAbstract
{
    WSIDECL_PRIVATE_CXX(SqlServer);
    WSIDECL_NOCOPY(SqlServer);
    
public:
    
    WSIDECL_DBMS_DRIVER;
    
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

WSI_BEGIN_NS(test)

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

WSI_END_NS

WSI_END_NS 
WSI_END_HEADER_CXX

WSI_BEGIN_HEADER_C

WSIAPI(::wsi::store::test::Mssql*) UTMssql();

WSI_END_HEADER_C

# endif

# endif