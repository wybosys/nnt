
# ifndef __WSI_PARSER_HTMLNODE_4B04F6FD2E5449E58C9CEF67C8F94FBF_H_INCLUDED
# define __WSI_PARSER_HTMLNODE_4B04F6FD2E5449E58C9CEF67C8F94FBF_H_INCLUDED

# import "../../3rd/Mac/HTML/HTMLNode.h"

WSI_BEGIN_HEADER_OBJC

@interface HTMLNode (WSI)

- (HTMLNode*)findChildByName:(NSString*)name;
- (HTMLNode*)nextSiblingByName:(NSString*)name;
- (NSString*)getAttributeNamed:(NSString*)name enc:(NSStringEncoding)enc;

@end

WSIDECL_CATEGORY(HTMLNode, WSI);

WSI_END_HEADER_OBJC

# endif