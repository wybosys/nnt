
# import "Core.h"
# import "FileCache.h"
# import "Directory+WSI.h"
//# import <Google/GDataXMLNode.h>
# import "coretypes.h"
# import "XmlParser.h"

WSI_BEGIN_OBJC

@interface CacheItemArrayFileCache : CacheItem
@end

@interface CacheItemPairFileCache : CacheItem
@end

@interface CacheItemStringFileCache : CacheItem
@end

@interface CacheItemDictionaryFileCache : CacheItem
@end

@interface CacheItemDataFileCache : CacheItem 
@end

@implementation AbstractUrlCache

@synthesize url;

- (id)initWithPath:(NSString *)path type:(WSIDirectoryType)type {
    self = [super init];
        
    self.url = WSIDirectoryCreateWithType(path, type);
    
    return self;
}

- (void)dealloc {
    zero_release(url);
    [super dealloc];
}

@end

@interface FileCachePrivate : NSObject {
    //! cache directory.
    NSString *str_path;
    
    //! type of directory.
    WSIDirectoryType dir_type;
    
    //! filesystem manager.
    NSFileManager *fs_mgr;
    
    FileCache *d_owner;
}

@property (nonatomic, assign) FileCache *d_owner;
@property (nonatomic, copy) NSString *str_path;
@property (nonatomic, assign) WSIDirectoryType dir_type;
@property (nonatomic, assign) NSFileManager *fs_mgr;

@end

@implementation FileCachePrivate

@synthesize d_owner;
@synthesize str_path, dir_type;
@synthesize fs_mgr;

- (id)init {
    self = [super init];
    
    dir_type = WSIDirectoryTypeNone;
    fs_mgr = [NSFileManager defaultManager];
    
    return self;
}

- (void)dealloc {
    zero_release(str_path);
    [super dealloc];
}

@end

@interface FileCache ()

- (void)__init;

@end

@implementation FileCache

@synthesize indexFile;

- (void)__init {
    WSIDECL_PRIVATE_INIT(FileCache);
    
    self.indexFile = @"index.xml";
}

- (id)init {
    self = [super init];
    [self __init];
    return self;
}

- (id)initWithPath:(NSString *)path type:(WSIDirectoryType)type {
    self = [super initWithPath:path type:type];        
    [self __init];
    
    d_ptr.str_path = path;
    d_ptr.dir_type = type;
    
    return self;
}

