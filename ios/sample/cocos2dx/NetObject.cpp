
# include <Foundation+NNT.h>
# include "NetObject.h"

NETOBJ_BEGIN

NetObj::NetObj()
{
    
}

NetObj::~NetObj()
{
    
}

void Model::callApi(NetObj* obj)
{
    NetObj::req_type* req = new NetObj::req_type(obj);
    req->setRequestType(NetObj::req_type::kHttpPost);
    req->setUrl(obj->getUrl().c_str());
    obj->initRequest(*req);
    NetObj::cli_type::getInstance()->send(req);
    req->release();
}

NETOBJ_END
