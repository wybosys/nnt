
# ifndef USERLOGIN
# define USERLOGIN

# include "NetObject.h"
# include "CommonObj.h"
# include "Const.h"

//output auto generated anonymous structs
//for output
//

NETOBJ_BEGIN

class UsersLogin
: public NetObj
{
private:        

    //input fields
    //应用ID 
    int in_appid;
    //渠道ID 
    int in_channelid;
    //设备ID 
    string in_equipmentid;
    //应用版本 
    string in_applicationversion;
    //系统版本 
    string in_systemversion;
    // 
    string in_cellbrand;
    // 
    string in_cellmodel;
    //设备令牌 
    string in_device_token;
    //mac地址 
    string in_mac;
    // 
    string in_name;
    // 
    string in_password;
    // 
    string in_rndcheck;


//output fields

private:
    
    // 
    int code;
    // 
    string message;
    // 
    LoginOutputData* data;

public:
    
    void setIn_appid(int _appid);
    void setIn_channelid(int _channelid);
    void setIn_equipmentid(string _equipmentid);
    void setIn_applicationversion(string _applicationversion);
    void setIn_systemversion(string _systemversion);
    void setIn_cellbrand(string _cellbrand);
    void setIn_cellmodel(string _cellmodel);
    void setIn_device_token(string _device_token);
    void setIn_mac(string _mac);
    void setIn_name(string _name);
    void setIn_password(string _password);
    void setIn_rndcheck(string _rndcheck);


    //
    void setCode(int _code) {
        code = _code;
    }
    int getCode() {
        return code;
    }
    //
    void setMessage(string _message) {
        message = _message;
    }
    string getMessage() {
        return message;
    }
    //
    void setData(LoginOutputData* _data) {
        data = _data;
    }    
    LoginOutputData* getData() {
        return data;
    }


public:
    
    UsersLogin();
    ~UsersLogin();
    
    string getUrl() const
    {
        return API_USERS_LOGIN;
    }
    
    virtual void initRequest(req_type&) const;
    void parse(json_object* obj);

};

NETOBJ_END

# endif
