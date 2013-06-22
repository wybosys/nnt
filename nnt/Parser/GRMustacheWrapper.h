
# ifndef __NNT_GRMUSTACHEWRAPPER_9F5ACFA363A748C9B7D53EB908A0EF83_H_INCLUDED
# define __NNT_GRMUSTACHEWRAPPER_9F5ACFA363A748C9B7D53EB908A0EF83_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface GRMustacheTemplateRender : NSObject {
    GRMustacheTemplate *tpl;
}

@property (nonatomic, retain) GRMustacheTemplate *tpl;

- (NSString*)renderObject:(id)obj;

@end

@interface GRMustacheTemplateRender (private)

- (NSString *)renderContext:(GRMustacheContext *)context;

@end

NNT_END_HEADER_OBJC

# endif