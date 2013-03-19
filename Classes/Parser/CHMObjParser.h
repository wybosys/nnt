
# ifndef __NNT_PARSER_CHMOBJPARSER_02E0F2E14C134869AEF8C9EA8F5EE91A_H_INCLUDED
# define __NNT_PARSER_CHMOBJPARSER_02E0F2E14C134869AEF8C9EA8F5EE91A_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(CHMObjParser);

@interface CHMTree : NNTObject {
    BOOL isTree;
    NSString *name;
    NSString *local;
    NSString *image;
    NSMutableArray *children;
}

@property (nonatomic, assign) BOOL isTree;
@property (nonatomic, copy) NSString *name, *local, *image;
@property (nonatomic, retain) NSMutableArray *children;

- (void)clear;

@end

@interface CHMObjParser : NNTObject {
    
    CHMTree *tree;
    
    NNTDECL_PRIVATE(CHMObjParser);
}

@property (nonatomic, readonly) CHMTree *tree;

- (BOOL)loadFile:(NSString*)file;
- (NSData*)loadTarget:(NSString*)tgt;
- (CFStringEncoding)encoding;

@end

NNT_END_HEADER_OBJC

# endif