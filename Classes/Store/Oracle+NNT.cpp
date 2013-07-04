
# include "Core.h"
# include "Oracle+NNT.h"

# include <oci/oci.h>

NNT_BEGIN_CXX 
NNT_BEGIN_NS(store)

NNTDECL_PRIVATE_BEGIN_CXX(Oracle)

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

NNTDECL_PRIVATE_END_CXX

core::string Oracle::identity = "oracle";

IDBMS* Oracle::dbmsInstance()
{
    return new Oracle;
}

Oracle::Oracle()
{
    NNTDECL_PRIVATE_CONSTRUCT(Oracle);
}

Oracle::~Oracle()
{
    NNTDECL_PRIVATE_DESTROY();
}

bool Oracle::connect(const ::nnt::store::connection_info &)
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

NNT_END_NS 
NNT_END_CXX
