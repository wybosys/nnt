
# ifndef __NNT_PARSER_STYLESTRINGPARSER_384E814832184A6C818BDAFF0E085970_H_INCLUDED
# define __NNT_PARSER_STYLESTRINGPARSER_384E814832184A6C818BDAFF0E085970_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface StyleStringParser : NNTObject {
    
    //! string store the result.
    NSString* string;
    
    //! style strings.
    NSArray* styleStrings;
}

@property (nonatomic, readonly, retain) NSString* string;
@property (nonatomic, retain) NSArray* styleStrings;

- (void)parseString:(NSString*)string;
- (void)parseData:(NSData*)data;

@end

NNT_END_HEADER_OBJC

# endif