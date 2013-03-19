
# import "Core.h"
# import "TBXML+WSI.h"

WSI_BEGIN_OBJC

@implementation TBXML (WSI)

id load_node(TBXMLElement* xmlnode) {
    id ret = nil;
    if (xmlnode->firstChild == NULL) {
        char *value = xmlnode->text ? xmlnode->text : "";
        ret = [NSString stringWithUTF8String:value];
    } else {
        NSMutableDictionary *dict = [[[NSMutableDictionary alloc] init] autorelease];
        
        TBXMLElement *node = xmlnode->firstChild;
        while (node) {
            id obj = load_node(node);
            
            NSString *key = [[NSString stringWithUTF8String:node->name] uppercaseString];
            id found = [dict objectForKey:key];
            if (found isnil_) {
                [dict setObject:obj forKey:key];
            } else {
                if ([found isKindOfClass:[NSMutableArray class]]) {
                    [(NSMutableArray*)found addObject:obj];
                } else {
                    NSMutableArray* arr = [NSMutableArray new];
                    [arr addObject:found];
                    [arr addObject:obj];
                    [dict setObject:arr forKey:key];
                    [arr release];
                }
            }
            
            node = node->nextSibling;
        }
        
        ret = dict;
    }
    return ret;
}

- (id)asObject:(BOOL)hideRoot {
    TBXMLElement *root = self.rootXMLElement;
    if (root isnil_)
        return nil;
    
    NSMutableDictionary *ret = [NSMutableDictionary new];
    TBXMLElement *node = root->firstChild;
    id store = ret;
    
    if (hideRoot == NO) {
        store = [NSMutableDictionary new];
        [ret setObject:store forKey:[[NSString stringWithUTF8String:root->name] uppercaseString]];
        [store release];
    }
    
    while (node) {
        id obj = load_node(node);
        NSString *key = [[NSString stringWithUTF8String:node->name] uppercaseString];
        id found = [(NSDictionary*)store objectForKey:key];
        if (found isnil_) {
            [(NSMutableDictionary*)store setObject:obj forKey:key];
        } else {
            if ([found isKindOfClass:[NSMutableArray class]]) {
                [(NSMutableArray*)found addObject:obj];
            } else {
                NSMutableArray* arr = [NSMutableArray new];
                [arr addObject:found];
                [arr addObject:obj];
                [(NSMutableDictionary*)store setObject:arr forKey:key];
                [arr release];
            }
        }
        node = node->nextSibling;
    }
    
    return [ret autorelease];
}

- (id)asObject {
    return [self asObject:YES];
}

@end

WSI_END_OBJC