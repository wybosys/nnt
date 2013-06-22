
# ifndef __NNT_SERVICE_ICLOUD_1455587937F742C6B33F43947F6C7D36_H_INCLUDED
# define __NNT_SERVICE_ICLOUD_1455587937F742C6B33F43947F6C7D36_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface ICloudService : NNTObject {
    NSUbiquitousKeyValueStore* _kvstore;
}

@property (nonatomic, readonly) NSUbiquitousKeyValueStore* store;

+ (id)shared;

- (BOOL)synchronize;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(cloud)

class iCloud
: public ns::Object<ICloudService>
{
    typedef ns::Object<ICloudService> super;
    
public:
    
    iCloud();
    iCloud(id);
    
    static iCloud& getInstance();
    
    id find(ns::String const& key) const
    {
        return [this->_self.store objectForKey:key];
    }

    void set(id obj, ns::String const& key)
    {
        [this->_self.store setObject:obj forKey:key];
    }

    void remove(ns::String const& key)
    {
        [this->_self.store removeObjectForKey:key];
    }
    
    ns::String to_string(ns::String const& key) const
    {
        return [this->_self.store stringForKey:key];
    }

    ns::Array to_array(ns::String const& key) const
    {
        return [this->_self.store arrayForKey:key];
    }

    ns::Dictionary to_dictionary(ns::String const& key) const
    {
        return [this->_self.store dictionaryForKey:key];
    }

    ns::Data to_data(ns::String const& key) const
    {
        return [this->_self.store dataForKey:key];
    }

    longlong to_longlong(ns::String const& key) const
    {
        return [this->_self.store longLongForKey:key];
    }

    double to_double(ns::String const& key) const
    {
        return [this->_self.store doubleForKey:key];
    }

    bool to_bool(ns::String const& key) const
    {
        return [this->_self.store boolForKey:key];
    }
    
    void set(ns::String const& str, ns::String const& key)
    {
        [this->_self.store setString:str forKey:key];
    }

    void set(ns::Data const& da, ns::String const& key)
    {
        [this->_self.store setData:da forKey:key];
    }
    
    void set(ns::Array const& ar, ns::String const& key)
    {
        [this->_self.store setArray:ar forKey:key];
    }

    void set(ns::Dictionary const& dict, ns::String const& key)
    {
        [this->_self.store setDictionary:dict forKey:key];
    }

    void set(longlong val, ns::String const& key)
    {
        [this->_self.store setLongLong:val forKey:key];
    }
    
    void set(double val, ns::String const& key)
    {
        [this->_self.store setDouble:val forKey:key];
    }

    void set(BOOL val, ns::String const& key)
    {
        [this->_self.store setBool:val forKey:key];
    }
    
    ns::Dictionary representation() const
    {
        return this->_self.store.dictionaryRepresentation;
    }
    
    bool synchronize()
    {
        return [this->_self synchronize];
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
