
# ifndef __NNT_UTIL_ALPHABETSORT_0DF8A61BC1C04347AD8782A469B4333A_H_INCLUDED
# define __NNT_UTIL_ALPHABETSORT_0DF8A61BC1C04347AD8782A469B4333A_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface ChineseObject : NNTObject

@property (nonatomic, copy) NSString *string;
@property (nonatomic, copy) NSString *pinyin;

@end

@interface AlphabeticSort : NNTObject

- (NSMutableDictionary *)sortByAlphabetic:(NSMutableArray*)chineseArray;

@end

NNT_END_HEADER_OBJC

# endif