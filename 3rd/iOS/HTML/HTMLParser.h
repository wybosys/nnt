//
//  HTMLParser.h
//  StackOverflow
//
//  Created by Ben Reeves on 09/03/2010.
//  Copyright 2010 Ben Reeves. All rights reserved.
//

//  wybosys
//  add encoding function to support gb18030 and others.
//  wybosys@gmail.com 2011
//

#import <Foundation/Foundation.h>
#import <libxml/HTMLparser.h>
#import "HTMLNode.h"

@class HTMLNode;

@interface HTMLParser : NSObject 
{
	@public
	htmlDocPtr _doc;
}

-(id)initWithContentsOfURL:(NSURL*)url error:(NSError**)error;
-(id)initWithData:(NSData*)data error:(NSError**)error;
-(id)initWithData:(NSData*)data error:(NSError**)error enc:(NSStringEncoding)enc;
-(id)initWithData:(NSData*)data error:(NSError**)error cenc:(CFStringEncoding)cenc;
-(id)initWithString:(NSString*)string error:(NSError**)error;

//Returns the doc tag
-(HTMLNode*)doc;

//Returns the body tag
-(HTMLNode*)body;

//Returns the html tag
-(HTMLNode*)html;

@end
