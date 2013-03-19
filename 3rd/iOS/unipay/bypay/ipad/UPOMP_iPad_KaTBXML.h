//
//  KaXML.h
//  mylibs
//
//  Created by pei xunjun on 11-11-5.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#define UPOMP_iPad_MAX_ELEMENTS 100
#define UPOMP_iPad_MAX_ATTRIBUTES 100

#define UPOMP_iPad_TBXML_ATTRIBUTE_NAME_START 0
#define UPOMP_iPad_TBXML_ATTRIBUTE_NAME_END 1
#define UPOMP_iPad_TBXML_ATTRIBUTE_VALUE_START 2
#define UPOMP_iPad_TBXML_ATTRIBUTE_VALUE_END 3
#define UPOMP_iPad_TBXML_ATTRIBUTE_CDATA_END 4

typedef struct _UPOMP_iPad_TBXMLAttribute {
	char * name;
	char * value;
	struct _UPOMP_iPad_TBXMLAttribute * next;
} UPOMP_iPad_TBXMLAttribute;

typedef struct _UPOMP_iPad_TBXMLElement {
	char * name;
	char * text;
	UPOMP_iPad_TBXMLAttribute * firstAttribute;
	struct _UPOMP_iPad_TBXMLElement * parentElement;
	struct _UPOMP_iPad_TBXMLElement * firstChild;
	struct _UPOMP_iPad_TBXMLElement * currentChild;
	struct _UPOMP_iPad_TBXMLElement * nextSibling;
	struct _UPOMP_iPad_TBXMLElement * previousSibling;
} UPOMP_iPad_TBXMLElement;

typedef struct _UPOMP_iPad_TBXMLElementBuffer {
	UPOMP_iPad_TBXMLElement * elements;
	struct _UPOMP_iPad_TBXMLElementBuffer * next;
	struct _UPOMP_iPad_TBXMLElementBuffer * previous;
} UPOMP_iPad_TBXMLElementBuffer;

typedef struct _UPOMP_iPad_TBXMLAttributeBuffer {
	UPOMP_iPad_TBXMLAttribute * attributes;
	struct _UPOMP_iPad_TBXMLAttributeBuffer * next;
	struct _UPOMP_iPad_TBXMLAttributeBuffer * previous;
} UPOMP_iPad_TBXMLAttributeBuffer;


@interface UPOMP_iPad_KaTBXML : NSObject {
	UPOMP_iPad_TBXMLElement * rootXMLElement;
	UPOMP_iPad_TBXMLElementBuffer * currentElementBuffer;
	UPOMP_iPad_TBXMLAttributeBuffer * currentAttributeBuffer;
	long currentElement;
	long currentAttribute;
	char * bytes;
	long bytesLength;
}
- (id)initWithXMLData:(NSData*)aData;
- (NSString*) elementName:(UPOMP_iPad_TBXMLElement*)aXMLElement;
- (NSString*) textForElement:(UPOMP_iPad_TBXMLElement*)aXMLElement;
- (NSString*) valueOfAttributeNamed:(NSString *)aName forElement:(UPOMP_iPad_TBXMLElement*)aXMLElement;

- (UPOMP_iPad_TBXMLElement*) getRootXMLElement;
- (UPOMP_iPad_TBXMLElement*) nextSiblingNamed:(NSString*)aName searchFromElement:(UPOMP_iPad_TBXMLElement*)aXMLElement;
- (UPOMP_iPad_TBXMLElement*) childElementNamed:(NSString*)aName parentElement:(UPOMP_iPad_TBXMLElement*)aParentXMLElement;

@end
