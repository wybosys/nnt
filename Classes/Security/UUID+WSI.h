
# ifndef __NNT_SEC_UUID_3A474467B7D644BC8726DF63AD0A305C_H_INCLUDED
# define __NNT_SEC_UUID_3A474467B7D644BC8726DF63AD0A305C_H_INCLUDED

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

NNT_EXTERN NSString* uuid_string();

NNT_END_HEADER_OBJC

# endif

NNT_BEGIN_HEADER_CXX

NNTCLASS(uuid);

class uuid
{
public:
    
    uuid();        
    ~uuid();
    
    uuid(uuid const& r)
    {
        *this = r;
    }
    
    uuid& operator = (uuid const&);
    
    core::string to_string() const;
    
protected:
    
    void* _u;
    
};

NNT_BEGIN_NS(ntl)

template <>
inline_impl string type_cast<string, uuid>(uuid const& uid)
{
    return uid.to_string();
}

NNT_END_NS

NNT_END_HEADER_CXX

# endif