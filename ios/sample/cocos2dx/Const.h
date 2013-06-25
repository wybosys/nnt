
# ifndef CONST
# define CONST

#define API_VERSION  1  //
#define GENDER_UNKONWN  2  // : 未知
#define GENDER_MALE  1  // : 男
#define GENDER_FEMALE  0  // : 女

#define FRIEND_RELATION_STRANGER  0  // : 不是好友
#define FRIEND_RELATION_FRIEND  1  // : 是好友
#define FRIEND_RELATION_SELF  2  // : 本人

#define MONEY_TYPE_GOLD  1  // 货币类型: 元宝
#define MONEY_TYPE_POINT  2  // 货币类型: 分贝

#define COLOR_TYPE_GOLDEN  1  // 钻石vip颜色: 金色
#define COLOR_TYPE_RED  2  // 钻石vip颜色: 红色

#define ITEM_TYPE_FUNCTION  1  // 道具类型: 功能类道具
#define ITEM_TYPE_CLAP  2  // 道具类型: 鼓掌类道具

#define ITEM_BIZ_TYPE_BUY  1  // 道具获得类型: 购买获得
#define ITEM_BIZ_TYPE_DONATE  2  // 道具获得类型: 系统赠送
#define ITEM_BIZ_TYPE_LOTTERY  3  // 道具获得类型: 普通摇奖
#define ITEM_BIZ_TYPE_JUDGE_LOTTERY  4  // 道具获得类型: 评审员摇奖

#define ITEM_SUB_TYPE_BIND  10  // 道具获得子类型: 快速注册绑定账户赠送
#define ITEM_SUB_TYPE_EXPLODE  5  // 道具获得子类型: 组合道具释放

#define ONLINE_STATUS_ONLINE  1  // 是否在线: 在线
#define ONLINE_STATUS_OFFLINE  0  // 是否在线: 离线

#define MESSAGE_DIRECTION_OUT  1  // 消息方向: 发出消息
#define MESSAGE_DIRECTION_IN  0  // 消息方向: 收到消息

#define ANSWER_NONE  -1  // : 未参与过该杠题
#define ANSWER_SIDE1  1  // : 以正方身份参与过该杠题
#define ANSWER_SIDE0  0  // : 以反方身份参与过该杠题

#define JOIN_TYPE_ASK  1  // 参与类型: 发杠人
#define JOIN_TYPE_AGAINST  2  // 参与类型: 抬杠人
#define JOIN_TYPE_COMMENT  3  // 参与类型: 参与评论人

#define VOICE_TYPE_ASK  1  // 语音类型: 发杠语音
#define VOICE_TYPE_AGAINST  2  // 语音类型: 抬杠语音
#define VOICE_TYPE_COMMENT  3  // 语音类型: 评论语音

#define AT_TYPE_NONE  0  // : 不是@
#define AT_TYPE_ASK  1  // : @发杠人
#define AT_TYPE_AGAINST  2  // : @抬杠人
#define AT_TYPE_COMMENT  3  // : @参与评论人

#define TOP_TYPE_YES  1  // : 置顶了
#define TOP_TYPE_NO  0  // : 没有置顶

#define WIN_SIDE_ASK  1  // : 正方获胜
#define WIN_SIDE_AGAINST  0  // : 反方获胜
#define WIN_SIDE_NONE  5  // : 抬杠中，未结算

#define QUESTION_TYPE_QUESTION_AREA  1  // : 抬杠区
#define QUESTION_TYPE_TOPIC_AREA  2  // : 靓杠区
#define QUESTION_TYPE_CHANNEL_AREA  20  // : 频道区
#define QUESTION_TYPE_FM_AREA  21  // : FM区
#define QUESTION_TYPE_WISH_TYPE  30  // : 祝福
#define QUESTION_TYPE_ACTIVITY_TYPE  40  // : 活动
#define QUESTION_TYPE_ACTIVITY_STAR_SHARE  50  // : 明星分享
#define QUESTION_TYPE_PIC_TYPE  60  // : 照片
#define QUESTION_TYPE_VOICE_SIGN_TYPE  70  // : 语音签名

#define FAVOURITE_FAVOURITED  1  // : 收藏了
#define FAVOURITE_NONE  0  // : 未收藏

#define VIP_TYPE_VIP0  0  // : 不是vip
#define VIP_TYPE_VIP1  1  // : 是vip
#define VIP_TYPE_VIP5  5  // : 是钻石vip

#define KIND_NORMAL  0  // : 普通用户
#define KIND_HOST  5  // : 是版主用户
#define KIND_GM  10  // : 是GM用户

#define ASK_AUTH_YES  1  // : 允许抬杠区发杠
#define ASK_AUTH_NO  0  // : 不允许抬杠区发杠

#define AGAINST_AUTH_YES  1  // : 允许抬杠区抬杠
#define AGAINST_AUTH_NO  0  // : 不允许抬杠区抬杠

#define FILTER_TYPE_ALL  0  // : 所有杠题
#define FILTER_TYPE_MY_AA_QUESTION  1  // : 我的发杠(包括发杠和抬杠)
#define FILTER_TYPE_MY_JOIN_QUESTION  2  // : 我的参与
#define FILTER_TYPE_FRIEND_AA_QUESTION  3  // : 好友发杠和抬杠的

#define ORDERBY_TYPE_STARTTIME  1  // : 抬杠时间
#define ORDERBY_TYPE_LAST_MODIFIED  3  // : 活跃度)
#define ORDERBY_TYPE_COMMENTS_COUNT  4  // : 评论数
#define ORDERBY_TYPE_ASKER_IMPACTPOWER  5  // : 发杠人影响力

