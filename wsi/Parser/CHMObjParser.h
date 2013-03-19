
# ifndef __WSI_PARSER_CHMOBJPARSER_02E0F2E14C134869AEF8C9EA8F5EE91A_H_INCLUDED
# define __WSI_PARSER_CHMOBJPARSER_02E0F2E14C134869AEF8C9EA8F5EE91A_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(CHMObjParser);

@interface CHMTree : WSIObject {
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

@interface CHMObjParser : WSIObject {
    
    CHMTree *tree;
    
    WSIDECL_PRIVATE(CHMObjParser);
}

@property (nonatomic, readonly) CHMTree *tree;

- (BOOL)loadFile:(NSString*)file;
- (NSData*)loadTarget:(NSString*)tgt;
- (CFStringEncoding)encoding;

@end

WSI_END_HEADER_OBJC

# endif