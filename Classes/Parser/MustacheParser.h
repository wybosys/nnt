
# ifndef __WSI_PARSER_MUSTACHEPARSER_9056CFE6C85A48958AA908FE2EFDC890_H_INCLUDED
# define __WSI_PARSER_MUSTACHEPARSER_9056CFE6C85A48958AA908FE2EFDC890_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(MustacheParser);

@interface MustacheParser : WSIObject {
    
    WSIDECL_PRIVATE(MustacheParser);
}

//! init.
- (id)init;
- (id)initWithTemplate:(NSString*)tpl;

//! construction.
+ (id)parserWithTemplate:(NSString*)tpl;
+ (id)parserNamed:(NSString*)file;

//! set template.
- (BOOL)loadTemplate:(NSString*)tpl;

//! render object.
- (NSString*)renderObject:(id)obj;

@end

WSI_END_HEADER_OBJC

# endif