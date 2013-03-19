//
//  KaTabItem.h
//  KaSpace
//
//  Created by pei xunjun on 11-7-19.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UPOMP_iPad_KaTabItem : NSObject {
	//背景图片
	UIImage *bgImage;
	//选中时图片
	UIImage *selectedImage;
	//是否被选中
	BOOL isSelected;
	//元素大小
	CGRect frame;
	//元素文字标题
	NSString *titel;
	//标题字体
	UIFont *titelFont;
	//标题 字符超出后显示模式
	UILineBreakMode titelLineBreakMode;
	//标题 显示样式
	UITextAlignment titelAlignment;
	//标题颜色
	UIColor *titelColor;
	//标题选中时的颜色
	UIColor *selectedColor;
}
- (void)draw;
- (id) initWithRect:(CGRect)rect;
- (void)setBGImage:(UIImage*)bgImg selectedImage:(UIImage*)seletedImg;
- (void)setTitelFont:(UIFont*)font;
- (void)setTitel:(NSString*)str;
- (void)setTitelLineBreakMode:(UILineBreakMode)mode;
- (void)setTitelAlignment:(UITextAlignment)alignment;
- (void)setTitelColor:(UIColor*)color;
- (void)setSelectedColor:(UIColor*)color;
@property BOOL isSelected;
@end
