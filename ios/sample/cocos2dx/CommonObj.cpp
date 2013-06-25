
# include <Foundation+NNT.h>
# include "Const.h"
# include "CommonObj.h"

NETOBJ_BEGIN

LoginOutputData::LoginOutputData() {
    accountid = 0;
    nickname = "";
    gender = 0;
    birthday = "";
    rank = "";
    introduction = "";
    points = 0;
    impactpower = 0;
    listenpower = 0;
    avatar = "";
    voice = "";
    voicetime = 0;
    viptypeid = 0;
    vipstarttime = "";
    vipexpiretime = "";
    created = "";
    status = 0;
    kind = 0;
    gold = 0;
    nativeplace = "";
    occupation = "";
    dialect = "";
    devicetoken = "";
    ipowerlevel = 0;
    lpowerlevel = 0;
    isaskpermit = 0;
    isagainstpermit = 0;
    giftcount = 0;
    pickuppoints = 0;
    isquickuser = 0;
    isplisttester = 0;
    clientversion = "";
    updateurl = "";
    updatedesc = "";
    restoredefaultplist = 0;
    username = "";
    platform = "";
    askpoints1 = 0;
    askpoints2 = 0;
    background = "";
    pushmessage = 0;
    lbs = 0;
    weixinur = 0;
    activitystatus = 0;
    shareversions = 0;
    isnewdialect = 0;
    vcolor = 0;
    isready = 0;
    tabidx = 0;

}

LoginOutputData::~LoginOutputData() {
    
}

