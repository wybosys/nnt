
# import "Core.h"
# import "HTMLNode+NNT.h"

NNT_BEGIN_OBJC

NSString * getAttributeNamedEnc(xmlNode * node, const char * nameStr, NSStringEncoding enc);
NSString * getAttributeNamedEnc(xmlNode * node, const char * nameStr, NSStringEncoding enc) {
	for(xmlAttrPtr attr = node->properties; NULL != attr; attr = attr->next)
	{
		if (strcmp((char*)attr->name, nameStr) == 0)
		{				
			for(xmlNode * child = attr->children; NULL != child; child = child->next)
			{
				return [NSString stringWithCString:(void*)child->content encoding:enc];				
			}
			break;
		}
	}	
	return NULL;
}

@implementation HTMLNode (NNT)

- (HTMLNode*)findChildByName:(NSString *)name {
    xmlNode *child = _node->children;
    while (child && ![[NSString stringWithUTF8String:(char*)child->name] isEqualToString:name]) {
        child = child->next;
    }
    if (child == NULL)
        return nil;
    return [[[HTMLNode alloc] initWithXMLNode:child] autorelease];
}

- (HTMLNode*)nextSiblingByName:(NSString *)name {
    xmlNode *next = _node->next;
    while (next && ![[NSString stringWithUTF8String:(char*)next->name] isEqualToString:name]) {
        next = next->next;
    }
    if (next == NULL)
        return nil;
    return [[[HTMLNode alloc] initWithXMLNode:next] autorelease];
}

- (NSString*)getAttributeNamed:(NSString*)name enc:(NSStringEncoding)enc {	
	const char * nameStr = [name UTF8String];	
	return getAttributeNamedEnc(_node, nameStr, enc);
}

@end

NNTIMPL_CATEGORY(HTMLNode, NNT);

NNT_END_OBJC