//
//  IFlySynthesizerControl.h
//
//  Description: 语言合成控件
//
//  Created by 陈阳 on 11-2-23.
//  Copyright 2011 iFLYTEK. All rights reserved.
//
//	Important History:
//	index	version		date		author		notes
//	0		1.0.0		2011/2/23	yangchen	创建文件

#import <UIKit/UIKit.h>

#define SpeechError int

#define PLAYPROGRESS    0
#define BUFFERPROGRESS  1

@class IFlySynthesizerControl;
@class IFlySynthesizerControlImp;

@protocol IFlySynthesizerControlDelegate

/*
	 @function	onSynthesizerEnd
	 @abstract	合成结束回调
	 @discussion	
	 @param	
*/
- (void)onSynthesizerEnd:(IFlySynthesizerControl *)iFlySynthesizerControl theError:(SpeechError) error;

//xlhou add 20120305
- (void)onSynthesizerBufferProgress:(float)bufferProgress;

- (void)onSynthesizerPlayProgress:(float)playProgress;


//-(void)onSynthesizeProgress:(int)State progress:(float)progress;


@end

@interface IFlySynthesizerControl : UIView 
{
	// 实现部分
	IFlySynthesizerControlImp			*_iFlySynthesizerControlImp;
	
	// 接口
	id<IFlySynthesizerControlDelegate>	_delegate;
}

@property(assign)id<IFlySynthesizerControlDelegate> delegate;

/*
	@function	initWithOrigin
	@abstract	初始化
	@discussion	
	@param		initParam:appID－使用令牌，需要到科大讯飞云网站上申请
*/
- (id)initWithOrigin:(CGPoint)origin initParam:(NSString *)initParam;

/*
	@function	setText
	@abstract	设置合成文本
	@discussion	
	@param		text -	待合成的文本 
                theParams － 设置引擎参数，“ent=引擎参数”，无特殊需要可设为nil
*/
- (void)setText:(NSString *)text params:(NSString *)params;

/*
	 @function	setSampleRate
	 @abstract	设置合成音频采样率
	 @discussion	
	 @param		仅支持8k、16k，设置错误或不设置会默认用16k	
*/
- (void)setSampleRate:(int)rate;

/*
	 @function	setShowUI
	 @abstract	设置是否显示合成界面
	 @discussion	
	 @param		param - YES 显示 - NO 不显示 默认显示
*/
- (void)setShowUI:(BOOL)param; 

/*
	 @function	setBackgroundSound
	 @abstract	设置背景音
	 @discussion	
	 @param		param - 默认为null，表示无背景音乐
*/
- (void)setBackgroundSound:(NSString *)param; 

/*
	 @function	setVoiceName
	 @abstract	设置发音人
	 @discussion	
	 @param		name - 可设置为:"xiaoyan","xiaoyu",默认为"xiaoyan"
*/
- (void)setVoiceName:(NSString *)name;

/*
	 @function	setSpeed
	 @abstract	设置语速
	 @discussion	
	 @param		param 范围:0-10,默认5
*/
- (void)setSpeed:(unsigned int)speed;

/*
	 @function	setVolume
	 @abstract	设置音量
	 @discussion	
	 @param		param 范围:0-100,默认50
*/
- (void)setVolume:(unsigned int)volume; 

/*
	 @function	start
	 @abstract	开始合成
	 @discussion	
*/
- (BOOL)start;

/*
	@function	cancel
	@abstract	取消合成
	@discussion	
	@param	
*/
- (void)cancel;


/*
	 @function	pause
	 @abstract	暂停播放
	 @discussion	
	 @param	
*/
- (void)pause;

/*
	 @function	resume
	 @abstract	恢复播放
	 @discussion	
	 @param	
*/
- (void)resume;

/*
	 @function	getUpflow
	 @abstract	查询流量
	 @discussion	
     @param		isTotal - TRUE：反馈自从初始化以来的所有上传流量 ，FALSE：反馈本次会话的上传流量
     @return    -1 ：查询失败 ， 其他值：流量字节
*/
- (int)getUpflow:(BOOL) isTotal;


/*
    @function	getDownflow
    @abstract	查询流量
    @discussion	
    @param         isTotal - TRUE：反馈自从初始化以来的所有下载流量 ，FALSE：反馈本次会话的下载流量
    @return        -1 ：查询失败 ，其他值：流量字节
 */
- (int)getDownflow:(BOOL) isTotal;


/*
 @function	replay
 @abstract	重新播放
 @discussion	
 @param		
 */
- (void) replay;


/*
	 @function	getErrorDescription
	 @abstract	根据错误码获取错误描述
	 @discussion	
	 @param		返回错误描述
*/
- (NSString *)getErrorDescription:(SpeechError)errorCode;

/*
 @function:      setShowLog
 @abstract:      设置是否控制台打印log
 @discussion:	
 @param:         
 */
- (void) setShowLog:(BOOL)param;
/*
    @function: getVersion
    @abstract: 获取版本号
    @discussion:
    @param:
    @return :  返回SDK的版本号
 */
- (NSString *) getVersion;
@end
