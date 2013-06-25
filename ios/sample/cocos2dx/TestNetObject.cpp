
# include <Foundation+NNT.h>
# include "TestNetObject.h"
# include "UsersLogin.h"

void test_netobj()
{
    trace_msg("try net obj");

    netobj::UsersLogin* ul = new netobj::UsersLogin;
    ul->setIn_appid(123445);
    ul->setIn_channelid(12341);
    ul->setIn_equipmentid("test");
    ul->setIn_applicationversion("xxx");
    ul->setIn_systemversion("yyy");
    ul->setIn_cellbrand("gsm");
    ul->setIn_cellmodel("gsm");
    ul->setIn_device_token("fdssdeew123");
    ul->setIn_mac("31232103213213213");
    ul->setIn_name("test");
    ul->setIn_password("password");
    ul->setIn_rndcheck("test");
    
    netobj::Model::getInstance().callApi(ul);
    
    ul->release();
}