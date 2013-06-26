
# include <Foundation+NNT.h>
# include "Model.h"

NETOBJ_BEGIN

# define DELEGATE_CALL(func) if (m->delegate) m->delegate->func;

void Model::cbHttpResponse(NetObj::cli_type* cli, NetObj::respn_type* respn)
{
    NetObj* m = (NetObj*)respn->getHttpRequest()->getUserData();
    
    int code = respn->getResponseCode();
    if (code != 200)
    {
        DELEGATE_CALL(onFailResponsed(m));
        DELEGATE_CALL(onFailed(m));
        return;
    }
    
    vector<char> const& buf = *respn->getResponseData();
    json_tokener* tok = json_tokener_new();
    json_object* jobj = json_tokener_parse_ex(tok, &buf[0], buf.size());
    bool ret = tok->err == json_tokener_success;
    json_tokener_free(tok);
    if (!ret)
    {
        DELEGATE_CALL(onFailParsed(m));
        DELEGATE_CALL(onFailed(m));
        return;
    }
    
    // load default.
    json_object* ncode = json_object_object_get(jobj, "code");
    json_object* nmsg = json_object_object_get(jobj, "message");
    json_object* ndata = json_object_object_get(jobj, "data");
    if (!ncode || !nmsg || !ndata)
    {
        DELEGATE_CALL(onFailParsed(m));
        DELEGATE_CALL(onFailed(m));
        json_object_put(jobj);
        m->release();
        return;
    }
    
    m->code = json_object_get_int(ncode);
    m->message = json_object_get_string(nmsg);
    
    if (m->code != 0)
    {
        DELEGATE_CALL(onFailCalled(m, m->message.c_str()));
        DELEGATE_CALL(onFailed(m));
        json_object_put(jobj);
        m->release();
        return;
    }
    
    // from json to api.
    m->parse(ndata);
    
    // suc.
    DELEGATE_CALL(onSuccess(m));
    
    json_object_put(jobj);
    
    // retain in callApi.
    m->release();
}

void Model::callApi(NetObj* obj)
{
    NetObj::req_type* req = new NetObj::req_type;
    req->setRequestType(NetObj::req_type::kHttpPost);
    req->setUrl(obj->getFullUrl().c_str());
    req->setResponseCallback(this, httpresponse_selector(Model::cbHttpResponse));
    obj->retain();
    req->setUserData(obj);
    obj->initRequest(*req);
    NetObj::cli_type::getInstance()->send(req);
    req->release();
}

NETOBJ_END
