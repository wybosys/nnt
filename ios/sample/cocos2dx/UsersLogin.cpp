
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

void UsersLogin::initRequest() {

    if (__inputSet__.find("appid") != __inputSet__.end())
    	//[request setPostValue:[NSNumber numberWithInt:in_appid] forKey:@"appid"];
        return;
    if (__inputSet__.find("channelid") != __inputSet__.end())
    	//[request setPostValue:[NSNumber numberWithInt:in_channelid] forKey:@"channelid"];
        return;
    if (__inputSet__.find("equipmentid") != __inputSet__.end())
    	//[request setPostValue:in_equipmentid forKey:@"equipmentid"];
        return;
    if (__inputSet__.find("applicationversion") != __inputSet__.end())
    	//[request setPostValue:in_applicationversion forKey:@"applicationversion"];
        return;
    if (__inputSet__.find("systemversion") != __inputSet__.end())
    	//[request setPostValue:in_systemversion forKey:@"systemversion"];
        return;
    if (__inputSet__.find("cellbrand") != __inputSet__.end())
    	//[request setPostValue:in_cellbrand forKey:@"cellbrand"];
        return;
    if (__inputSet__.find("cellmodel") != __inputSet__.end())
    	//[request setPostValue:in_cellmodel forKey:@"cellmodel"];
        return;
    if (__inputSet__.find("device_token") != __inputSet__.end())
    	//[request setPostValue:in_device_token forKey:@"device_token"];
        return;
    if (__inputSet__.find("mac") != __inputSet__.end())
    	//[request setPostValue:in_mac forKey:@"mac"];
        return;
    if (__inputSet__.find("name") != __inputSet__.end())
    	//[request setPostValue:in_name forKey:@"name"];
        return;
    if (__inputSet__.find("password") != __inputSet__.end())
    	//[request setPostValue:in_password forKey:@"password"];
        return;
    if (__inputSet__.find("rndcheck") != __inputSet__.end())
    	//[request setPostValue:in_rndcheck forKey:@"rndcheck"];
        return;
    
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


void UsersLogin::parse(json_object* obj) {    
    if (obj == NULL)
        return;
    /*
    json_object *node = json_object_object_get(obj, "code");
    this.code = json_object_get_int(node);
    json_object *node = json_object_object_get(obj, "message");
    this.message.assign(json_object_get_string(node), json_object_get_string_len(node));
    json_object *node = json_object_object_get(obj, "data");
    data.parse(node);
     */
}

NETOBJ_END

