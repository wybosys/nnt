
# ifndef __WSI_SEC_UUID_3A474467B7D644BC8726DF63AD0A305C_H_INCLUDED
# define __WSI_SEC_UUID_3A474467B7D644BC8726DF63AD0A305C_H_INCLUDED

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

WSI_EXTERN NSString* uuid_string();

WSI_END_HEADER_OBJC

# endif

WSI_BEGIN_HEADER_CXX

WSICLASS(uuid);

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

WSI_BEGIN_NS(wtl)

template <>
inline_impl string type_cast<string, uuid>(uuid const& uid)
{
    return uid.to_string();
}

WSI_END_NS

WSI_END_HEADER_CXX

# endif