
# import "Core.h"
# import "UUID+NNT.h"

NNT_BEGIN_OBJC

NSString* uuid_string()
{
    /*
    uuid_t uid;
    uuid_generate_random(uid);
    uuid_string_t str;
    uuid_unparse_lower(uid, str);
    return [[[NSString alloc] initWithBytes:str
                                     length:36
                                   encoding:NSUTF8StringEncoding] autorelease];
     */
    
    CFUUIDRef uuidObject = CFUUIDCreate(kCFAllocatorDefault);
    NSString *uuidStr = [(NSString *)CFUUIDCreateString(kCFAllocatorDefault, uuidObject) autorelease];
    CFRelease(uuidObject);
    
    return uuidStr;
}

NNT_END_OBJC
