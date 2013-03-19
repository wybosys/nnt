
# ifndef __NNT_SEC_MDN_A775164498C84AA38A8FA0ABDF8D329E_H_INCLUDED
# define __NNT_SEC_MDN_A775164498C84AA38A8FA0ABDF8D329E_H_INCLUDED

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

@interface MD5 : NNTObject

+ (NSString*)StringDigest:(NSString*)string;

@end

NNT_END_HEADER_OBJC

# endif

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX

NNTCLASS(md5);

class md5
{
public:
    
    static core::string digest(core::data const&);
    static core::string digest(core::string const&);
    
    static core::data hex(core::string const&);
    static core::data hex(core::data const&);    

};

NNT_END_HEADER_CXX

# endif

# endif