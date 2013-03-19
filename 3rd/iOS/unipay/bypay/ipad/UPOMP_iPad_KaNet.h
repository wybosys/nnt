//
//  KaNet.h
//  mylibs
//
//  Created by pei xunjun on 11-11-7.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class UPOMP_iPad_View;

@protocol UPOMP_iPad_KaNetDelegate<NSObject>
@required
-(void)netError:(NSError*)error;
-(void)netFinish:(NSData*)data;
@end

@interface UPOMP_iPad_KaNet : NSObject {
	NSMutableData *netData;
	NSMutableURLRequest *request;
	NSURLConnection *conn;
	UPOMP_iPad_View *cpView;
	NSMutableString *key;
	BOOL isImage;
    NSTimer *timer;
    BOOL hasTimer;
}
- (id)initWithView:(UPOMP_iPad_View*)view;
- (void)start:(NSData*)data URL:(NSString*)url;
- (void)cancel;
-(void)getImageByURL:(NSString*)url otherURL:(NSString*)otherURL;

@property(readonly)BOOL netComplete;
@property (nonatomic, assign) id <UPOMP_iPad_KaNetDelegate> netDelegate;
@end