#define CATEGORY_ID_PK  1  // : 抬杠PK台(抬杠区)
#define CATEGORY_ID_HELP  3  // : 帮帮忙(靓杠区)
#define CATEGORY_ID_HOMEFRIEND  4  // : 乡音交友(靓杠区)
#define CATEGORY_ID_CHAT  5  // : 休闲聊天(靓杠区)
#define CATEGORY_ID_TALENTSHOW  6  // : 达人秀(靓杠区)
#define CATEGORY_ID_TOP  5000  // : 置顶精华区(靓杠区)
#define CATEGORY_ID_BEIJING  1001  // : 北京
#define CATEGORY_ID_TIANJING  1002  // : 天津
#define CATEGORY_ID_HEBEI  1003  // : 河北
#define CATEGORY_ID_SHANXI  1004  // : 山西
#define CATEGORY_ID_NEIMENG  1005  // : 内蒙古
#define CATEGORY_ID_LIAONING  1006  // : 辽宁
#define CATEGORY_ID_JILIN  1007  // : 吉林
#define CATEGORY_ID_HEILONGJIANG  1008  // : 黑龙江
#define CATEGORY_ID_SHANGHAI  1009  // : 上海
#define CATEGORY_ID_JIANGSU  1010  // : 江苏
#define CATEGORY_ID_ZHEJIANG  1011  // : 浙江
#define CATEGORY_ID_ANHUI  1012  // : 安徽
#define CATEGORY_ID_FUJIAN  1013  // : 福建
#define CATEGORY_ID_JIANGXI  1014  // : 江西
#define CATEGORY_ID_SHANDONG  1015  // : 山东
#define CATEGORY_ID_HENAN  1016  // : 河南
#define CATEGORY_ID_HUBEI  1017  // : 湖北
#define CATEGORY_ID_HUNAN  1018  // : 湖南
#define CATEGORY_ID_GUANGDONG  1019  // : 广东
#define CATEGORY_ID_HAINAN  1020  // : 海南
#define CATEGORY_ID_CHONGQING  1021  // : 重庆
#define CATEGORY_ID_SICHUAN  1022  // : 四川
#define CATEGORY_ID_GUIZHOU  1023  // : 贵州
#define CATEGORY_ID_YUNNAN  1024  // : 云南
#define CATEGORY_ID_XIZANG  1025  // : 西藏
#define CATEGORY_ID_SHAANXI  1026  // : 陕西
#define CATEGORY_ID_GANSU  1027  // : 甘肃
#define CATEGORY_ID_QINGHAI  1028  // : 青海
#define CATEGORY_ID_NINGXIA  1029  // : 宁夏
#define CATEGORY_ID_XINJIANG  1030  // : 新疆
#define CATEGORY_ID_XIANGGANG  1031  // : 香港
#define CATEGORY_ID_AOMEN  1032  // : 澳门
#define CATEGORY_ID_TAIWAN  1033  // : 台湾
#define CATEGORY_ID_GUANGXI  1034  // : 广西

#define STATUS_WAITING  0  // : 待杠状态
#define STATUS_PROCESSING  1  // : 抬杠状态
#define STATUS_FINISHED  10  // : 结束状态
#define STATUS_INCOMPUTING  5  // : 结算中
#define STATUS_CHECK_ASK  20  // : 杠题等待发杠审核
#define STATUS_CHECK_AGAINST  30  // : 杠题等待抬杠审核
#define STATUS_CHECK_ASK_FAIL  25  // : 杠题发杠审核未通过
#define STATUS_DELETED  512  // : 已删除 513代表抬杠后被删除
#define STATUS_LOCKED  256  // : 已锁定 257代表抬杠后被锁定

#define VCOLOR_NORMAL  0  // : 正常
#define VCOLOR_VIP1  30  // : 普通vip颜色
#define VCOLOR_VIP5  40  // : 钻石vip颜色
#define VCOLOR_VIP5_SPECIAL  50  // : 特殊钻石vip颜色
#define VCOLOR_SNAKE  200  // : 蛇年神秘气泡颜色

#define CONTENT_TYPE_QUESTION  2  // 聚焦页内容类型: 杠题
#define CONTENT_TYPE_CATEGORY  3  // 聚焦页内容类型: 板块（休闲聊天，乡音交友等）
#define CONTENT_TYPE_SUBJECT  4  // 聚焦页内容类型: 专题
#define CONTENT_TYPE_GEM  9  // 聚焦页内容类型: 焦点语录
#define CONTENT_TYPE_WEB_PAGE  7  // 聚焦页内容类型: 网页
#define CONTENT_TYPE_PARTY  8  // 聚焦页内容类型: party
#define CONTENT_TYPE_AD  11  // 聚焦页内容类型: 广告
#define CONTENT_TYPE_SHOP  12  // 聚焦页内容类型: 商店
#define CONTENT_TYPE_RANKING  13  // 聚焦页内容类型: 排行榜  排行榜    新人榜、TOP榜、主播榜、收听榜 (ranktype=1,2,3,4)
#define CONTENT_TYPE_INTERVIEW  14  // 聚焦页内容类型: 采访
#define CONTENT_TYPE_CC  15  // 聚焦页内容类型: 客服
#define CONTENT_TYPE_APP  16  // 聚焦页内容类型: app推荐
#define CONTENT_TYPE_NEARBY_PEOPLE  17  // 聚焦页内容类型: 附近杠友
#define CONTENT_TYPE_ACTIVITY  22  // 聚焦页内容类型: 活动（捐款）
#define CONTENT_TYPE_USERCENTER  27  // 聚焦页内容类型: 个人中心
#define CONTENT_TYPE_SUBJECT_HISTORY  104  // 聚焦页内容类型: 历史专辑入口（点击可直接跳转历史专辑）
#define CONTENT_TYPE_FM_TOPIC  121  // 聚焦页内容类型: 新频道区杠题
#define CONTENT_TYPE_FM_LIST  123  // 聚焦页内容类型: 新频道列表
#define CONTENT_TYPE_FM_INFO  124  // 聚焦页内容类型: 新频道信息页
#define CONTENT_TYPE_MERGE  131  // 聚焦页内容类型: 新人、最新、乡音、精华,最热   (mtype=1,2,3,4,5)
#define CONTENT_TYPE_FOLLOW_PUSH  151  // 聚焦页内容类型: 推荐关注列表
#define CONTENT_TYPE_GAME  161  // 聚焦页内容类型: 游戏入口（预留接口，跳转游戏列表页）

#define JOIN_STATUS_ASK_TYPE  20  // 杠题审核类型: 发杠审核
#define JOIN_STATUS_AGAINST_TYPE  30  // 杠题审核类型: 抬杠审核
#define JOIN_STATUS_CHALLENGE_ASK_TYPE  40  // 杠题审核类型: 抬它发杠审核
#define JOIN_STATUS_CHALLENGE_AGAINST_TYPE  70  // 杠题审核类型: 抬它抬杠审核

#define CHECK_VOTE_YES  1  // 杠题审核投票选择: 赞成票
#define CHECK_VOTE_NO  2  // 杠题审核投票选择: 反对票

#define CHECK_STATUS_PROCESSING  50  // 杠题审核状态: 审核中
#define CHECK_STATUS_PASS  60  // 杠题审核状态: 审核通过
#define CHECK_STATUS_FAIL  55  // 杠题审核状态: 审核未通过

#define CHECK_REFUSE_TYPE_SAY_SOMETHING  90  // 杠题审核拒绝理由: 评审员有话要说，发表语音
#define CHECK_REFUSE_TYPE_VULGAR  110  // 杠题审核拒绝理由: 三俗话题
#define CHECK_REFUSE_TYPE_OBVIOUS  120  // 杠题审核拒绝理由: 必胜杠题
#define CHECK_REFUSE_TYPE_NO_DEFINITE_POINT  130  // 杠题审核拒绝理由: 无明确观点
#define CHECK_REFUSE_TYPE_NO_DEFINITE_PROOF  140  // 杠题审核拒绝理由: 无明确论据
#define CHECK_REFUSE_TYPE_INPOLITE_WORD  210  // 杠题审核拒绝理由: 不文明用语
#define CHECK_REFUSE_TYPE_SAME_POINT  220  // 杠题审核拒绝理由: 观点一致
#define CHECK_REFUSE_TYPE_IRRELEVANT  230  // 杠题审核拒绝理由: 答非所问

