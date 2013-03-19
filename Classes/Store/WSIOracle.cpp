
# include "Core.h"
# include "WSIOracle.h"

# include <oci/oci.h>

WSI_BEGIN_CXX 
WSI_BEGIN_NS(store)

WSIDECL_PRIVATE_BEGIN_CXX(Oracle)

void init()
{
    sword ret = OCIEnvCreate(&env, OCI_DEFAULT, NULL, 0, 0, 0, 0, NULL);   
    if (ret != OCI_SUCCESS && ret != OCI_SUCCESS_WITH_INFO)
        trace_msg("failed to create oci env.");
}

void dealloc()
{

}

OCIEnv* env;

WSIDECL_PRIVATE_END_CXX

core::string Oracle::identity = "oracle";

IDBMS* Oracle::dbmsInstance()
{
    return new Oracle;
}

Oracle::Oracle()
{
    WSIDECL_PRIVATE_CONSTRUCT(Oracle);
}

Oracle::~Oracle()
{
    WSIDECL_PRIVATE_DESTROY();
}

bool Oracle::connect(const wsi::store::connection_info &)
{
    return false;
}

void Oracle::close()
{
    
}

DBMSqlDatatable* Oracle::exec(const core::string &sql)
{
    return NULL;
}

DBMSqlDatatable* Oracle::exec(const core::string &sql, const params_type &params)
{
    return NULL;
}

WSI_BEGIN_NS(test)

bool Oracle::prepare()
{
    _ora = new store::Oracle;
    return true;
}

void Oracle::collect()
{
    safe_delete(_ora);
}

bool Oracle::run()
{
    return true;
}

WSI_END_NS

WSI_END_NS 
WSI_END_CXX
