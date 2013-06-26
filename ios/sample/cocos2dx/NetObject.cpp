
# include <Foundation+NNT.h>
# include "NetObject.h"
# include "json.h"

NETOBJ_BEGIN

NetObj::NetObj()
: delegate(NULL)
{
    
}

NetObj::~NetObj()
{
    delegate = NULL;
}

string NetObj::getFullUrl() const
{
    return "http://dev.hoodinn.com/venus09/api/" + getUrl();
}

# define DELEGATE_CALL(func) if (delegate) delegate->func;

void NetObj::cbHttpResponse(cli_type* client, respn_type* respn)
{
    int code = respn->getResponseCode();
    if (code != 200)
    {
        DELEGATE_CALL(failResponsed(this));
        DELEGATE_CALL(failed(this));
        return;
    }
    
    vector<char> const& buf = *respn->getResponseData();
    json_tokener* tok = json_tokener_new();
    json_object* jobj = json_tokener_parse_ex(tok, &buf[0], buf.size());
    bool ret = tok->err == json_tokener_success;
    json_tokener_free(tok);
    if (!ret)
    {
        DELEGATE_CALL(failParsed(this));
        DELEGATE_CALL(failed(this));
        return;
    }
    
    // load default.
    json_object* ncode = json_object_object_get(jobj, "code");
    json_object* nmsg = json_object_object_get(jobj, "message");
    json_object* ndata = json_object_object_get(jobj, "data");
    if (!ncode || !nmsg || !ndata)
    {
        DELEGATE_CALL(failParsed(this));
        DELEGATE_CALL(failed(this));
        json_object_put(jobj);
        return;
    }
    
    this->code = json_object_get_int(ncode);
    message = json_object_get_string(nmsg);
    
    if (this->code != 0)
    {
        DELEGATE_CALL(failCalled(this, message.c_str()));
        DELEGATE_CALL(failed(this));
        json_object_put(jobj);
        return;
    }
    
    // from json to api.
    parse(ndata);
    
    // suc.
    DELEGATE_CALL(success(this));
    
    json_object_put(jobj);
}

void Model::callApi(NetObj* obj)
{
    NetObj::req_type* req = new NetObj::req_type;
    req->setRequestType(NetObj::req_type::kHttpPost);
    req->setUrl(obj->getFullUrl().c_str());
    req->setResponseCallback(obj, httpresponse_selector(NetObj::cbHttpResponse));
    obj->initRequest(*req);
    NetObj::cli_type::getInstance()->send(req);
    req->release();
}

NETOBJ_END