#define SYSTEM_MESSAGE_TYPE_SYSTEM  1  // 系统消息类型（总的分类）: 系统动态消息
#define SYSTEM_MESSAGE_TYPE_QUESTION  2  // 系统消息类型（总的分类）: 杠题动态消息
#define SYSTEM_MESSAGE_TYPE_CHECK  3  // 系统消息类型（总的分类）: 审核动态消息
#define SYSTEM_MESSAGE_TYPE_SYSALL  5  // 系统消息类型（总的分类）: v2 系统消息

#define MESSAGE_TYPE_INVITE  201  // 消息类型（系统消息的具体类型编码）: 好友邀请通知
#define MESSAGE_TYPE_AGREE  202  // 消息类型（系统消息的具体类型编码）: 好友添加成功通知（对方同意）
#define MESSAGE_TYPE_AUTOAGREE  204  // 消息类型（系统消息的具体类型编码）: 好友添加成功通知（自动同意）
#define MESSAGE_TYPE_NOTICE  102  // 消息类型（系统消息的具体类型编码）: 官方通告
#define MESSAGE_TYPE_MOST_LISTENED_BY  230  // 消息类型（系统消息的具体类型编码）: xxx成为听你最多的用户
#define MESSAGE_TYPE_MOST_LISTENTO  231  // 消息类型（系统消息的具体类型编码）: xxx成为你听的最多的用户
#define MESSAGE_TYPE_INVITED_INTERVIEWED  232  // 消息类型（系统消息的具体类型编码）: 邀请接受采访
#define MESSAGE_TYPE_FRIEND_MOST_LISTENTO  241  // 消息类型（系统消息的具体类型编码）: 你成为谁最忠实的粉丝，你是否要加他好友
#define MESSAGE_TYPE_FRIEND_MOST_LISTENED_BY  240  // 消息类型（系统消息的具体类型编码）: 谁成为你最忠实的粉丝，你是否要加他好友
#define MESSAGE_TYPE_FRIEND_AT_YOU  242  // 消息类型（系统消息的具体类型编码）: XX已经@你3次了，你是否要加他好友
#define MESSAGE_TYPE_FRIEND_YOU_AT  243  // 消息类型（系统消息的具体类型编码）: 你已经@XX3次了，你是否要加他好友
#define MESSAGE_TYPE_AT_INVITE  244  // 消息类型（系统消息的具体类型编码）: “XX”用户给你发了一个@他邀请，去参与吧
#define MESSAGE_TYPE_AT_INVITE_ACCEPTED  245  // 消息类型（系统消息的具体类型编码）: B用户已经参与了你发送的@他邀请
#define MESSAGE_TYPE_FM_APPLY  265  // 消息类型（系统消息的具体类型编码）: v2 用户申请加入频道消息
#define MESSAGE_TYPE_FM_INVITE  266  // 消息类型（系统消息的具体类型编码）: v2 管理员邀请用户加入频道消息
#define MESSAGE_TYPE_FM_BE_MEMBER  267  // 消息类型（系统消息的具体类型编码）: v2 成为主播
#define MESSAGE_TYPE_FM_BE_CHIEF  268  // 消息类型（系统消息的具体类型编码）: v2 成为台长或临时台长
#define MESSAGE_TYPE_FM_INVITEE_ACCEPTED  269  // 消息类型（系统消息的具体类型编码）: v2 听众a接受您的邀请，加入了频道
#define MESSAGE_TYPE_FM_INVITEE_REJECTED  270  // 消息类型（系统消息的具体类型编码）: v2  听众a婉拒了您的邀请，另请高明吧！
#define MESSAGE_TYPE_FM_MEMBER_LOST  271  // 消息类型（系统消息的具体类型编码）: v2 您失去了在频道名中的主播资格！
#define MESSAGE_TYPE_FM_MEMBER_QUIT  272  // 消息类型（系统消息的具体类型编码）: v2  听众a退出了您的频道，快去招聘新主播吧！
#define MESSAGE_TYPE_FM_CHIEF_LOST  273  // 消息类型（系统消息的具体类型编码）: v2  您不再是频道名的代理抬长了。
#define MESSAGE_TYPE_FM_COMMENT_TOPPED  274  // 消息类型（系统消息的具体类型编码）: v2 您在节目名中的声援被主播a导播了！
#define MESSAGE_TYPE_FM_DISBLACK  275  // 消息类型（系统消息的具体类型编码）: v2 您不再是频道名的黑名单成员了，快去那里看看吧
#define MESSAGE_TYPE_IMPACTPOWER_TOP  601  // 消息类型（系统消息的具体类型编码）: v2 恭喜你成为抬杠影响力前100的精英杠友
#define MESSAGE_TYPE_LISTENPOWER_TOP  602  // 消息类型（系统消息的具体类型编码）: v2 恭喜你成为抬杠倾听力前100的精英杠友
#define MESSAGE_TYPE_MEDAL  111  // 消息类型（系统消息的具体类型编码）: v2 获得勋章
#define MESSAGE_TYPE_AGAINST  104  // 消息类型（系统消息的具体类型编码）: 杠题被抬，通知发杠人
#define MESSAGE_TYPE_WIN  105  // 消息类型（系统消息的具体类型编码）: 杠题获胜
#define MESSAGE_TYPE_LOSE  106  // 消息类型（系统消息的具体类型编码）: 杠题失败 
#define MESSAGE_TYPE_ATED  110  // 消息类型（系统消息的具体类型编码）: 有人@你了
#define MESSAGE_TYPE_TOPIC_AGAINST  404  // 消息类型（系统消息的具体类型编码）: 杠客区杠题被抬，通知发杠人
#define MESSAGE_TYPE_TOPIC_OVER  407  // 消息类型（系统消息的具体类型编码）: 杠客区杠题结束
#define MESSAGE_TYPE_ASK_CHECK_PASS  331  // 消息类型（系统消息的具体类型编码）: 发杠审核通过
#define MESSAGE_TYPE_ASK_CHECK_FAIL  332  // 消息类型（系统消息的具体类型编码）: 发杠审核未通过
#define MESSAGE_TYPE_AGAINST_CHECK_PASS  333  // 消息类型（系统消息的具体类型编码）: 抬杠审核通过
#define MESSAGE_TYPE_AGAINST_CHECK_FAIL  334  // 消息类型（系统消息的具体类型编码）: 抬杠审核未通过
#define MESSAGE_TYPE_URL  500  // 消息类型（系统消息的具体类型编码）: 带URL的消息类型，点击跳safari

