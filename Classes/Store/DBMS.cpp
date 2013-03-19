
# include "Core.h"
# include "DBMS.h"

# include "WSIBdb.h"
# include "WSISqlite.h"
# include "WSIMySql.h"
//# include "WSIOracle.h"
//# include "WSIPostgreSql.h"
# include "WSISqlServer.h"

WSI_BEGIN_CXX WSI_BEGIN_NS(store)

class map_drivers
{
public:
    map_drivers()
    {
        drivers[Bdb::identity] = Bdb::dbmsInstance;
        drivers[Sqlite::identity] = Sqlite::dbmsInstance;
        drivers[MySql::identity] = MySql::dbmsInstance;
        //drivers[Oracle::identity] = Oracle::dbmsInstance;
        //drivers[PostgreSql::identity] = PostgreSql::dbmsInstance;
        drivers[SqlServer::identity] = SqlServer::dbmsInstance;
    }
    
    typedef core::map<core::string, IDBMS* (*)()> drivers_type;
    drivers_type drivers;
};

IDBMS* instanceDatabaseByIdentity(core::string const& identity)
{
    static map_drivers drivers;
    
    map_drivers::drivers_type::const_iterator found = drivers.drivers.find(identity);
    if (found == drivers.drivers.end())
        return NULL;
    
    IDBMS* ret = found->second();
    
    return ret;
}

WSI_END_NS WSI_END_CXX