void LoginOutputData::parse(json_object* obj) {    
    if (obj == NULL)
        return;
    
    json_object* node;
    
    node = json_object_object_get(obj, "accountid");
    this->accountid = json_object_get_int(node);
    node = json_object_object_get(obj, "nickname");
    this->nickname.assign(json_object_get_string(node), json_object_get_string_len(node));
    node = json_object_object_get(obj, "gender");
    this->gender = json_object_get_int(node);
    node = json_object_object_get(obj, "birthday");
    this->birthday.assign(json_object_get_string(node), json_object_get_string_len(node));
    node = json_object_object_get(obj, "rank");
    this->rank.assign(json_object_get_string(node), json_object_get_string_len(node));
    node = json_object_object_get(obj, "introduction");
    this->introduction.assign(json_object_get_string(node), json_object_get_string_len(node));
    node = json_object_object_get(obj, "points");
    this->points = json_object_get_int(node);
    node = json_object_object_get(obj, "impactpower");
    this->impactpower = json_object_get_int(node);
    node = json_object_object_get(obj, "listenpower");
    this->listenpower = json_object_get_int(node);
    node = json_object_object_get(obj, "avatar");
    this->avatar.assign(json_object_get_string(node), json_object_get_string_len(node));
    node = json_object_object_get(obj, "voice");
    this->voice.assign(json_object_get_string(node), json_object_get_string_len(node));
    node = json_object_object_get(obj, "voicetime");
    this->voicetime = json_object_get_int(node);
    node = json_object_object_get(obj, "viptypeid");
    this->viptypeid = json_object_get_int(node);
    node = json_object_object_get(obj, "vipstarttime");
    this->vipstarttime.assign(json_object_get_string(node), json_object_get_string_len(node));
    node = json_object_object_get(obj, "vipexpiretime");
    this->vipexpiretime.assign(json_object_get_string(node), json_object_get_string_len(node));
    node = json_object_object_get(obj, "created");
    this->created.assign(json_object_get_string(node), json_object_get_string_len(node));
    node = json_object_object_get(obj, "status");
    this->status = json_object_get_int(node);
    node = json_object_object_get(obj, "kind");
    this->kind = json_object_get_int(node);
    node = json_object_object_get(obj, "gold");
    this->gold = json_object_get_int(node);
    node = json_object_object_get(obj, "nativeplace");
    this->nativeplace.assign(json_object_get_string(node), json_object_get_string_len(node));
    node = json_object_object_get(obj, "occupation");
    this->occupation.assign(json_object_get_string(node), json_object_get_string_len(node));
    node = json_object_object_get(obj, "dialect");
    this->dialect.assign(json_object_get_string(node), json_object_get_string_len(node));
    node = json_object_object_get(obj, "devicetoken");
    this->devicetoken.assign(json_object_get_string(node), json_object_get_string_len(node));
    node = json_object_object_get(obj, "ipowerlevel");
    this->ipowerlevel = json_object_get_int(node);
    node = json_object_object_get(obj, "lpowerlevel");
    this->lpowerlevel = json_object_get_int(node);
    node = json_object_object_get(obj, "isaskpermit");
    this->isaskpermit = json_object_get_int(node);
    node = json_object_object_get(obj, "isagainstpermit");
    this->isagainstpermit = json_object_get_int(node);
    node = json_object_object_get(obj, "giftcount");
    this->giftcount = json_object_get_int(node);
    node = json_object_object_get(obj, "pickuppoints");
    this->pickuppoints = json_object_get_int(node);
    node = json_object_object_get(obj, "levelconfig");
    node = json_object_object_get(obj, "isquickuser");
    this->isquickuser = json_object_get_int(node);
    node = json_object_object_get(obj, "isplisttester");
    this->isplisttester = json_object_get_int(node);
    node = json_object_object_get(obj, "clientversion");
    this->clientversion.assign(json_object_get_string(node), json_object_get_string_len(node));
    node = json_object_object_get(obj, "updateurl");
    this->updateurl.assign(json_object_get_string(node), json_object_get_string_len(node));
    node = json_object_object_get(obj, "updatedesc");
    this->updatedesc.assign(json_object_get_string(node), json_object_get_string_len(node));
    node = json_object_object_get(obj, "restoredefaultplist");
    this->restoredefaultplist = json_object_get_int(node);
    node = json_object_object_get(obj, "bindplatformlist");
    array_list* array =  json_object_get_array(obj);
    if (array) {
        int len = array_list_length(array);
        for (int i = 0; i < len; i++) {
            json_object *obj = (json_object*)array_list_get_idx(array, i);
            if (!obj)
                continue;

            json_type type = json_object_get_type(obj); 
            if (type == json_type_object) {
                //* tmp = new ();
                //tmp.parse(obj);
                //bindplatformlist.push_back(tmp);
            } else if (type == json_type_int) {
                //bindplatformlist.push_back(itoa(json_object_get_int(obj)));
            } else if (type == json_type_double) {
                //bindplatformlist.push_back(json_object_get_double(obj));
            } else if (type == json_type_string) {
                string str;
                bindplatformlist.push_back(str.assign(json_object_get_string(obj), json_object_get_string_len(obj)));
            }
        }
    }node = json_object_object_get(obj, "username");
    this->username.assign(json_object_get_string(node), json_object_get_string_len(node));
    node = json_object_object_get(obj, "platform");
    this->platform.assign(json_object_get_string(node), json_object_get_string_len(node));
    node = json_object_object_get(obj, "askpoints1");
    this->askpoints1 = json_object_get_int(node);
    node = json_object_object_get(obj, "askpoints2");
    this->askpoints2 = json_object_get_int(node);
    node = json_object_object_get(obj, "background");
    this->background.assign(json_object_get_string(node), json_object_get_string_len(node));
    node = json_object_object_get(obj, "pushmessage");
    this->pushmessage = json_object_get_int(node);
    node = json_object_object_get(obj, "lbs");
    this->lbs = json_object_get_int(node);
    node = json_object_object_get(obj, "weixinur");
    this->weixinur = json_object_get_int(node);
    node = json_object_object_get(obj, "activitystatus");
    this->activitystatus = json_object_get_int(node);
    node = json_object_object_get(obj, "shareversions");
    this->shareversions = json_object_get_int(node);
    node = json_object_object_get(obj, "isnewdialect");
    this->isnewdialect = json_object_get_int(node);
    node = json_object_object_get(obj, "vcolor");
    this->vcolor = json_object_get_int(node);
    node = json_object_object_get(obj, "isready");
    this->isready = json_object_get_int(node);
    node = json_object_object_get(obj, "tabidx");
    this->tabidx = json_object_get_int(node);


}

NETOBJ_END