#define EVENT_TYPE_LOGIN  10  // 大事记类型: 首次登陆：第一次登录抬杠软件
#define EVENT_TYPE_TOP  20  // 大事记类型: 杠题置顶
#define EVENT_TYPE_VOICEGEM  30  // 大事记类型: 入选语录
#define EVENT_TYPE_ACTIVITY  40  // 大事记类型: 推荐活动：杠题被选为官方推荐活动
#define EVENT_TYPE_JOIN  50  // 大事记类型: 参与杠题
#define EVENT_TYPE_WIN  60  // 大事记类型: 获胜杠题
#define EVENT_TYPE_INTERVIEW_OVER  70  // 大事记类型: 采访完成
#define EVENT_TYPE_GIFT  80  // 大事记类型: 获得礼物
#define EVENT_TYPE_BE_JUDGE  90  // 大事记类型: 评审员：达成1万影响力，获得评审员资格
#define EVENT_TYPE_BE_RECOMMENDER  100  // 大事记类型: 推荐员：达成1万倾听力，获得推荐评论资格
#define EVENT_TYPE_ASK_QUALIFIED  110  // 大事记类型: 去抬杠区：达成1000影响力，可以去抬杠区发杠
#define EVENT_TYPE_BE_GEM_JUDGE  120  // 大事记类型: 优秀A：成为优秀评审员。（进入官方评审的每月优秀评审员资格）
#define EVENT_TYPE_BE_GEM_RECOMMENDER  130  // 大事记类型: 优秀B：成为优秀推荐员
#define EVENT_TYPE_PROFILE_OK  140  // 大事记类型: 资料完善：个人资料完善100%

#define FEEDBACK_TYPE_COMPLAINT  10  // 用户反馈类型: 投诉杠客
#define FEEDBACK_TYPE_ILLEGAL_PICTURE  20  // 用户反馈类型: 违规图片
#define FEEDBACK_TYPE_BUG  30  // 用户反馈类型: 软件BUG
#define FEEDBACK_TYPE_QUESTION  40  // 用户反馈类型: 抬杠疑问
#define FEEDBACK_TYPE_SUGGESTION  50  // 用户反馈类型: 软件建议
#define FEEDBACK_TYPE_OTHER  60  // 用户反馈类型: 其他
#define FEEDBACK_TYPE_PRIVATE_MESSAGE  70  // 用户反馈类型: 用户私信

#define FEEDBACK_STATUS_WAITING  0  // 用户反馈处理状态: 等待处理
#define FEEDBACK_STATUS_PROCESSING  1  // 用户反馈处理状态: 处理中
#define FEEDBACK_STATUS_FINISHED  2  // 用户反馈处理状态: 已经处理

#define FILE_TYPE_IMAGE  1  // 文件类型: 图片
#define FILE_TYPE_VOICE  2  // 文件类型: 语音

#define TIP_TYPE_QUESTION  100  // 举报类型: 杠题举报
#define TIP_TYPE_PHOTO  200  // 举报类型: 相册图片举报

#define TIP_SUB_TYPE_IMAGE  1  // 举报子类型: 图片
#define TIP_SUB_TYPE_VOICE  2  // 举报子类型: 语音

#define REPORT_TYPE_PERSONAL_ATTACK  10  // 举报理由: 人身攻击
#define REPORT_TYPE_SENSITIVE_INFORMATION  20  // 举报理由: 敏感信息
#define REPORT_TYPE_MALICIOUS_HARASSMENT  30  // 举报理由: 恶意骚扰
#define REPORT_TYPE_PORNOGRAPHY  40  // 举报理由: 色情
#define REPORT_TYPE_EMPTY_VOICE  50  // 举报理由: 空语音
#define REPORT_TYPE_OTHERS  60  // 举报理由: 其他投诉

#define TIP_DEAL_TYPE_COVER  1  // 举报处理操作类型: 流放。进行语音置换
#define TIP_DEAL_TYPE_IGNORE  2  // 举报处理操作类型: 无视。不做处理

#define ADS_TYPE_SOFTWARE_FEATURE  1  // 广告类型: 亮点介绍
#define ADS_TYPE_COMMERCIAL_AD  2  // 广告类型: 商业广告

#define IS_LASTPAGE_YES  1  // : 是最后一页
#define IS_LASTPAGE_NO  0  // : 不是最后一页

#define CHANNEL_MEMBER_TYPE_ROLE_NONMEMBER  0  // 频道成员类型: 非成员
#define CHANNEL_MEMBER_TYPE_ROLE_MASTER  10  // 频道成员类型: 台主
#define CHANNEL_MEMBER_TYPE_ROLE_CHIEF_MATE  20  // 频道成员类型: 抬副
#define CHANNEL_MEMBER_TYPE_ROLE_SECOND_MATE  30  // 频道成员类型: 二副
#define CHANNEL_MEMBER_TYPE_ROLE_GENERAL  50  // 频道成员类型: 普通用户

#define FM_MEMBER_TYPE_NONE  0  // FM成员类型: 非成员
#define FM_MEMBER_TYPE_CHIEF  1  // FM成员类型: 台主
#define FM_MEMBER_TYPE_HOST  2  // FM成员类型: 主播
#define FM_MEMBER_TYPE_TEMP_CHIEF  3  // FM成员类型: 临时抬长

#define FEED_TYPE_ASK  601  // 动态类型: 发起杠题
#define FEED_TYPE_AGAINST  602  // 动态类型: 抬杠题
#define FEED_TYPE_COMMENT  603  // 动态类型: 声援杠题
#define FEED_TYPE_TOP  604  // 动态类型: 发起的杠题被加精
#define FEED_TYPE_BIG_SHOW  605  // 动态类型: 发起的杠题被加大图推荐
#define FEED_TYPE_UPLOAD_NEW_PIC  606  // 动态类型: 上传照片
#define FEED_TYPE_VOICENAME  607  // 动态类型: 更新了语音签名
#define FEED_TYPE_FM_CREATE  608  // 动态类型: 创建频道
#define FEED_TYPE_FM_HOST  609  // 动态类型: 成为频道主播
#define FEED_TYPE_COUNTRY_ARGUE  610  // 动态类型: 乡长推送的杠题
#define FEED_TYPE_FM_ASK  611  // 动态类型: 发起频道节目
#define FEED_TYPE_ACTIVITY  701  // 动态类型: 参与活动
#define FEED_TYPE_BUY_VIP5  702  // 动态类型: 购买钻石VIP
#define FEED_TYPE_GOT_GOLD_ITEM  703  // 动态类型: 被赠送元宝道具
#define FEED_TYPE_PHOTO_UP  704  // 动态类型: 被赞过的照片
#define FEED_TYPE_PERSONAL_VOICE_UP  705  // 动态类型: 被赞过的语音签名
#define FEED_TYPE_VOICE_UP  706  // 动态类型: 被赞过的杠题语音泡泡
#define FEED_TYPE_GOT_MEDAL  707  // 动态类型: 获得勋章
#define FEED_TYPE_MEDAL_UPGRADED  708  // 动态类型: 勋章升级
#define FEED_TYPE_FANS_NUMBER_REACHED  709  // 动态类型: 粉丝到达一定量级
#define FEED_TYPE_PK_FINISH  710  // 动态类型: 参与PK台的杠题结束

#define RESOURCE_TYPE_FEED  100  // : 动态
#define RESOURCE_TYPE_QUESTION_ASK  101  // : 抬杠区发杠人语音
#define RESOURCE_TYPE_QUESTION_AGAINST  102  // : 抬杠区抬杠人语音
#define RESOURCE_TYPE_QUESTION_COMMENT  103  // : 抬杠区评论语音
#define RESOURCE_TYPE_TOPIC_ASK  201  // : 靓杠区发杠人语音
#define RESOURCE_TYPE_TOPIC_AGAINST  202  // : 靓杠区抬杠人语音
#define RESOURCE_TYPE_TOPIC_COMMENT  203  // : 靓杠区评论语音
#define RESOURCE_TYPE_FM_ASK  211  // : 频道区发杠语音
#define RESOURCE_TYPE_FM_COMMENT  213  // : 频道区评论语音
#define RESOURCE_TYPE_PHOTO  501  // : 相册照片
#define RESOURCE_TYPE_USERVOICE  502  // : 语音签名

