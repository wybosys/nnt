//
//  CPNet.h
//  ChinaUnionPay
//
//  Created by Anplex on 11-6-23.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UPOMPView.h"

@interface UPOMP_CPNet : NSObject {
	UPOMP_CPView *cpview;
	NSMutableData *netData;
	NSMutableURLRequest *request;
	NSURLConnection *conn;
	bool hasNoLoading;
	bool isComplete;
    BOOL hasTimer;
	NSString *desKey;
    NSTimer *timer;
}
-(id)initByNetView:(UPOMP_CPView*)nView;
-(void)startNetData:(NSData*)data URL:(NSString *)url;
+(NSData*)setPostDataByAppName:(NSString*)appName 
						  keys:(NSArray*)keys 
						values:(NSArray*)values 
					netVersion:(NSString *)netversion
				   anotherInfo:(NSString *)anotherStr;
-(void)cancel;
@property bool hasNoLoading;
@property bool isComplete;
@end
