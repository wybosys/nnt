
# ifndef __NNT_REGEXOBJPARSER_700153092A2945CEBCADF2C10BE2C531_H_INCLUDED
# define __NNT_REGEXOBJPARSER_700153092A2945CEBCADF2C10BE2C531_H_INCLUDED

# import "TextObjParser.h"

NNT_BEGIN_HEADER_OBJC

@interface RegexObjParser : TextObjParser {
    NSMutableArray* _queries;
}

@property (nonatomic, retain) NSMutableArray *queries;

//! add query.
- (void)add_query:(NSString*)str;
- (void)set_query:(NSString*)str;

@end

NNT_END_HEADER_OBJC

# endif
