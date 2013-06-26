
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

# include <Contrib/cocos2dx/cocos2dx+NNT.h>
# include <extension/network/HttpClient.h>
# include <extension/network/HttpRequest.h>
# include <extension/network/HttpResponse.h>

NETOBJ_BEGIN_C

extern size_t json_object_get_string_len(json_object* jso);

NETOBJ_END_C

NETOBJ_BEGIN

using namespace ::std;

class NetObj
: public cocos2d::CCObject
{
public:
    
    class IDelegate
    {
    public:
        
        virtual ~IDelegate() {}
        
        virtual void onSuccess(NetObj*) {}
        virtual void onFailed(NetObj*) {}
        virtual void onFailCalled(NetObj*, char const*) {}
        virtual void onFailResponsed(NetObj*) const {}
        virtual void onFailParsed(NetObj*) const {}
        
    };
    
    typedef cocos2d::extension::CCHttpRequest req_type;
    typedef json_object* result_obj;
    
    NetObj()
    : delegate(NULL)
    {
        
    }
    
    virtual ~NetObj()
    {
        delegate = NULL;
    }
    
    virtual string getFullUrl() const
    {
        return "http://dev.hoodinn.com/venus09/api/" + getUrl();
    }
    
    virtual string getUrl() const { return ""; }
    virtual void initRequest(req_type&) const {}
    virtual void parse(json_object* obj) {}
    
    IDelegate* delegate;
    
    int code;
    string message;
    
protected:
    
    typedef set<string> set_type;
    set_type __inputSet__;
    
private:

    friend class Model;
    
};

NETOBJ_END

# endif
