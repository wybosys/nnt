
# import "Core.h"
# import "AlphabeticSort.h"
# import "ChineseString.h"

NNT_BEGIN_OBJC

@implementation ChineseObject

@synthesize string = _string, pinyin = _pinyin;

- (void)dealloc {
    safe_release(_string);
    safe_release(_pinyin);
    [super dealloc];
}

@end

@implementation AlphabeticSortResult

@synthesize key = _key, value = _value;

- (void)dealloc {
    safe_release(_key);
    safe_release(_value);
    [super dealloc];
}

@end

@implementation AlphabeticSort

@synthesize keys;

- (void)dealloc {
    safe_release(keys);
    [super dealloc];
}

- (id)init {
    self = [super init];
    
    keys = [[NSMutableArray alloc] init];
    
    return self;
}

- (NSMutableDictionary *)sortByAlphabetic:(NSArray *)chineseArray {

    NSMutableArray *chineseStringArray = [[NSMutableArray alloc] init];
    for (uint idx = 0; idx < chineseArray.count; ++idx) {
        ChineseObject *co = [[ChineseObject alloc] init];
        co.string = [NSString stringWithString:[chineseArray objectAtIndex:idx null:@""]];
    
        if (![co.string isEqualToString:@""]) {
            co.pinyin = [[ChineseString CharacterToPinYin:co.string] uppercaseString];
        } else {
            co.pinyin = @"";
        }
        
        [chineseStringArray addObject:co];
        safe_release(co);
    }
    
    NSArray *sortDescriptors = [NSArray arrayWithObject:[NSSortDescriptor sortDescriptorWithKey:@"pinyin" ascending:YES]];
    [chineseStringArray sortUsingDescriptors:sortDescriptors];
        
    NSMutableDictionary *ret = [[[NSMutableDictionary alloc] init] autorelease];
    
    for (uint idx = 0; idx < chineseStringArray.count; ++idx) {
        ChineseObject *obj = (ChineseObject *)[chineseStringArray objectAtIndex:idx];
        NSMutableString *strchar = [NSMutableString stringWithString:obj.pinyin];
        NSString *first = [[strchar substringToIndex:1] uppercaseString];
        
        if (![[ret allKeys] containsObject:first]) {
            NSMutableArray *value = [[NSMutableArray alloc] init];
            [value addObject:obj.string];
            [ret setKey:first forObj:value];
            safe_release(value);
        } else {
            NSMutableArray *value = (NSMutableArray *)[ret objectForKey:first];
            [value addObject:obj.string];
        }
    }
    
    return ret;
}

- (NSArray *)sortedResult:(NSArray *)chineseArray {
    NSMutableDictionary *dict = [self sortByAlphabetic:chineseArray];
    
    NSMutableArray *ret = [[NSMutableArray alloc] init];
    
    for (NSString *key in dict.allKeys) {
        AlphabeticSortResult *as = [[AlphabeticSortResult alloc] init];
        as.key = key;
        as.value = [dict objectForKey:key null:@""];
        [ret addObject:as];
        safe_release(as);
    }
    
    NSArray *sortDescriptors = [NSArray arrayWithObject:[NSSortDescriptor sortDescriptorWithKey:@"key" ascending:YES]];
    [ret sortUsingDescriptors:sortDescriptors];
    
    for (AlphabeticSortResult *as in ret) {
        [keys  addObject:as.key];
    }
    
    return ret.autorelease;
}

@end

NNT_END_OBJC






















