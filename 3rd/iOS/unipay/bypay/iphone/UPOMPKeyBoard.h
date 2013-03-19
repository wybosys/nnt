//
//  UPOMPKeyBoard.h
//  UPOMP
//
//  Created by pei xunjun on 11-8-15.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AudioToolbox/AudioToolbox.h>
@class UPOMP;
@class UPOMP_CPCell;
typedef enum UPOMP_KeyBoardIndex {
	CP_KeyBoard_Default,
	CP_KeyBoard_Delect,
	CP_KeyBoard_BIG,
	CP_KeyBoard_Num,
	CP_KeyBoard_Text,
	CP_KeyBoard_Other,
	CP_KeyBoard_OK
} UPOMP_KeyBoardIndex;

@class UPOMPKeyBoardItem;
@class UPOMPKeyBoardBgView;
@class UPOMPKeyItem;
@interface UPOMPKeyBoard : UIView{
	NSMutableArray *keys;
	NSMutableArray *drawKeys;
	UPOMPKeyBoardBgView *bgView;
	UPOMP *mainView;
	bool isSecure;
	bool onlyNum;
	BOOL isBig;
	int keyBoardIndex;
	UPOMP_CPCell *cell;
	int fieldLenght;
	int animationIndex;
	UPOMPKeyBoardItem *numkey;
	UPOMPKeyBoardItem *textkey;
	UPOMPKeyBoardItem *otherkey;
	UPOMPKeyBoardItem *okkey;
	int spaceWeight;
	int boardType;
	bool isUP;
	BOOL isLast;
	BOOL nodown;
}
-(void)playSound;
- (id)initWithFieldLenght:(int)length cell:(UPOMP_CPCell*)c isSecure:(BOOL)secure onlyNum:(BOOL)isNum mainView:(UPOMP*)mView;
-(void)keyBoardUP;
-(void)keyBoardDown;
-(void)setKeyBoardIndex:(int)index;
-(void)action:(int)keyIndex value:(NSString*)str;
-(void)touchDown;
@property int spaceWeight;
@property int boardType;
@property BOOL isBig;
@property BOOL isLast;
@property BOOL nodown;
@property(nonatomic,readonly)NSMutableArray *drawKeys;
@end

@interface UPOMPKeyBoardBgView : UIView {
	UPOMPKeyBoard *keyBoard;
	int selectKey;
	bool outsite;
}
- (id)initWithFrame:(CGRect)frame keyboard:(UPOMPKeyBoard*)kboard;
@property int selectKey;
@end

@interface UPOMPKeyBoardItem : UIButton {
	UPOMPKeyBoard *keyboard;
	NSString *value;
	int type;
	int index;
}
- (id)initWithFrame:(CGRect)frame keyboard:(UPOMPKeyBoard*)kboard value:(NSString*)str;
@property int type;
@property int index;
@property(nonatomic,retain) NSString *value;
@end
@interface UPOMPKeyItem : NSObject {
	CGRect frame;
	NSString *value;
	UPOMPKeyBoard *keyBoard;
	NSString *imageName;
	BOOL isSelect;
}
- (id) initWithFrame:(CGRect)rect keyboard:(UPOMPKeyBoard*)kboard value:(NSString*)str imageName:(NSString*)imgName;
- (void)draw;
@property CGRect frame;
@property(nonatomic,retain) NSString *value;
@property BOOL isSelect;
@end
