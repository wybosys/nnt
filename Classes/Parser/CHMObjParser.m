
# import "Core.h"
# import "CHMObjParser.h"
# import "CHMParser.h"
# import "HTMLNode+NNT.h"

NNT_BEGIN_OBJC

int func_enum(chm_t *chm, chm_unitinfo *ui, void *context);
int func_load_file(chm_t *chm, chm_unitinfo *ui, void *context);

NNTUSE_CATEGORY(HTMLNode, NNT);

@implementation CHMTree

@synthesize isTree, name, local, image, children;

- (id)init {
    self = [super init];
    children = [NSMutableArray new];
    return self;
}

- (void)dealloc {
    zero_release(name);
    zero_release(local);
    zero_release(image);
    zero_release(children);
    [super dealloc];
}

- (void)clear {
    [children removeAllObjects];
}

@end

@interface CHMObjParserPrivate : NSObject {
    CHMObjParser *d_owner;
    
    chm_t *chm;
    FILE *fd;
    
    CHMTree *tree;
}

@property (nonatomic, assign) CHMObjParser *d_owner;
@property (nonatomic, assign) chm_t *chm;
@property (nonatomic, assign) FILE *fd;
@property (nonatomic, retain) CHMTree *tree;

- (void)open;
- (void)close;
- (void)load_tree;

- (CHMTree*)load_li:(HTMLNode*)node;

@end

@implementation CHMObjParserPrivate

@synthesize d_owner;
@synthesize chm, fd;
@synthesize tree;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    [self close];    
    zero_release(tree);
    [super dealloc];
}

- (void)open {
    chm = (chm_t*)malloc(sizeof(chm_t));
    chm_init(chm);    
}

- (void)close {
    if (chm) {
        chm_free(chm);
        free(chm);
        chm = NULL;
    }
    
    if (fd) {
        fclose(fd);
        fd = 0;
    }
}

int func_enum(chm_t *chm, chm_unitinfo *ui, void *context) {
	if((ui->flags & CHM_ENUMERATE_NORMAL) && (ui->flags & CHM_ENUMERATE_FILES)) {
        char *path = ui->path;
        size_t len = strlen(path);
        if (len >= 4) {
            if (memcmp(path + len - 4, ".hhc", 4) == 0) {
                NSMutableData **pdata = (NSMutableData **)context;
                *pdata = [[NSMutableData alloc] initWithCapacity:9126];
                
                // load file
                byte buffer[9126];
                uqword offset = 0;
                uqword remain = ui->length;
                while (remain) {
                    uqword len = chm_retrieve_object(chm, ui, buffer, offset, 9126);
                    [*pdata appendBytes:buffer length:len];
                    offset += len;
                    remain -= len;
                }
                
                return CHM_ENUMERATOR_SUCCESS;
            }
        }
    }
    return CHM_ENUMERATOR_CONTINUE;
}

- (void)load_tree {
    [tree release];
    
    // load hhc files
    NSMutableData *data = nil;
    chm_enumerate(chm, CHM_ENUMERATE_ALL, func_enum, &data);
    
    if (data) {
        NSError *err = nil;        
        HTMLParser *html = [[HTMLParser alloc] initWithData:data error:&err cenc:CFStringEncodingFromWindowsLocaleCode(chm->itsf.lang_id)];
        if (err == nil) {
            HTMLNode *body = [html body];
            HTMLNode *ul = [body findChildByName:@"ul"];
            while (ul) {                
                HTMLNode *li = [ul findChildByName:@"li"];
                if (li) {                
                    CHMTree *child = [self load_li:li];
                    tree = [child retain];
                }                
                ul = [ul nextSiblingByName:@"li"];
            }
        }        
        [html release];
        [data release];
    }
}

- (CHMTree*)load_li:(HTMLNode *)node {
    HTMLNode *obj = [node findChildTag:@"object"];
    CHMTree *ret = [[CHMTree alloc] init];
    HTMLNode *name = [obj findChildByName:@"param"];
    HTMLNode *local = [name nextSiblingByName:@"param"];
    HTMLNode *image = [local nextSiblingByName:@"param"];
    ret.name = [name getAttributeNamed:@"value"];
    ret.local = [local getAttributeNamed:@"value"];
    ret.image = [image getAttributeNamed:@"value"];
    HTMLNode *ul = [node findChildByName:@"ul"];
    if (ul) {
        ret.isTree = YES;
        HTMLNode *li = [ul findChildByName:@"li"];
        while (li) {
            CHMTree *child = [self load_li:li];
            [ret.children addObject:child];
            li = [li nextSiblingByName:@"li"];
        }
    } else {
        ret.isTree = NO;
    }
    return [ret autorelease];
}

@end

@implementation CHMObjParser

@dynamic tree;

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT(CHMObjParser);
    return self;
}

- (void)dealloc {
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (BOOL)loadFile:(NSString *)file {
    [d_ptr close];
    
    d_ptr.fd = fopen([file UTF8String], "r");
    if (!(d_ptr.fd > 0))
        return NO;
    
    [d_ptr open];
    
    bool suc = chm_read(d_ptr.chm, d_ptr.fd);
    
    if (suc) {
        [d_ptr load_tree];
    }
    
    return suc;
}

- (CHMTree*)tree {
    return d_ptr.tree;
}

int func_load_file(chm_t *chm, chm_unitinfo *ui, void *context) {
    if (ui->flags & CHM_ENUMERATE_FILES) {
        char *path = ui->path;
        NSString *str_path = [NSString stringWithUTF8String:path];
        NSPair *pair = (NSPair*)context;
        NSString *str_tgt = pair.first;
        if ([str_tgt rangeOfString:str_path].location != NSNotFound) {
            // read data
            NSMutableData **pdata = ((NSPointer*)pair.second).addr;            
            *pdata = [[NSMutableData alloc] initWithCapacity:9126];
                    
            // load file
            byte buffer[9126];
            uqword offset = 0;
            uqword remain = ui->length;
            while (remain) {
                uqword len = chm_retrieve_object(chm, ui, buffer, offset, 9126);
                [*pdata appendBytes:buffer length:len];
                offset += len;
                remain -= len;
            }
                    
            return CHM_ENUMERATOR_SUCCESS;
        }
    }
    return CHM_ENUMERATOR_CONTINUE;
}

- (NSData*)loadTarget:(NSString *)tgt {
    NSData *ret = nil;
    tgt = [NSString stringWithFormat:@"/%@", tgt];
    NSPair *pair = [NSPair pairWith:tgt second:[NSPointer pointerWithAddr:&ret]];
    chm_enumerate(d_ptr.chm, CHM_ENUMERATE_NORMAL, func_load_file, pair);
    return [ret autorelease];
}

- (CFStringEncoding)encoding {
    return CFStringEncodingFromWindowsLocaleCode(d_ptr.chm->itsf.lang_id);
}

@end

NNT_END_OBJC