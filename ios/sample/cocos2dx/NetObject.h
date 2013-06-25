
# ifndef NETOBJ
# define NETOBJ

# define NETOBJ_BEGIN_C extern "C" {
# define NETOBJ_END_C }
# define NETOBJ_BEGIN namespace netobj {
# define NETOBJ_END }

# include <string>
# include <vector>
# include <list>
# include <set>
# include "json.h"

NETOBJ_BEGIN_C

extern size_t json_object_get_string_len(json_object* jso);

NETOBJ_END_C

NETOBJ_BEGIN

using namespace ::std;

class NetObj
{
public:
    
    NetObj();
    virtual ~NetObj();
    
    virtual string getUrl() { return ""; }
    virtual void initRequest() { return; }
    virtual void parse(json_object* obj) = 0;

};

NETOBJ_END

# endif
