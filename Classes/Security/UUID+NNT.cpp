
# include "Core.h"
# include "UUID+NNT.h"

# if defined(NNT_MACH) || defined(NNT_UNIX)
#   define USE_OSSP
# endif

# ifdef USE_OSSP
#   include <ossp/uuid.h>
# endif

# ifdef NNT_MSVC
#   include <Rpc.h>
# endif

NNT_BEGIN_CXX

uuid::uuid()
: _u(0)
{
# ifdef NNT_MSVC
    
	UUID* uid = (UUID*)malloc(sizeof(UUID));
	::UuidCreate(uid);
	_u = uid;
    
# endif
    
# ifdef USE_OSSP
    
    uuid_create((uuid_t**)&_u);
    uuid_make((uuid_t*)_u, UUID_MAKE_V1);
    
# endif
    
}

uuid::~uuid()
{
# ifdef NNT_MSVC
    
	::free(_u);
    
# endif
    
# ifdef USE_OSSP
    
    uuid_destroy((uuid_t*)_u);
    
# endif    
    
}

uuid& uuid::operator = (const ::nnt::uuid & r)
{
# ifdef NNT_MSVC
    
	*(UUID*)_u = *(UUID*)r._u;
    
# endif
    
# ifdef USE_OSSP
    
    if (_u)
        uuid_destroy((uuid_t*)_u);
    uuid_clone((uuid_t const*)r._u, (uuid_t**)&_u);
    
# endif
    
    return *this;
}

core::string uuid::to_string() const
{    
# ifdef NNT_MSVC
    
    char buf[36];
	::UuidToStringA((UUID const*)_u, (RPC_CSTR*)buf);
    return core::string(buf, 36);
    
# endif
    
# ifdef USE_OSSP
    
    usize sz = 0;
    char* buf = NULL;
    uuid_export((uuid_t const*)_u, UUID_FMT_STR, &buf, (size_t*)&sz);
    core::string str(buf, sz - 1);
    free(buf);
    return str;
    
# endif
    
}

NNT_END_CXX
