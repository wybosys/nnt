
# ifndef __WSI_SEC_MDN_A775164498C84AA38A8FA0ABDF8D329E_H_INCLUDED
# define __WSI_SEC_MDN_A775164498C84AA38A8FA0ABDF8D329E_H_INCLUDED

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

@interface MD5 : WSIObject

+ (NSString*)StringDigest:(NSString*)string;

@end

WSI_END_HEADER_OBJC

# endif

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX

WSICLASS(md5);

class md5
{
public:
    
    static core::string digest(core::data const&);
    static core::string digest(core::string const&);
    
    static core::data hex(core::string const&);
    static core::data hex(core::data const&);    

};

WSI_END_HEADER_CXX

# endif

# endif