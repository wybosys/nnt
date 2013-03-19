
# ifndef __WSI_CORE_MAP_BBB25FAAB28F4E0C83E3FEF8CFB18916_H_INCLUDED
# define __WSI_CORE_MAP_BBB25FAAB28F4E0C83E3FEF8CFB18916_H_INCLUDED

# ifdef WSI_CXX

# include <map>

# ifdef WSI_GCC
# ifdef _LIBCPP_VERSION
# define USE_UNORDEREDMAP 1
# include <unordered_map>
# undef __DEPRECATED
# include <ext/hash_map>
# else
# include <ext/hash_map>
# endif
# endif

# ifdef WSI_MSVC
# include <hash_map>
# endif

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(wtl)

using ::std::map;
using ::std::multimap;

# ifdef WSI_GCC
# ifdef USE_UNORDEREDMAP
using ::std::unordered_map;
using ::__gnu_cxx::hash_map;
# else
using ::__gnu_cxx::hash_map;
# endif
# endif

# ifdef WSI_MSVC
using ::stdext::hash_map;
# endif

template <typename valT, typename keyT>
valT const* find(wtl::map<keyT, valT*> const& map, keyT const& key, valT const* _null = NULL)
{
    typedef typename wtl::map<keyT, valT*>::const_iterator iterator;
    iterator found = map.find(key);
    if (found == map.end())
        return _null;
    return found->second;
}

template <typename valT, typename keyT>
valT const* find(wtl::map<keyT, valT const*> const& map, keyT const& key, valT const* _null = NULL)
{
    typedef typename wtl::map<keyT, valT const*>::const_iterator iterator;
    iterator found = map.find(key);
    if (found == map.end())
        return _null;
    return found->second;
}

template <typename valT, typename keyT>
wtl::map<keyT, valT>& operator << (wtl::map<keyT, valT>& map, typename wtl::map<keyT, valT>::value_type const& val)
{
    map.insert(val);
    return map;
}

template <typename keyT, typename valT,
typename isequal = typename is_equal<keyT, valT>::type
>
class twmap
{
    
};

template <typename keyT, typename valT>
class twmap <keyT, valT, equal_t>
{
public:
    
    typedef map<keyT, valT> left_map_type;
    typedef map<valT, keyT> right_map_type;
    typedef ::std::pair<keyT, valT> value_type;
    
    twmap()
    {
        PASS;
    }
    
    void insert(keyT const& k, valT const& v)
    {
        left_map[k] = v;
        right_map[v] = k;
    }
    
    void insert(value_type const& p)
    {
        insert(p.first, p.second);
    }
    
    void erase(keyT const& k)
    {
        typename left_map_type::iterator found = left_map.find(k);
        if (found == left_map.end())
            return;
        
        right_map.erase(right_map.find(found->second));
        left_map.erase(found);
    }
    
    left_map_type left_map;
    right_map_type right_map;
    
};

template <typename keyT, typename valT>
class twmap <keyT, valT, unequal_t>
: public twmap <keyT, valT, equal_t>
{
    typedef twmap <keyT, valT, equal_t> super;
    
public:
    
    using super::left_map;
    using super::right_map;
    typedef typename super::left_map_type left_map_type;
    typedef typename super::right_map_type right_map_type;
    
    void erase(keyT const& k)
    {
        super::erase(k);
    }
    
    void erase(valT const& v)
    {
        typename right_map_type::iterator found = right_map.find(v);
        if (found == right_map.end())
            return;
        
        left_map.erase(left_map.find(found->second));
        right_map.erase(found);
    }
    
};

template <typename valT, typename keyT>
wtl::twmap<keyT, valT>& operator << (wtl::twmap<keyT, valT>& map, typename wtl::twmap<keyT, valT>::value_type const& val)
{
    map.insert(val);
    return map;
}

WSI_END_NS

WSI_BEGIN_NS(core)

using wtl::map;
using wtl::multimap;

WSI_END_NS

WSI_END_HEADER_CXX

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

typedef ::wsi::wtl::map<id, id> _NSMap;
typedef ::wsi::core::multimap<id, id> _NSMultiMap;

typedef _NSMap::iterator NSMapIterator;
typedef _NSMap::const_iterator NSMapConstIterator;

typedef _NSMultiMap::iterator NSMultiMapIterator;
typedef _NSMultiMap::const_iterator NSMultiMapConstIterator;

@interface NSMap : WSIObject {
    _NSMap *_map;
}

@property (nonatomic, discard) _NSMap *container;

- (NSMapIterator)begin;
- (NSMapIterator)end;

@end

@interface NSMultiMap : WSIObject {
    _NSMultiMap *_map;
}

@property (nonatomic, discard) _NSMultiMap *container;

- (NSMultiMapIterator)begin;
- (NSMultiMapIterator)end;

@end

WSI_END_HEADER_OBJC

# endif

# endif

# endif