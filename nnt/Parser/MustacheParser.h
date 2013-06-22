
# ifndef __NNT_PARSER_MUSTACHEPARSER_9056CFE6C85A48958AA908FE2EFDC890_H_INCLUDED
# define __NNT_PARSER_MUSTACHEPARSER_9056CFE6C85A48958AA908FE2EFDC890_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(MustacheParser);

@interface MustacheParser : NNTObject {
    
    NNTDECL_PRIVATE(MustacheParser);
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

NNT_END_HEADER_OBJC

# endif