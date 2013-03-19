
# ifndef __NNT_PARSER_HTMLNODE_4B04F6FD2E5449E58C9CEF67C8F94FBF_H_INCLUDED
# define __NNT_PARSER_HTMLNODE_4B04F6FD2E5449E58C9CEF67C8F94FBF_H_INCLUDED

# import "../../3rd/Mac/HTML/HTMLNode.h"

NNT_BEGIN_HEADER_OBJC

@interface HTMLNode (NNT)

- (HTMLNode*)findChildByName:(NSString*)name;
- (HTMLNode*)nextSiblingByName:(NSString*)name;
- (NSString*)getAttributeNamed:(NSString*)name enc:(NSStringEncoding)enc;

@end

NNTDECL_CATEGORY(HTMLNode, NNT);

NNT_END_HEADER_OBJC

# endif