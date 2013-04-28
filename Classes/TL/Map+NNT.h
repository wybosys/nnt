
# ifndef __NNT_CORE_MAP_BBB25FAAB28F4E0C83E3FEF8CFB18916_H_INCLUDED
# define __NNT_CORE_MAP_BBB25FAAB28F4E0C83E3FEF8CFB18916_H_INCLUDED

# ifdef NNT_CXX

# include <map>

# ifdef NNT_GCC
# ifdef _LIBCPP_VERSION
# define USE_UNORDEREDMAP 1
# include <unordered_map>
# undef __DEPRECATED
# include <ext/hash_map>
# else
# include <ext/hash_map>
# endif
# endif

# ifdef NNT_MSVC
# include <hash_map>
# endif

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ntl)

using ::std::map;
using ::std::multimap;

# ifdef NNT_GCC
# ifdef USE_UNORDEREDMAP
using ::std::unordered_map;
using ::__gnu_cxx::hash_map;
# else
using ::__gnu_cxx::hash_map;
# endif
# endif

# ifdef NNT_MSVC
using ::stdext::hash_map;
# endif

template <typename valT, typename keyT>
valT const* find(ntl::map<keyT, valT*> const& map, keyT const& key, valT const* _null = NULL)
{
    typedef typename ntl::map<keyT, valT*>::const_iterator iterator;
    iterator found = map.find(key);
    if (found == map.end())
        return _null;
    return found->second;
}

template <typename valT, typename keyT>
valT const* find(ntl::map<keyT, valT const*> const& map, keyT const& key, valT const* _null = NULL)
{
    typedef typename ntl::map<keyT, valT const*>::const_iterator iterator;
    iterator found = map.find(key);
    if (found == map.end())
        return _null;
    return found->second;
}

template <typename valT, typename keyT>
ntl::map<keyT, valT>& operator << (ntl::map<keyT, valT>& map, typename ntl::map<keyT, valT>::value_type const& val)
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
ntl::twmap<keyT, valT>& operator << (ntl::twmap<keyT, valT>& map, typename ntl::twmap<keyT, valT>::value_type const& val)
{
    map.insert(val);
    return map;
}

NNT_END_NS

NNT_BEGIN_NS(core)

using ntl::map;
using ntl::multimap;

NNT_END_NS

NNT_END_HEADER_CXX

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

typedef ::nnt::ntl::map<id, id> _NSMap;
typedef ::nnt::core::multimap<id, id> _NSMultiMap;

typedef _NSMap::iterator NSMapIterator;
typedef _NSMap::const_iterator NSMapConstIterator;

typedef _NSMultiMap::iterator NSMultiMapIterator;
typedef _NSMultiMap::const_iterator NSMultiMapConstIterator;

@interface NSMap : NNTObject {
    _NSMap *_map;
}

@property (nonatomic, discard) _NSMap *container;

- (NSMapIterator)begin;
- (NSMapIterator)end;

@end

@interface NSMultiMap : NNTObject {
    _NSMultiMap *_map;
}

@property (nonatomic, discard) _NSMultiMap *container;

- (NSMultiMapIterator)begin;
- (NSMultiMapIterator)end;

@end

NNT_END_HEADER_OBJC

# endif

# endif

# endif
