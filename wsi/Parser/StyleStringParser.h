
# ifndef __WSI_PARSER_STYLESTRINGPARSER_384E814832184A6C818BDAFF0E085970_H_INCLUDED
# define __WSI_PARSER_STYLESTRINGPARSER_384E814832184A6C818BDAFF0E085970_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface StyleStringParser : WSIObject {
    
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

WSI_END_HEADER_OBJC

# endif