#define VIEW_ARGUE_FROM_FOCUS  1  // : 焦点区)
#define VIEW_ARGUE_FROM_NEWEST  2  // : 最新)
#define VIEW_ARGUE_FROM_NEAREST  3  // : 附近)
#define VIEW_ARGUE_FROM_DIALECT  4  // : 乡音
#define VIEW_ARGUE_FROM_HOTTEST  5  // : 最热
#define VIEW_ARGUE_FROM_GEM  6  // : 精华
#define VIEW_ARGUE_FROM_NEWBIE  7  // : 新人
#define VIEW_ARGUE_FROM_CHAT  8  // : 聊聊天
#define VIEW_ARGUE_FROM_HELP  9  // : 求帮忙
#define VIEW_ARGUE_FROM_SHOW  10  // : 达人秀
#define VIEW_ARGUE_FROM_PK  11  // : pk台
#define VIEW_ARGUE_FROM_HISTORY  12  // : 历史记录
#define VIEW_ARGUE_FROM_FEED  13  // : 动态
#define VIEW_ARGUE_FROM_UCFEED  14  // : 个人中心中的动态
#define VIEW_ARGUE_FROM_FAVORITE  15  // : 收藏
#define VIEW_ARGUE_FROM_SYSMSG  16  // : 系统消息
#define VIEW_ARGUE_FROM_FMALL  17  // : 全部频道
#define VIEW_ARGUE_FROM_FMLIKED  18  // : 我喜欢的频道
#define VIEW_ARGUE_FROM_FMHISTORY  19  // : 频道历史
#define VIEW_ARGUE_FROM_PUSH  20  // : 大推送
#define VIEW_ARGUE_FROM_ATME  21  // : @我
#define VIEW_ARGUE_FROM_SEARCH  22  // : 搜藏
#define VIEW_ARGUE_FROM_SQUARE  23  // : 广场
#define VIEW_ARGUE_FROM_SUBJECT  24  // : 专题
#define VIEW_ARGUE_FROM_AGAINST  25  // : 抬杠

#define VIEW_MEDAL_FROM_AVATAR  100  // : 头像下面的点击
#define VIEW_MEDAL_FROM_USERCENTER  101  // : 个人中心的点击
#define VIEW_MEDAL_FROM_SYSMSG  102  // : 系统消息 
#define VIEW_MEDAL_FROM_PUSH  103  // : 大推送 

#define UP_FROM_VIEW  110  // : 单条页
#define UP_FROM_FEED  111  // : 动态
#define UP_FROM_PHOTO  112  // : 照片墙
#define UP_FROM_USERVOICE  114  // : 语音签名

#define SHARE_FROM_VIEW  120  // : 单条页
#define SHARE_FROM_FEED  121  // : 动态
#define SHARE_FROM_ASK  122  // : 发杠时分享

#define FM_FROM_BAR  130  // : 快捷送礼
#define FM_FROM_MENU  131  // : 扩展菜单

#define AT_FROM_BAR  140  // : 快捷@
#define AT_FROM_MENU  141  // : 扩展菜单
#define AT_FROM_ATLIST  142  // : @我列表回复

#define PHOTO_FROM_WALL  150  // : 照片墙
#define PHOTO_FROM_FEED  151  // : 动态
#define PHOTO_FROM_SQUARE  152  // : 广场



