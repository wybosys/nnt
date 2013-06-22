
# ifndef __NNT_CORE_NSARRAY_FC3BCC61EFC14B4F810D3AE1081D4ECA_H_INCLUDED
# define __NNT_CORE_NSARRAY_FC3BCC61EFC14B4F810D3AE1081D4ECA_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface NSArray (NNT)

- (id)first;
- (id)second;
- (id)v0;
- (id)v1;
- (id)v2;
- (id)v3;
- (id)v4;
- (id)v5;
- (id)v6;
- (id)v7;
- (id)v8;

//! safe get object at index.
- (id)objectAtIndex:(NSUInteger)index null:(id)null;

//! object at next index.
- (id)objectAtNextIndex:(NSUInteger)index;

//! ojbect at pre index.
- (id)objectAtPrevIndex:(NSUInteger)index;

//! next object.
- (id)objectAtNext:(id)obj;

//! prev object.
- (id)objectAtPrev:(id)obj;

//! safe array.
+ (NSArray*)safeArray:(id)obj;

//! if the obj is not a array, will return nil.
+ (NSArray*)restrictArray:(id)obj;

//! get reverse array.
- (NSArray*)reverse;

//! convert to dictionary, NSString as key type from @"0".
- (NSDictionary*)asDictionary;

//! new array.
+ (NSArray*)arrayWithArrays:(NSArray*)arr, ...;

//! coretype.
- (uint)coreType;

//! calc unique array.
- (NSArray*)uniqueArray;

@end

NNTDECL_CATEGORY(NSArray, NNT);

@interface NSMutableArray (NNT)

//! safe array.
+ (NSMutableArray*)safeArray:(id)obj;

//! if the obj is not a array, will return nil.
+ (NSMutableArray*)restrictArray:(id)obj;

//! array with default capacity;
+ (NSMutableArray*)arrayWithCapacity;

//! swap object with left and right index.
- (void)swapObjectAtIndex:(NSUInteger)from ofIndex:(NSUInteger)to;

//! left rotate.
- (void)leftRotate;

//! left move.
- (void)leftMove;
- (void)leftMove:(id)fill;

//! right rotate.
- (void)rightRotate;

//! right move.
- (void)rightMove;
- (void)rightMove:(id)fill;

@end

NNTDECL_CATEGORY(NSMutableArray, NNT);

@interface NNTNSArray : NSArray

@property (nonatomic, readonly) id first, second, v0, v1, v2, v3, v4, v5, v6, v7, v8;

@end

@interface NNTNSMutableArray : NSMutableArray

@property (nonatomic, readonly) id first, second, v0, v1, v2, v3, v4, v5, v6, v7, v8;

@end

NNT_EXTERN uint kNSMutableArrayInitCapacity;

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ns)

NNT_BEGIN_NS(tpl)

template <typename TArr>
class CommonArray
: public ns::Object<TArr>
{
    typedef CommonArray<TArr> self_type;
    typedef ns::Object<TArr> super;
    
public:
    
    typedef struct {} array_type;
    
    CommonArray()
    {
        PASS;
    }
    
    CommonArray(usize sz)
    : super(nil)
    {
        this->_self = [[TArr alloc] initWithCapacity:sz];
    }
    
    CommonArray(id arr)
    : super(arr)
    {
        PASS;
    }
    
    CommonArray(self_type const& r)
    : super(r._self)
    {
        PASS;
    }
    
    ~CommonArray()
    {
        PASS;
    }
    
    id operator [] (int idx) const
    {
        return [this->_self objectAtIndex:idx null:nil];
    }
    
    id front() const
    {
        return (*this)[0];
    }
        
    id at(int idx) const
    {
        return [this->_self objectAtIndex:idx null:nil];
    }
    
    usize size() const 
    {
        return [this->_self count];
    }
    
    usize count() const
    {
        return [this->_self count];
    }
    
    self_type clone() const
    {
        TArr* arr = [TArr arrayWithArray:this->_self];
        self_type ret(arr);
        return ret;
    }
    
    uint find(id obj, uint null = -1) const
    {
        NSUInteger found = [this->_self indexOfObject:obj];
        if (found == NSNotFound)
            return null;
        return found;
    }
    
    NSArray* sort(SEL comparator) const
    {
        return [this->_self sortedArrayUsingSelector:comparator];
    }
    
    typedef NSInteger (* sort_comparator)(id, id, void *);
    
    NSArray* sort(sort_comparator comparator, void* context)
    {
        return [this->_self sortedArrayUsingFunction:comparator context:context];
    }
    
    NSArray* sort(sort_comparator comparator, void* context, NSData* hint)
    {
        return [this->_self sortedArrayUsingFunction:comparator context:context hint:hint];
    }
    
};

template <typename TArr>
class Array
: public CommonArray <TArr>
{
public:
    
    Array()
    {
        PASS;
    }
    
    Array(TArr *arr)
    : CommonArray <TArr> (arr)
    {
        PASS;
    }
    
};

