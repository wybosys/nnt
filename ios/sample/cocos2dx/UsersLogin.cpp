
# include <Foundation+NNT.h>
# include "UsersLogin.h"

NETOBJ_BEGIN

//output auto generated anonymous structs

//for output

UsersLogin::UsersLogin() {
    in_appid = 0;
    in_channelid = 0;
    in_equipmentid = "";
    in_applicationversion = "";
    in_systemversion = "";
    in_cellbrand = "";
    in_cellmodel = "";
    in_device_token = "";
    in_mac = "";
    in_name = "";
    in_password = "";
    in_rndcheck = "";

    code = 0;
    message = "";
    data = new LoginOutputData();

}

UsersLogin::~UsersLogin() {
    delete data;
}

void UsersLogin::initRequest(req_type& req) const
{
    stringstream ss;
    if (__inputSet__.find("appid") == __inputSet__.end())
        return;
    ss << "appid=" << in_appid << "&";
    if (__inputSet__.find("channelid") == __inputSet__.end())
        return;
    ss << "channelid=" << in_channelid << "&";
    if (__inputSet__.find("equipmentid") == __inputSet__.end())
        return;
    ss << "equipmentid=" << in_equipmentid << "&";
    if (__inputSet__.find("applicationversion") == __inputSet__.end())
        return;
    ss << "applicationversion=" << in_applicationversion << "&";
    if (__inputSet__.find("systemversion") == __inputSet__.end())
        return;
    ss << "systemversion=" << in_systemversion << "&";
    if (__inputSet__.find("cellbrand") == __inputSet__.end())
        return;
    ss << "cellbrand=" << in_cellbrand << "&";
    if (__inputSet__.find("cellmodel") == __inputSet__.end())
        return;
    ss << "cellmodel=" << in_cellmodel << "&";
    if (__inputSet__.find("device_token") == __inputSet__.end())
        return;
    ss << "device_token=" << in_device_token << "&";
    if (__inputSet__.find("mac") == __inputSet__.end())
        return;
    ss << "mac=" << in_mac << "&";
    if (__inputSet__.find("name") == __inputSet__.end())
        return;
    ss << "name=" << in_name << "&";
    if (__inputSet__.find("password") == __inputSet__.end())
        return;
    ss << "password=" << in_password << "&";
    if (__inputSet__.find("rndcheck") == __inputSet__.end())
        return;
    ss << "rndcheck=" << in_rndcheck;
    
    string str = ss.str();
    req.setRequestData(str.c_str(), str.length());
}

void UsersLogin::setIn_appid(int _appid) {
    in_appid = _appid;
    __inputSet__.insert("appid");
}
void UsersLogin::setIn_channelid(int _channelid) {
    in_channelid = _channelid;
    __inputSet__.insert("channelid");
}
void UsersLogin::setIn_equipmentid(string _equipmentid) {
    in_equipmentid = _equipmentid;
    __inputSet__.insert("equipmentid");
}
void UsersLogin::setIn_applicationversion(string _applicationversion) {
    in_applicationversion = _applicationversion;
    __inputSet__.insert("applicationversion");
}
void UsersLogin::setIn_systemversion(string _systemversion) {
    in_systemversion = _systemversion;
    __inputSet__.insert("systemversion");
}
void UsersLogin::setIn_cellbrand(string _cellbrand) {
    in_cellbrand = _cellbrand;
    __inputSet__.insert("cellbrand");
}
void UsersLogin::setIn_cellmodel(string _cellmodel) {
    in_cellmodel = _cellmodel;
    __inputSet__.insert("cellmodel");
}
void UsersLogin::setIn_device_token(string _device_token) {
    in_device_token = _device_token;
    __inputSet__.insert("device_token");
}
void UsersLogin::setIn_mac(string _mac) {
    in_mac = _mac;
    __inputSet__.insert("mac");
}
void UsersLogin::setIn_name(string _name) {
    in_name = _name;
    __inputSet__.insert("name");
}
void UsersLogin::setIn_password(string _password) {
    in_password = _password;
    __inputSet__.insert("password");
}
void UsersLogin::setIn_rndcheck(string _rndcheck) {
    in_rndcheck = _rndcheck;
    __inputSet__.insert("rndcheck");
}


void UsersLogin::parse(json_object* obj)
{
    json_object* node;
    
    node = json_object_object_get(obj, "accountid");
    if (node)
        data->setAccountid(json_object_get_int(node));
    node = json_object_object_get(obj, "nickname");
    if (node)
        data->setNickname(json_object_get_string(node));
}

NETOBJ_END