#define API_USERS_LOGOUT   "users/logout"
#define API_USERS_LOGIN   "users/login"
#define API_USERS_USLOGIN   "users/uslogin"
#define API_USERS_QUICKLOGIN   "users/quicklogin"
#define API_USERS_REGISTER   "users/register"
#define API_USERS_QUICKREGISTER   "users/quickregister"
#define API_USERS_BINDQUICKUSER   "users/bindquickuser"
#define API_USERS_GETBINDUSERS   "users/getbindusers"
#define API_USERS_GETACCOUNTID   "users/getaccountid"
#define API_USERS_NICKNAMECHECK   "users/nicknamecheck"
#define API_USERS_VERSION   "users/version"
#define API_USERS_CHANGEPASSWORD   "users/changepassword"
#define API_USERS_UPDATENEWPASSWORD   "users/updatenewpassword"
#define API_USERS_FINDPASSWORD   "users/findpassword"
#define API_USERS_TLOGIN   "users/tlogin"
#define API_USERS_TBIND   "users/tbind"
#define API_USERS_TUNBIND   "users/tunbind"
#define API_USERS_INITNICKNAME   "users/initnickname"
#define API_USERS_PROFILE   "users/profile"
#define API_USERS_CHANGEPROFILE   "users/changeprofile"
#define API_USERS_CHANGENICKNAME   "users/changenickname"
#define API_USERS_SETPREFERENCE   "users/setpreference"
#define API_USERS_GETPREFERENCE   "users/getpreference"
#define API_USERS_GETUSERSTATISTICS   "users/getuserstatistics"
#define API_USERS_FEEDBACK   "users/feedback"
#define API_USERS_GETPLISTXML   "users/getplistxml"
#define API_USERS_GETTESTPLISTXML   "users/gettestplistxml"
#define API_USERS_SETDEVICETOKEN   "users/setdevicetoken"
#define API_USERS_GETCHANGELIST   "users/getchangelist"
#define API_USERS_RELOG   "users/relog"
#define API_USERS_FOCUS   "users/focus"
#define API_USERS_CHECKUPDATE   "users/checkupdate"
#define API_USERS_PUSH   "users/push"
#define API_USERS_GETVCOLORLIST   "users/getvcolorlist"
#define API_USERS_SETVCOLOR   "users/setvcolor"
#define API_USERS_SSOLOGIN   "users/ssologin"
#define API_USERS_FILLPROFILE   "users/fillprofile"
#define API_USERCENTER_HOME   "usercenter/home"
#define API_USERCENTER_PHOTOLIST   "usercenter/photolist"
#define API_USERCENTER_UPLOADPHOTO   "usercenter/uploadphoto"
#define API_USERCENTER_DELETEPHOTO   "usercenter/deletephoto"
#define API_USERCENTER_USEPHOTOAVATAR   "usercenter/usephotoavatar"
#define API_USERCENTER_GETIMPACTPOWER   "usercenter/getimpactpower"
#define API_USERCENTER_GETLISTENPOWER   "usercenter/getlistenpower"
#define API_USERCENTER_GETGIFTLIST   "usercenter/getgiftlist"
#define API_USERCENTER_GETRECENTVISITORS   "usercenter/getrecentvisitors"
#define API_USERCENTER_GETACHIEVEMENT   "usercenter/getachievement"
#define API_USERCENTER_INTERVIEWS   "usercenter/interviews"
#define API_USERCENTER_ANSWERINTERVIEW   "usercenter/answerinterview"
#define API_USERCENTER_DELETEINTERVIEWANSWER   "usercenter/deleteinterviewanswer"
#define API_USERCENTER_INTERVIEWINVITE   "usercenter/interviewinvite"
#define API_USERCENTER_EVENTS   "usercenter/events"
#define API_USERCENTER_BACKGROUNDIMAGES   "usercenter/backgroundimages"
#define API_USERCENTER_GETUSERSNEARBY   "usercenter/getusersnearby"
#define API_USERCENTER_SETMEDAL   "usercenter/setmedal"
#define API_USERCENTER_GETVOICELIST   "usercenter/getvoicelist"
#define API_USERCENTER_DELETEVOICE   "usercenter/deletevoice"
#define API_USERCENTER_SETPREFERENCE   "usercenter/setpreference"
#define API_USERCENTER_GETPREFERENCE   "usercenter/getpreference"
#define API_USERCENTER_CHECKGIFTBOX   "usercenter/checkgiftbox"
#define API_USERCENTER_BLACKLIST   "usercenter/blacklist"
#define API_USERCENTER_ADDBLACKLIST   "usercenter/addblacklist"
#define API_USERCENTER_DELETEBLACKLIST   "usercenter/deleteblacklist"
#define API_USERCENTER_VIEWMEDAL   "usercenter/viewmedal"
#define API_USERCENTER_GETMEDALS   "usercenter/getmedals"
#define API_USERCENTER_GETNEWMEDALS   "usercenter/getnewmedals"
#define API_USERCENTER_GIFTWALL   "usercenter/giftwall"
#define API_USERCENTER_GIFTWALLDETAILS   "usercenter/giftwalldetails"
#define API_USERCENTER_DEBUG   "usercenter/debug"
#define API_USERCENTER_GETNOTIC   "usercenter/getnotic"
#define API_TOPICS_ASK   "topics/ask"
#define API_TOPICS_GETLIST   "topics/getlist"
#define API_TOPICS_VIEW   "topics/view"
#define API_TOPICS_AGAINST   "topics/against"
#define API_TOPICS_ANSWER   "topics/answer"
#define API_TOPICS_ADDFAVORITE   "topics/addfavorite"
#define API_TOPICS_GETRESULT   "topics/getresult"
#define API_TOPICS_GETTOPLIST   "topics/gettoplist"
#define API_TOPICS_GETHOMELIST   "topics/gethomelist"
#define API_TOPICS_GETHOMEWAITINGLIST   "topics/gethomewaitinglist"
#define API_TOPICS_TREEHOLE   "topics/treehole"
#define API_TOPICS_TOTOP   "topics/totop"
#define API_TOPICS_REJECTP2P   "topics/rejectp2p"
#define API_TOPICCOMMENTS_GETCOMMENTLIST   "topiccomments/getcommentlist"
#define API_TOPICCOMMENTS_COMMENT   "topiccomments/comment"
#define API_TOPICCOMMENTS_SETDIRECTED   "topiccomments/setdirected"
#define API_QUESTIONS_ASK   "questions/ask"
#define API_QUESTIONS_GETLIST   "questions/getlist"
#define API_QUESTIONS_VIEW   "questions/view"
#define API_QUESTIONS_AGAINST   "questions/against"
#define API_QUESTIONS_ANSWER   "questions/answer"
#define API_QUESTIONS_GETLISTBYUSER   "questions/getlistbyuser"
#define API_QUESTIONS_ADDFAVORITE   "questions/addfavorite"
#define API_QUESTIONS_GETFAVORITELIST   "questions/getfavoritelist"
#define API_QUESTIONS_GETRESULT   "questions/getresult"
#define API_QUESTIONS_GETCHECKLIST   "questions/getchecklist"
#define API_QUESTIONS_CHECKQUESTION   "questions/checkquestion"
#define API_QUESTIONS_GETINCHECKINGLIST   "questions/getincheckinglist"
#define API_QUESTIONS_GETCHECKOTHERLIST   "questions/getcheckotherlist"
#define API_QUESTIONS_FORWARDTOTOPIC   "questions/forwardtotopic"
#define API_QUESTIONS_CHECKCLEAN   "questions/checkclean"
#define API_QUESTIONS_AGAINSTLOCK   "questions/againstlock"
#define API_QUESTIONS_VIEWREFUSED   "questions/viewrefused"
#define API_QUESTIONS_GETFRIENDQUESTIONLIST   "questions/getfriendquestionlist"
#define API_QUESTIONS_GETBESTHISTORYLIST   "questions/getbesthistorylist"
#define API_QUESTIONS_GETTOPLIST   "questions/gettoplist"
#define API_COMMENTS_GETCOMMENTLIST   "comments/getcommentlist"
#define API_COMMENTS_COMMENT   "comments/comment"
#define API_COMMENTS_GETATMELIST   "comments/getatmelist"
#define API_COMMENTS_CHALLENGECOMMENT   "comments/challengecomment"
#define API_COMMENTS_CHALLENGEDEAL   "comments/challengedeal"
#define API_COMMENTS_CHALLENGEMELIST   "comments/challengemelist"
#define API_RANKINGS_IMPACTPOWER   "rankings/impactpower"
#define API_RANKINGS_LISTENPOWER   "rankings/listenpower"
#define API_RANKINGS_HOST   "rankings/host"
#define API_RANKINGS_FM   "rankings/fm"
#define API_MESSAGES_SEND   "messages/send"
#define API_MESSAGES_GETLIST   "messages/getlist"
#define API_MESSAGES_GETDETAILLIST   "messages/getdetaillist"
#define API_MESSAGES_REMOVE   "messages/remove"
#define API_MESSAGES_GETSYSTEMMSGLIST   "messages/getsystemmsglist"
#define API_MESSAGES_SETMESSAGEREAD   "messages/setmessageread"
#define API_MESSAGES_SETSYSMSGSTATUS   "messages/setsysmsgstatus"
#define API_MESSAGES_FORWARDMESSAGE   "messages/forwardmessage"
#define API_FEEDBACKS_GETLIST   "feedbacks/getlist"
#define API_FEEDBACKS_DEALFEEDBACK   "feedbacks/dealfeedback"
#define API_FEEDBACKS_REPLY   "feedbacks/reply"
#define API_FRIENDS_INVITE   "friends/invite"
#define API_FRIENDS_BATCHINVITE   "friends/batchinvite"
#define API_FRIENDS_AGREE   "friends/agree"
#define API_FRIENDS_DELETE   "friends/delete"
#define API_FRIENDS_GETLIST   "friends/getlist"
#define API_FRIENDS_GETINVITELIST   "friends/getinvitelist"
#define API_FRIENDS_SEARCH   "friends/search"
#define API_ITEMS_GETITEMLIST   "items/getitemlist"
#define API_ITEMS_GETPACKAGE   "items/getpackage"
#define API_ITEMS_GETPACKAGEALL   "items/getpackageall"
#define API_ITEMS_GETITEMLISTBYVOICE   "items/getitemlistbyvoice"
#define API_ITEMS_APPLYPACKAGEITEM   "items/applypackageitem"
#define API_ITEMS_BUYITEM   "items/buyitem"
#define API_ITEMS_BUY2APPLYITEM   "items/buy2applyitem"
#define API_ITEMS_APPLYVOICEITEM   "items/applyvoiceitem"
#define API_ITEMS_GETPICKINGLIST   "items/getpickinglist"
#define API_ITEMS_PICKUP   "items/pickup"
#define API_ITEMS_APPLYTOKENITEM   "items/applytokenitem"
#define API_ITEMS_ASKITEM   "items/askitem"
#define API_ITEMS_DONATEITEM   "items/donateitem"
#define API_ITEMS_GETLISTBYGROUP   "items/getlistbygroup"
#define API_ITEMS_GETITEMINFO   "items/getiteminfo"
#define API_ITEMS_BUYVCOLOR   "items/buyvcolor"
#define API_ITEMS_GETITEM   "items/getitem"
#define API_ITEMS_VIPLUCKYENTER   "items/vipluckyenter"
#define API_ITEMS_VIPLUCKYSTART   "items/vipluckystart"
#define API_ITEMS_VIPLUCKYEND   "items/vipluckyend"
#define API_ITEMS_VIPRULE   "items/viprule"
#define API_SHOPS_GETLIST   "shops/getlist"
#define API_SHOPS_BUY   "shops/buy"
#define API_SHOPS_ALIPAYBUY   "shops/alipaybuy"
#define API_SHOPS_ALIPAYVERIFY   "shops/alipayverify"
#define API_SHOPS_EASOUBUY   "shops/easoubuy"
#define API_SHOPS_EASOUVERIFY   "shops/easouverify"
#define API_STATISTICS_REPORTVOICELISTEN   "statistics/reportvoicelisten"
#define API_STATISTICS_GET   "statistics/get"
#define API_STATISTICS_REPORTLOCATION   "statistics/reportlocation"
#define API_STATISTICS_GETAPPLIST   "statistics/getapplist"
#define API_STATISTICS_REPORTAPPCLICK   "statistics/reportappclick"
#define API_STATISTICS_REPORTPUSHCALL   "statistics/reportpushcall"
#define API_STATISTICS_DUMP   "statistics/dump"
#define API_STATISTICS_REPORTVISIT   "statistics/reportvisit"
#define API_SUBJECTS_VIEW   "subjects/view"
#define API_SUBJECTS_GETSUBJECTLIST   "subjects/getsubjectlist"
#define API_SUBJECTS_GETQUESTIONLIST   "subjects/getquestionlist"
#define API_SUBJECTS_ASK   "subjects/ask"
#define API_TIPS_GETLIST   "tips/getlist"
#define API_TIPS_REPORT   "tips/report"
#define API_TIPS_DEAL   "tips/deal"
#define API_VOICEGEMS_GETVOICEGEM   "voicegems/getvoicegem"
#define API_VOICEGEMS_RECOMMEND   "voicegems/recommend"
#define API_PHOTOALBUM_GETCOMMENTLIST   "photoalbum/getcommentlist"
#define API_PHOTOALBUM_COMMENT   "photoalbum/comment"
#define API_PHOTOALBUM_RERECORD   "photoalbum/rerecord"
#define API_PHOTOALBUM_DELETECOMMENT   "photoalbum/deletecomment"
#define API_PHOTOALBUM_DELETEPHOTO   "photoalbum/deletephoto"
#define API_PHOTOALBUM_DELETEVOICE   "photoalbum/deletevoice"
#define API_PHOTOALBUM_SETCOMMENTREAD   "photoalbum/setcommentread"
#define API_PHOTOALBUM_THIRDPHOTO   "photoalbum/thirdphoto"
#define API_PHOTOALBUM_VIEW   "photoalbum/view"
#define API_ARGUES_SEARCH   "argues/search"
#define API_ARGUES_GETGEMLIST   "argues/getgemlist"
#define API_ARGUES_GETNEWBIELIST   "argues/getnewbielist"
#define API_ARGUES_GETNEWBIEWAITING   "argues/getnewbiewaiting"
#define API_ARGUES_GETNEWESTLIST   "argues/getnewestlist"
#define API_ARGUES_GETHOTTESTLIST   "argues/gethottestlist"
#define API_ARGUES_GETAUTOPLAYLIST   "argues/getautoplaylist"
#define API_ARGUES_GETCONDENSELIST   "argues/getcondenselist"
#define API_ARGUES_SIGNCOMMENT   "argues/signcomment"
#define API_ARGUES_DELETEVOICE   "argues/deletevoice"
#define API_ARGUES_GETATLIST   "argues/getatlist"
#define API_ARGUES_GETATLISTBYID   "argues/getatlistbyid"
#define API_ARGUES_GETQUESTIONSNEARBY   "argues/getquestionsnearby"
#define API_MMS_GETJOINLISTBYUSER   "mms/getjoinlistbyuser"
#define API_MMS_GETGEMLIST   "mms/getgemlist"
#define API_MMS_GETFRIENDJOINLIST   "mms/getfriendjoinlist"
#define API_MMS_GETPRIVATEMESSAGE   "mms/getprivatemessage"
#define API_MMS_SETMESSAGESREAD   "mms/setmessagesread"
#define API_MMS_GETSYSTEMMSGLIST   "mms/getsystemmsglist"
#define API_MMS_SETSYSTEMMSGREAD   "mms/setsystemmsgread"
#define API_MMS_GETGIFTLIST   "mms/getgiftlist"
#define API_MMS_SETFMESSAGESREAD   "mms/setfmessagesread"
#define API_THIRDSNS_THIRDFRIEND   "thirdsns/thirdfriend"
#define API_THIRDSNS_INVITEFRIEND   "thirdsns/invitefriend"
#define API_THIRDSNS_SHAREINFO   "thirdsns/shareinfo"
#define API_GUESS_GETLIST   "guess/getlist"
#define API_GUESS_GETMYLIST   "guess/getmylist"
#define API_GUESS_GUESSDETAIL   "guess/guessdetail"
#define API_GUESS_BET   "guess/bet"
#define API_CHANNELS_CREATE   "channels/create"
#define API_CHANNELS_GETCHANNELINFO   "channels/getchannelinfo"
#define API_CHANNELS_CHANGECHANNELINFO   "channels/changechannelinfo"
#define API_CHANNELS_ADDICON   "channels/addicon"
#define API_CHANNELS_DELETEICON   "channels/deleteicon"
#define API_CHANNELS_INVITE   "channels/invite"
#define API_CHANNELS_APPLY   "channels/apply"
#define API_CHANNELS_AGREE   "channels/agree"
#define API_CHANNELS_ADDFAVORITE   "channels/addfavorite"
#define API_CHANNELS_GETCHANNELLIST   "channels/getchannellist"
#define API_CHANNELS_TRANSFER   "channels/transfer"
#define API_CHANNELS_SETCHIEFMATE   "channels/setchiefmate"
#define API_CHANNELS_SETSECONDMATE   "channels/setsecondmate"
#define API_CHANNELS_KICKOUT   "channels/kickout"
#define API_CHANNELS_QUIT   "channels/quit"
#define API_CHANNELS_DUMB   "channels/dumb"
#define API_CHANNELS_SHOWINHOME   "channels/showinhome"
#define API_CHANNELS_GETCHATLIST   "channels/getchatlist"
#define API_CHANNELS_CHAT   "channels/chat"
#define API_CHANNELTOPICS_ASK   "channeltopics/ask"
#define API_CHANNELTOPICS_GETLIST   "channeltopics/getlist"
#define API_CHANNELTOPICS_GETHOTTESTLIST   "channeltopics/gethottestlist"
#define API_CHANNELTOPICS_VIEW   "channeltopics/view"
#define API_CHANNELTOPICS_ADDFAVORITE   "channeltopics/addfavorite"
#define API_CHANNELTOPICS_GETFAVORITELIST   "channeltopics/getfavoritelist"
#define API_CHANNELTOPICS_GEMTOPIC   "channeltopics/gemtopic"
#define API_CHANNELTOPICS_TOPTOPIC   "channeltopics/toptopic"
#define API_CHANNELTOPICS_TRANSPARENT   "channeltopics/transparent"
#define API_CHANNELTOPICS_RECOMMEND   "channeltopics/recommend"
#define API_CHANNELTOPICS_INVITEHOST   "channeltopics/invitehost"
#define API_CHANNELCOMMENTS_GETCOMMENTLIST   "channelcomments/getcommentlist"
#define API_CHANNELCOMMENTS_COMMENT   "channelcomments/comment"
#define API_CHANNELCOMMENTS_GETAUTOPLAYLIST   "channelcomments/getautoplaylist"
#define API_GAME_GETBLOW   "game/getblow"
#define API_GAME_GETGAMELIST   "game/getgamelist"
#define API_DONATES_HOME   "donates/home"
#define API_DONATES_STATUS   "donates/status"
#define API_DONATES_GENERATE_ACCESSTOKEN   "donates/generate_accesstoken"
#define API_DONATES_LIST_WISHES   "donates/list_wishes"
#define API_DONATES_DONATE   "donates/donate"
#define API_DONATES_ASK_WISH   "donates/ask_wish"
#define API_DONATES_NEXT_WISH   "donates/next_wish"
#define API_DONATES_CELEBRITY_RECOMMEND   "donates/celebrity_recommend"
#define API_DONATES_LIST_CELEBRITY   "donates/list_celebrity"
#define API_DONATES_APPLYITEM   "donates/applyitem"
#define API_DONATES_SHARE   "donates/share"
#define API_DONATES_THANKSREPLY   "donates/thanksreply"
#define API_DONATES_MOREGISTER   "donates/moregister"
#define API_DONATES_HISTORYREPLYLIST   "donates/historyreplylist"
#define API_DONATES_HISTORYREPLYDETAIL   "donates/historyreplydetail"
#define API_DONATES_LUCKDRAW   "donates/luckDraw"
#define API_FM_GETLIST   "fm/getlist"
#define API_FM_SEARCH   "fm/search"
#define API_FM_CREATE   "fm/create"
#define API_FM_VIEW   "fm/view"
#define API_FM_UPDATE   "fm/update"
#define API_FM_USERBLOCK   "fm/userblock"
#define API_FM_USERBLACKLIST   "fm/userblacklist"
#define API_FM_FAVORITEADD   "fm/favoriteadd"
#define API_FM_CHIEFTRANSFER   "fm/chieftransfer"
#define API_FM_FOLLOW   "fm/follow"
#define API_FM_MANAGE   "fm/manage"
#define API_FM_EDITBACKGROUND   "fm/editbackground"
#define API_FM_MEMBERS   "fm/members"
#define API_FM_ICONSETDEFAULT   "fm/iconsetdefault"
#define API_FM_ICONADD   "fm/iconadd"
#define API_FM_ICONDELETE   "fm/icondelete"
#define API_FM_GETGIFTLIST   "fm/getgiftlist"
#define API_FM_HOSTRECRUITLIST   "fm/hostrecruitlist"
#define API_FM_HOSTRECRUITCREATE   "fm/hostrecruitcreate"
#define API_FM_HOSTINVITE   "fm/hostinvite"
#define API_FM_HOSTINVITECONFIRM   "fm/hostinviteconfirm"
#define API_FM_HOSTAPPLY   "fm/hostapply"
#define API_FM_HOSTAPPLYCONFIRM   "fm/hostapplyconfirm"
#define API_FM_HOSTAPPLICANTS   "fm/hostapplicants"
#define API_FM_HOSTREMOVE   "fm/hostremove"
#define API_FM_HOSTSETROLE   "fm/hostsetrole"
#define API_FM_HOSTREWARD   "fm/hostreward"
#define API_FM_HOSTSETPHOTO   "fm/hostsetphoto"
#define API_FM_REVENUES   "fm/revenues"
#define API_FMTOPICS_GETLIST   "fmtopics/getlist"
#define API_FMTOPICS_CREATE   "fmtopics/create"
#define API_FMTOPICS_SETTOP   "fmtopics/settop"
#define API_FMTOPICS_DELETE   "fmtopics/delete"
#define API_FMCOMMENTS_GETLIST   "fmcomments/getlist"
#define API_FMCOMMENTS_GETATMELIST   "fmcomments/getatmelist"
#define API_FMCOMMENTS_CREATE   "fmcomments/create"
#define API_FMCOMMENTS_RECOMMEND   "fmcomments/recommend"
#define API_FMCOMMENTS_SETTRANSPARENT   "fmcomments/settransparent"
#define API_FEEDS_FOLLOW   "feeds/follow"
#define API_FEEDS_FOLLOWBATCH   "feeds/followbatch"
#define API_FEEDS_BYPASS   "feeds/bypass"
#define API_FEEDS_GETFOLLOWLIST   "feeds/getfollowlist"
#define API_FEEDS_GETPUSHLIST   "feeds/getpushlist"
#define API_FEEDS_GETBYPASSLIST   "feeds/getbypasslist"
#define API_FEEDS_MORE   "feeds/more"
#define API_FEEDS_GETINLIST   "feeds/getinlist"
#define API_FEEDS_GETOUTLIST   "feeds/getoutlist"
#define API_FEEDS_UP   "feeds/up"
#define API_FEEDS_GETUPLIST   "feeds/getuplist"
#define API_HOME_SQUARE   "home/square"
#define API_HOME_PHOTOLIST   "home/photolist"
#define API_DIALECT_DLHOSTLIST   "dialect/dlhostlist"
#define API_DIALECT_DLCHECKINLIST   "dialect/dlcheckinlist"
#define API_DIALECT_DLCHECKIN   "dialect/dlcheckin"
#define API_DIALECT_DLSETMYDIALECT   "dialect/dlsetmydialect"
#define API_DIALECT_PUSHMSG   "dialect/pushmsg"
#define API_DIALECT_PROHIBITSEND   "dialect/prohibitsend"
#define API_MEDALS_GETURL   "medals/geturl"

# endif
