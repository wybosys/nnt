
# ifndef COMMONOBJ
# define COMMONOBJ

# include "NetObject.h"

NETOBJ_BEGIN

//
class LoginOutputData : public NetObj {
private:
    //账号ID 
    int accountid;
    //昵称 
    string nickname;
    // GENDER_UNKONWN(2):未知, GENDER_MALE(1):男, GENDER_FEMALE(0):女, 
    int gender;
    //生日 
    string birthday;
    //11。第一位1表示是明星，0不是。第二位1表示捐了款 ，0：未捐款 
    string rank;
    //明星文字 
    string introduction;
    //分贝 
    int points;
    //影响力 
    int impactpower;
    //倾听力 
    int listenpower;
    //头像url 
    string avatar;
    //语音签名url 
    string voice;
    //语音长度 
    int voicetime;
    // VIP_TYPE_VIP0(0):不是vip, VIP_TYPE_VIP1(1):是vip, VIP_TYPE_VIP5(5):是钻石vip, 
    int viptypeid;
    //vip开始时间 
    string vipstarttime;
    //vip结束时间 
    string vipexpiretime;
    //账户创建时间 
    string created;
    //账户状态 0：正常  1：停用 
    int status;
    // KIND_NORMAL(0):普通用户, KIND_HOST(5):是版主用户, KIND_GM(10):是GM用户, 
    int kind;
    //元宝余额 
    int gold;
    //籍贯和乡音 
    string nativeplace;
    //职业 
    string occupation;
    //方言 
    string dialect;
    //设备令牌 ios消息推送用 
    string devicetoken;
    //影响力等级 
    int ipowerlevel;
    //倾听力等级 
    int lpowerlevel;
    // ASK_AUTH_YES(1):允许抬杠区发杠, ASK_AUTH_NO(0):不允许抬杠区发杠, 
    int isaskpermit;
    // AGAINST_AUTH_YES(1):允许抬杠区抬杠, AGAINST_AUTH_NO(0):不允许抬杠区抬杠, 
    int isagainstpermit;
    //待领取的礼物数量 
    int giftcount;
    //每日首次登录待领取的分贝数量 
    int pickuppoints;  
    //是否是快速注册用户  0:不是  1：是 
    int isquickuser;
    //是否是plist测试账户  0：不是  1：是 
    int isplisttester;
    //客户端最新版本号 
    string clientversion;
    //客户端更新url 当有新版本更新时才返回该值 
    string updateurl;
    //更新描述  当有新版本更新时才返回该值 
    string updatedesc;
    //是否强制更新plist文件  0：不更新   1：强制更新 
    int restoredefaultplist;
    //绑定的第三方平台 
    vector<string> bindplatformlist; //用户账户(email) 
    string username;
    //注册的平台  例如HOODINN 
    string platform;
    //抬杠区发杠需要分贝 
    int askpoints1;
    //靓杠区发杠需要分贝 
    int askpoints2;
    //背景图片url 
    string background;
    //接受推送新消息通知 1:开启 2:关闭 
    int pushmessage;
    //个人中心是否显示LBS 1:开启 2:关闭 
    int lbs;
    //微信转发时送MP3还是url  0：MP3   1：送url http://t.gangker.com/web/weixin?fid= 
    int weixinur;
    //活动状态  0：正常  1：结束  捐款首页菜单 
    int activitystatus;
    //分享信息版本号 
    int shareversions;
    //是不是第一次进入乡音区 1是,0否 
    int isnewdialect;
    // VCOLOR_NORMAL(0):正常, VCOLOR_VIP1(30):普通vip颜色, VCOLOR_VIP5(40):钻石vip颜色, VCOLOR_VIP5_SPECIAL(50):特殊钻石vip颜色, VCOLOR_SNAKE(200):蛇年神秘气泡颜色, 
    int vcolor;
    //新用户个人信息是否已完善。0：已完善   1：不完善(客户端注册)  2:不完善(第三方登录) 
    int isready;
    //默认激活哪个标签 0 1 2 3 4 
    int tabidx;



public:
    //账号ID
    void setAccountid(int _accountid) {
        accountid = _accountid;
    }
    int getAccountid() {
        return accountid;
    }
    //昵称
    void setNickname(string _nickname) {
        nickname = _nickname;
    }
    string getNickname() {
        return nickname;
    }
    //GENDER_UNKONWN(2):未知, GENDER_MALE(1):男, GENDER_FEMALE(0):女, 
    void setGender(int _gender) {
        gender = _gender;
    }
    int getGender() {
        return gender;
    }
    //生日
    void setBirthday(string _birthday) {
        birthday = _birthday;
    }
    string getBirthday() {
        return birthday;
    }
    //11。第一位1表示是明星，0不是。第二位1表示捐了款 ，0：未捐款
    void setRank(string _rank) {
        rank = _rank;
    }
    string getRank() {
        return rank;
    }
    //明星文字
    void setIntroduction(string _introduction) {
        introduction = _introduction;
    }
    string getIntroduction() {
        return introduction;
    }
    //分贝
    void setPoints(int _points) {
        points = _points;
    }
    int getPoints() {
        return points;
    }
    //影响力
    void setImpactpower(int _impactpower) {
        impactpower = _impactpower;
    }
    int getImpactpower() {
        return impactpower;
    }
    //倾听力
    void setListenpower(int _listenpower) {
        listenpower = _listenpower;
    }
    int getListenpower() {
        return listenpower;
    }
    //头像url
    void setAvatar(string _avatar) {
        avatar = _avatar;
    }
    string getAvatar() {
        return avatar;
    }
    //语音签名url
    void setVoice(string _voice) {
        voice = _voice;
    }
    string getVoice() {
        return voice;
    }
    //语音长度
    void setVoicetime(int _voicetime) {
        voicetime = _voicetime;
    }
    int getVoicetime() {
        return voicetime;
    }
    //VIP_TYPE_VIP0(0):不是vip, VIP_TYPE_VIP1(1):是vip, VIP_TYPE_VIP5(5):是钻石vip, 
    void setViptypeid(int _viptypeid) {
        viptypeid = _viptypeid;
    }
    int getViptypeid() {
        return viptypeid;
    }
    //vip开始时间
    void setVipstarttime(string _vipstarttime) {
        vipstarttime = _vipstarttime;
    }
    string getVipstarttime() {
        return vipstarttime;
    }
    //vip结束时间
    void setVipexpiretime(string _vipexpiretime) {
        vipexpiretime = _vipexpiretime;
    }
    string getVipexpiretime() {
        return vipexpiretime;
    }
    //账户创建时间
    void setCreated(string _created) {
        created = _created;
    }
    string getCreated() {
        return created;
    }
    //账户状态 0：正常  1：停用
    void setStatus(int _status) {
        status = _status;
    }
    int getStatus() {
        return status;
    }
    //KIND_NORMAL(0):普通用户, KIND_HOST(5):是版主用户, KIND_GM(10):是GM用户, 
    void setKind(int _kind) {
        kind = _kind;
    }
    int getKind() {
        return kind;
    }
    //元宝余额
    void setGold(int _gold) {
        gold = _gold;
    }
    int getGold() {
        return gold;
    }
    //籍贯和乡音
    void setNativeplace(string _nativeplace) {
        nativeplace = _nativeplace;
    }
    string getNativeplace() {
        return nativeplace;
    }
    //职业
    void setOccupation(string _occupation) {
        occupation = _occupation;
    }
    string getOccupation() {
        return occupation;
    }
    //方言
    void setDialect(string _dialect) {
        dialect = _dialect;
    }
    string getDialect() {
        return dialect;
    }
    //设备令牌 ios消息推送用
    void setDevicetoken(string _devicetoken) {
        devicetoken = _devicetoken;
    }
    string getDevicetoken() {
        return devicetoken;
    }
    //影响力等级
    void setIpowerlevel(int _ipowerlevel) {
        ipowerlevel = _ipowerlevel;
    }
    int getIpowerlevel() {
        return ipowerlevel;
    }
    //倾听力等级
    void setLpowerlevel(int _lpowerlevel) {
        lpowerlevel = _lpowerlevel;
    }
    int getLpowerlevel() {
        return lpowerlevel;
    }
    //ASK_AUTH_YES(1):允许抬杠区发杠, ASK_AUTH_NO(0):不允许抬杠区发杠, 
    void setIsaskpermit(int _isaskpermit) {
        isaskpermit = _isaskpermit;
    }
    int getIsaskpermit() {
        return isaskpermit;
    }
    //AGAINST_AUTH_YES(1):允许抬杠区抬杠, AGAINST_AUTH_NO(0):不允许抬杠区抬杠, 
    void setIsagainstpermit(int _isagainstpermit) {
        isagainstpermit = _isagainstpermit;
    }
    int getIsagainstpermit() {
        return isagainstpermit;
    }
    //待领取的礼物数量
    void setGiftcount(int _giftcount) {
        giftcount = _giftcount;
    }
    int getGiftcount() {
        return giftcount;
    }
    //每日首次登录待领取的分贝数量
    void setPickuppoints(int _pickuppoints) {
        pickuppoints = _pickuppoints;
    }
    int getPickuppoints() {
        return pickuppoints;
    }
    //是否是快速注册用户  0:不是  1：是
    void setIsquickuser(int _isquickuser) {
        isquickuser = _isquickuser;
    }
    int getIsquickuser() {
        return isquickuser;
    }
    //是否是plist测试账户  0：不是  1：是
    void setIsplisttester(int _isplisttester) {
        isplisttester = _isplisttester;
    }
    int getIsplisttester() {
        return isplisttester;
    }
    //客户端最新版本号
    void setClientversion(string _clientversion) {
        clientversion = _clientversion;
    }
    string getClientversion() {
        return clientversion;
    }
    //客户端更新url 当有新版本更新时才返回该值
    void setUpdateurl(string _updateurl) {
        updateurl = _updateurl;
    }
    string getUpdateurl() {
        return updateurl;
    }
    //更新描述  当有新版本更新时才返回该值
    void setUpdatedesc(string _updatedesc) {
        updatedesc = _updatedesc;
    }
    string getUpdatedesc() {
        return updatedesc;
    }
    //是否强制更新plist文件  0：不更新   1：强制更新
    void setRestoredefaultplist(int _restoredefaultplist) {
        restoredefaultplist = _restoredefaultplist;
    }
    int getRestoredefaultplist() {
        return restoredefaultplist;
    }
    //绑定的第三方平台
    void setBindplatformlist(vector<string> _bindplatformlist) {
        bindplatformlist = _bindplatformlist;
    }    
    vector<string>& getBindplatformlist() {
        return bindplatformlist;
    }    
    //用户账户(email)
    void setUsername(string _username) {
        username = _username;
    }
    string getUsername() {
        return username;
    }
    //注册的平台  例如HOODINN
    void setPlatform(string _platform) {
        platform = _platform;
    }
    string getPlatform() {
        return platform;
    }
    //抬杠区发杠需要分贝
    void setAskpoints1(int _askpoints1) {
        askpoints1 = _askpoints1;
    }
    int getAskpoints1() {
        return askpoints1;
    }
    //靓杠区发杠需要分贝
    void setAskpoints2(int _askpoints2) {
        askpoints2 = _askpoints2;
    }
    int getAskpoints2() {
        return askpoints2;
    }
    //背景图片url
    void setBackground(string _background) {
        background = _background;
    }
    string getBackground() {
        return background;
    }
    //接受推送新消息通知 1:开启 2:关闭
    void setPushmessage(int _pushmessage) {
        pushmessage = _pushmessage;
    }
    int getPushmessage() {
        return pushmessage;
    }
    //个人中心是否显示LBS 1:开启 2:关闭
    void setLbs(int _lbs) {
        lbs = _lbs;
    }
    int getLbs() {
        return lbs;
    }
    //微信转发时送MP3还是url  0：MP3   1：送url http://t.gangker.com/web/weixin?fid=
    void setWeixinur(int _weixinur) {
        weixinur = _weixinur;
    }
    int getWeixinur() {
        return weixinur;
    }
    //活动状态  0：正常  1：结束  捐款首页菜单
    void setActivitystatus(int _activitystatus) {
        activitystatus = _activitystatus;
    }
    int getActivitystatus() {
        return activitystatus;
    }
    //分享信息版本号
    void setShareversions(int _shareversions) {
        shareversions = _shareversions;
    }
    int getShareversions() {
        return shareversions;
    }
    //是不是第一次进入乡音区 1是,0否
    void setIsnewdialect(int _isnewdialect) {
        isnewdialect = _isnewdialect;
    }
    int getIsnewdialect() {
        return isnewdialect;
    }
    //VCOLOR_NORMAL(0):正常, VCOLOR_VIP1(30):普通vip颜色, VCOLOR_VIP5(40):钻石vip颜色, VCOLOR_VIP5_SPECIAL(50):特殊钻石vip颜色, VCOLOR_SNAKE(200):蛇年神秘气泡颜色, 
    void setVcolor(int _vcolor) {
        vcolor = _vcolor;
    }
    int getVcolor() {
        return vcolor;
    }
    //新用户个人信息是否已完善。0：已完善   1：不完善(客户端注册)  2:不完善(第三方登录)
    void setIsready(int _isready) {
        isready = _isready;
    }
    int getIsready() {
        return isready;
    }
    //默认激活哪个标签 0 1 2 3 4
    void setTabidx(int _tabidx) {
        tabidx = _tabidx;
    }
    int getTabidx() {
        return tabidx;
    }


public:
    
    LoginOutputData();
    ~LoginOutputData();
    
    void parse(json_object* obj);

};

NETOBJ_END

# endif
