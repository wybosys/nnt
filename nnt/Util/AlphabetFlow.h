
# ifndef __WSI_UTIL_ALPHABETFLOW_0CA15CFEB8294B4B83171ED3ACB8088A_H_INCLUDED
# define __WSI_UTIL_ALPHABETFLOW_0CA15CFEB8294B4B83171ED3ACB8088A_H_INCLUDED

WSI_BEGIN_HEADER_C

//! need free memory manual.
char *alphabetflow_next(char const*, uint);
char *alphabetflow_prev(char const*, uint);

WSI_END_HEADER_C

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

@interface AlphabetFlow : NSObject {
    
    NSString *curValue;
    
}

@property (nonatomic, copy) NSString *curValue;

//! next value.
+ (NSString*)nextValue:(NSString*)value;

//! previous value.
+ (NSString*)prevValue:(NSString *)value;

//! default value.
+ (NSString*)defaultValue;

//! value operation.
- (NSString*)next;
- (NSString*)prev;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ns)

class AlphabetFlow
: public ns::Object< ::AlphabetFlow >
{
public:
    
    NSString* next()
    {
        return [this->_self next];
    }
    
    NSString* prev()
    {
        return [this->_self prev];
    }
    
    static NSString* DefaultValue()
    {
        return [::AlphabetFlow defaultValue];
    }
    
    static NSString* next(ns::String const& val)
    {
        return [::AlphabetFlow nextValue:val];
    }
    
    static NSString* prev(ns::String const& val)
    {
        return [::AlphabetFlow prevValue:val];
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX

class AlphabetFlow
{
public:
    
    AlphabetFlow();
    
    //! current string.
    core::string curValue;
    
    //! next & previous.
    static core::string nextValue(core::string const&);
    static core::string prevValue(core::string const&);
    
    //! default value string.
    core::string defaultValue() const;
    
    //! next & previous.
    core::string next();
    core::string prev();
    
};

WSI_END_HEADER_CXX

# endif

# endif