- (void)dealloc {
    zero_release(indexFile);
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (Class)classCacheItem:(id<NSObject>)obj {
    Class ret = nil;
    switch ([(NSObject*)obj coreType]) {
        default: {
# ifdef WSI_DEBUG
            NSString *msg = [NSString stringWithFormat:@"cache warning: caching a [%s] class object", object_getClassName(obj)];
            trace_msg(msg);
# endif
        } break;
        case CoreTypeArray: ret = [CacheItemArrayFileCache class]; break;
        case CoreTypePair: ret = [CacheItemPairFileCache class]; break;
        case CoreTypeDictionary: ret = [CacheItemDictionaryFileCache class]; break;
        case CoreTypeString: ret = [CacheItemStringFileCache class]; break;
        case CoreTypeData: ret = [CacheItemDataFileCache class]; break;
    }
    return ret;
}

- (void)clear {        
    NSArray *all = [d_ptr.fs_mgr contentsOfDirectoryAtURL:self.url includingPropertiesForKeys:nil options:NSDirectoryEnumerationSkipsHiddenFiles error:nil];
    for (NSURL *each in all) {
        [d_ptr.fs_mgr removeItemAtURL:each error:nil];
    }
    
    [super clear];
}

- (void)removeItem:(CacheItem *)item {
    if (item.pdata) {
        [d_ptr.fs_mgr removeItemAtURL:(NSURL*)item.pdata error:nil];
    }
    
    [super removeItem:item];
}

- (BOOL)save {    
    BOOL ret = [super save];
    if (ret == NO)
        return ret;
    
    NSError* error = nil;
    
    WSI_USINGCXXNAMESPACE;
    
    // make index file.
    //GDataXMLElement* root = [[GDataXMLElement alloc] initWithXMLString:@"<root />" error:&error];
    parser::XmlDocument doc;
    parser::XmlNode* root = doc.root();
    root->name = "root";
    
    // add version.
    //GDataXMLElement* nversion = [[GDataXMLElement alloc] initWithXMLString:@"<version />" error:&error];
    //[nversion setStringValue:wsi::tostr(self.version)];
    //[root addChild:nversion];
    //[nversion release];
    root->add_node("version", core::tostr(self.version));
    
    // add index.    
    NSArray* items = [[self get_storage] allValues];
    
    // add count.
    //GDataXMLElement* count = [[GDataXMLElement alloc] initWithXMLString:@"<count />" error:&error];
    //[count setStringValue:wsi::tostr([items count])];
    //[root addChild:count];
    //[count release];
    root->add_node("count", core::tostr(items.count));
    
    // add index.
    for (CacheItem* each in items) {
        //GDataXMLElement* node = [[GDataXMLElement alloc] initWithXMLString:@"<index />" error:&error];
        //GDataXMLElement* nurl =  [[GDataXMLElement alloc] initWithXMLString:@"<url />" error:&error];
        //GDataXMLElement* ntype = [[GDataXMLElement alloc] initWithXMLString:@"<type />" error:&error];
        //GDataXMLElement* ntimestamp = [[GDataXMLElement alloc] initWithXMLString:@"<timestamp />" error:&error];
        //GDataXMLElement* noverdate = [[GDataXMLElement alloc] initWithXMLString:@"<overdate />" error:&error];
        parser::XmlNode* node = root->add_node("index");
        
        //[nurl setStringValue:each.code];
        //[ntype setStringValue:NSStringFromClass([each class])];
        //[ntimestamp setStringValue:wsi::tostr(each.timestamp)];
        //[noverdate setStringValue:wsi::tostr(each.overdate)];
        node->add_node("url", core::tostr(each.code));
        node->add_node("type", core::tostr(NSStringFromClass([each class])));
        node->add_node("timestamp", core::tostr(each.timestamp));
        node->add_node("overdate", core::tostr(each.overdate));
        
        //[node addChild:nurl];
        //[node addChild:ntype];
        //[node addChild:ntimestamp];
        //[node addChild:noverdate];
        //[root addChild:node];
        
        //[nurl release];
        //[ntype release];
        //[ntimestamp release];
        //[noverdate release];
        //[node release];
    }
    //trace_fmt(@"index %d cache items.", [items count]);
    
    // save to xml.
    //GDataXMLDocument* doc = [[GDataXMLDocument alloc] initWithRootElement:root];
    //NSData* data = [doc XMLData];
    //[root release];
    //[doc release];
    core::data raw;
    doc.save(raw);
    ns::Data data = core::type_cast<ns::Data>(raw);
    
    // save data to file.
    NSURL* index_file = [self.url URLByAppendingPathComponent:self.indexFile];
    if (NO == [data writeToURL:index_file options:NSDataWritingAtomic error:&error]) {
        trace_msg(@"failed to save cache items' index.");
        ret = NO;
    }
    
    return ret;
}

- (BOOL)saveItem:(NSString*)key item:(CacheItem*)item {
    BOOL suc = YES;
    NSData *data = [item toData];
    if (data) {
        NSURL *file_url = (NSURL*)item.pdata;
        if (file_url == nil) {
            file_url = [self.url URLByAppendingPathComponent:item.code];                                    
            item.pdata = file_url;
        }
        
        // save data.
        NSError *err = nil;
        if (NO == [data writeToURL:file_url options:NSDataWritingAtomic error:&err]) {
            suc = NO;
        }
        
    } else {
        trace_msg(@"skip cache a null data cache-item");
        suc = NO;
    }
    item.updated = NO;
    return suc;
}

- (BOOL)load {    
    WSIMACRO_LOCKOBJ(self);
    
    [self begin_load];
    
    NSError* error = nil;
    
    // load index.
    NSURL* index_file = [self.url URLByAppendingPathComponent:self.indexFile];
    NSData* data = [NSData dataWithContentsOfURL:index_file options:NSDataWritingAtomic error:&error];
    if (data == nil) {
        //trace_fmt(@"can't open cache: %@.", index_file.absoluteString);
        [self end_load];
        return NO;
    }
    
    BOOL enable_load = YES;
    
    WSI_USINGCXXNAMESPACE;
    
    // read index file.
    //GDataXMLDocument* doc = [[GDataXMLDocument alloc] initWithData:data options:0 error:&error];
    //GDataXMLElement* root = [doc rootElement];
    parser::XmlDocument doc;
    doc.parse_data(core::type_cast<core::data>(ns::Data(data)));
    parser::XmlNode* root = doc.root();
    
    // read version.
    //GDataXMLElement* nversion = (GDataXMLElement*)[[root elementsForName:@"version"] objectAtIndex:0 null:nil];
    parser::XmlNode* nversion = root->node("version");
    if (!nversion ||
        //([[nversion stringValue] intValue] < self.version)
        (core::toint(nversion->value) < self.version)
        ) {
        
        trace_fmt(@"clear cache because cache-system is out date. local: %d. cachesystem:%d.",
                  //[[nversion stringValue] intValue],
                  core::toint(nversion->value),
                  self.version);
        
        // version is out date.
        [self clear];
        
        enable_load = NO;
    }
    
    if (enable_load == NO) {
        [self end_load];
        return NO;
    }
    
    // read indexes.
    //NSArray* xml_indexes = [root elementsForName:@"index"];
    parser::XmlNode::nodes_result xml_indexes = root->nodes("index");
    
# ifdef WSI_DEBUG
    uint _sum = 0;
# endif
    
    //for (GDataXMLElement* each in xml_indexes)
    for (parser::XmlNode::nodes_result::iterator iter = xml_indexes.begin();
         iter != xml_indexes.end();
         ++iter)
    {
        
        // read.
        //NSString* type = [(GDataXMLElement*)[[each elementsForName:@"type"] objectAtIndex:0] stringValue];
        parser::XmlNode const* each = *iter;
        ns::String type = core::type_cast<ns::String>(each->node("type")->value);
        
        // add item.
        CacheItem *item = [[NSClassFromString(type) alloc] init];
        if (item == nil)
            continue;
        
        //NSString* file = [(GDataXMLElement*)[[each elementsForName:@"url"] objectAtIndex:0] stringValue];
        ns::String file = core::type_cast<ns::String>(each->node("url")->value);
        
        NSURL* file_url = [self.url URLByAppendingPathComponent:file];
        
        //int tmstamp = [[(GDataXMLElement*)[[each elementsForName:@"timestamp"] objectAtIndex:0] stringValue] intValue];
        //int overdate = [[(GDataXMLElement*)[[each elementsForName:@"overdate"] objectAtIndex:0] stringValue] intValue];
        int tmstamp = core::toint(each->node("timestamp")->value);
        int overdate = core::toint(each->node("overdate")->value);
        
        item.pending = YES;
        item.pdata = file_url;
        item.code = file;
        item.timestamp = tmstamp;
        item.overdate = overdate;
        
        if ([self addItem:item])
        //[super addItemUnsafe:item];
        {
            WSIDEBUG_EXPRESS(++_sum);
        }
        
        safe_release(item);
    }
    
# ifdef WSI_DEBUG
    trace_fmt(@"load %d[%d] items",
              _sum,
              //(uint)[xml_indexes count]
              (int)xml_indexes.size()
              );
# endif

    //[doc release];
    
    [self end_load];
    return YES;
}

- (BOOL)loadItem:(CacheItem *)item {
    if (item.pdata == nil) {
        trace_msg(@"skip a cacheitem with null url");
        return NO;
    }
    NSError* err = nil;
    NSData *data = [NSData dataWithContentsOfURL:(NSURL*)item.pdata 
                                         options:NSDataReadingUncached 
                                           error:&err];
    if (data == nil) {
        trace_msg(@"cacheitem:: fail to load data from disk.");
        trace_msg(err.localizedDescription);
        return NO;
    }
    
    // set super.
    [super loadItem:item];
    
    // get object from data.
    BOOL suc = [item fromData:data];
    
    // set flag.
    item.updated = NO;
    
    return suc;
}

@end

@implementation CacheItemArrayFileCache

- (NSData*)toData {
    if (self.data == nil)
        return nil;
    NSString *str = [WSIObject json_encode:self.data];
    return [str dataUsingEncoding:NSUTF8StringEncoding];
}

- (BOOL)fromData:(NSData *)__data {
    NSString *str = [[NSString alloc] initWithData:__data encoding:NSUTF8StringEncoding];
    self.data = [WSIObject json_decode:str];
    [str release];
    return YES;
}

@end

@implementation CacheItemPairFileCache

- (NSData*)toData {
    if (self.data == nil)
        return nil;
    NSString *str = [WSIObject json_encode:self.data];
    return [str dataUsingEncoding:NSUTF8StringEncoding];
}

- (BOOL)fromData:(NSData *)__data {
    NSString *str = [[NSString alloc] initWithData:__data encoding:NSUTF8StringEncoding];
    self.data = [WSIObject json_decode:str];
    [str release];
    return YES;
}

@end

@implementation CacheItemDictionaryFileCache

- (NSData*)toData {
    if (self.data == nil)
        return nil;
    NSString *str = [WSIObject json_encode:self.data];
    return [str dataUsingEncoding:NSUTF8StringEncoding];
}

- (BOOL)fromData:(NSData *)__data {
    NSString *str = [[NSString alloc] initWithData:__data encoding:NSUTF8StringEncoding];
    self.data = [WSIObject json_decode:str];
    [str release];
    return YES;
}

@end

@implementation CacheItemStringFileCache

- (NSData*)toData {
    if (self.data == nil)
        return nil;
    return [(NSString*)self.data dataUsingEncoding:NSUTF8StringEncoding];
}

- (BOOL)fromData:(NSData *)__data {
    NSString *str = [[NSString alloc] initWithData:__data encoding:NSUTF8StringEncoding];
    self.data = str;
    [str release];
    return YES;
}

@end

@implementation CacheItemDataFileCache

- (NSData*)toData {
    if (self.data == nil)
        return nil;
    return (NSData*)self.data;
}

- (BOOL)fromData:(NSData *)__data {
    self.data = __data;
    return YES;
}

@end

WSI_END_OBJC
