//
//  DataSigner.m
//  AlixPayDemo
//
//  Created by Jing Wen on 8/2/11.
//  Copyright 2011 alipay.com. All rights reserved.
//

#import "DataSigner.h"
#import "src/RSADataSigner.h"
#import "src/MD5DataSigner.h"

id<DataSigner> CreateRSADataSigner(NSString *privateKey) {
	id signer = nil;
	signer = [[RSADataSigner alloc] initWithPrivateKey:privateKey];
	return [signer autorelease];
	
}