template <>
class Array <NSMutableArray>
: public CommonArray <NSMutableArray>
{
    typedef CommonArray <NSMutableArray> super;
    typedef Array <NSMutableArray> self_type;
    
public:
    
    Array()
    {
        PASS;
    }
    
    Array(NSMutableArray *arr)
    : super(arr)
    {
        PASS;
    }
    
    Array(NSArray *arr)
    : super((id)nil)
    {
        NSMutableArray* obj = [[NSMutableArray alloc] initWithArray:arr];
        _set(obj);
        [obj release];
    }
    
    explicit Array(id obj)
    : super((NSMutableArray*)obj)
    {
        PASS;
    }
    
    template <typename T>
    Array(T const& obj,
          typename ntl::is_wrapper<T>::wrapper* = NULL)
    : super((NSMutableArray*)obj)
    {
        PASS;
    }
    
    Array(usize sz)
    : super (sz)
    {
        PASS;
    }
    
protected:
    
    class target
    {
    public:
        
        Array <NSMutableArray>& operator = (id val)
        {
            int diff = (int)idx - (int)[arr->_self count];
            for (int i = 1; i < diff; ++i) {
                [arr->_self addObject:[NSNull null]];
            }
            if (diff < 0)
            {
                [arr->_self replaceObjectAtIndex:idx withObject:val];
            }
            else
            {
                [arr->_self addObject:val];
            }
            obj = val;
            return *arr;
        }
        
        operator id ()
        {
            return obj;
        }
        
        operator lang_objc* ()
        {
            return (lang_objc*)obj;
        }
        
    public:
        
        uindex idx;
        id obj;
        Array <NSMutableArray> *arr;
        
    };
    
    friend class target;
    
public:
    
    target operator [] (int idx)
    {
        target ret;
        ret.idx = idx;
        ret.obj = [this->_self objectAtIndex:idx null:nil];
        ret.arr = this;
        return ret;
    }
    
    target operator [] (int idx) const
    {
        target ret;
        ret.idx = idx;
        ret.obj = [this->_self objectAtIndex:idx null:nil];
        return ret;
    }
    
    self_type& operator << (id obj)
    {
        [this->_self addObject:obj];
        return *this;
    }
    
    self_type& push_back(id obj)
    {
        [this->_self addObject:obj];
        return *this;
    }
    
    self_type& operator << (auto_id const& obj)
    {
        [this->_self addObject:obj.obj];
        return *this;
    }
    
    self_type& operator << (ignore_null obj)
    {
        if (obj == nil) {
            return *this;
        }
        [this->_self addObject:(id)obj];
        return *this; 
    }
    
    self_type& add(id obj)
    {
        [this->_self addObject:obj];
        return *this;
    }
    
    self_type& add_array(id obj)
    {
        for (id each in obj) {
            [this->_self addObject:each];
        }
        return *this;
    }
    
    void clear()
    {
        [this->_self removeAllObjects];
    }
    
    void remove(id obj)
    {
        [this->_self removeObject:obj];
    }
    
    void remove(uint idx)
    {
        [this->_self removeObjectAtIndex:idx];
    }
    
    static self_type Safe(id obj)
    {
        return [objc_type safeArray:obj];
    }
    
};

template <>
class Array <NSArray>
: public CommonArray <NSArray>
{
    typedef Array<NSArray> self_type;
    typedef CommonArray <NSArray> super;
    
public:
    
    Array()
    {
        PASS;
    }
    
    Array(NSArray *arr)
    : super(arr)
    {
        PASS;
    }
    
    Array(Array<NSMutableArray> const& r)
    : super((NSArray*)(NSMutableArray*)r)
    {
        PASS;
    }
    
    explicit Array(id obj)
    : super((NSArray*)obj)
    {
        PASS;
    }
    
    template <typename T>
    Array(T const& obj,
          typename ntl::is_wrapper<T>::wrapper* = NULL)
    : super((NSArray*)obj)
    {
        PASS;
    }
    
    self_type& operator = (Array<NSMutableArray> const& r)
    {
        this->_set((NSArray*)(NSMutableArray*)r);
        return *this;
    }
    
    static self_type Safe(id obj)
    {
        return [objc_type safeArray:obj];
    }
    
};
    
NNT_END_NS
    
typedef tpl::Array<NSArray> Array;
typedef tpl::Array<NSMutableArray> MutableArray;
    
NNT_EXTERN Array const null_array;
NNT_EXTERN MutableArray const null_mutablearray;

NNT_END_NS
    
NNT_BEGIN_NS(ntl)

template <typename valT>
struct sequence<valT, SEQUENCE_OBJC_MUTARRAY>
{ 
    typedef ::nnt::ns::MutableArray type; 
};
    
template <typename containerT, typename objcarrT>
static containerT type_cast(objcarrT const& arr, typename objcarrT::array_type* = NULL)
{
    containerT ret;
    for (id each in *arr)
    {
        ret << typename containerT::value_type(each);
    }
    return ret;
}
    
template <typename objcarrT, typename containerT>
static objcarrT type_cast(containerT const& con, typename objcarrT::array_type* = NULL)
{
    ns::MutableArray ret;
    typedef typename containerT::const_iterator iterator;
    for (iterator iter = con.begin();
         iter != con.end();
         ++iter)
    {
        ret << (id)*iter;
    }
    return (objcarrT)ret;
}

NNT_END_NS

NNT_END_HEADER_CXX

# endif

# endif