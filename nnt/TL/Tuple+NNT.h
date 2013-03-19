
# ifndef __NNT_CORE_TUPLE_E3F27C33473C4BEB9A7E5FFDE1063B86_H_INCLUDED
# define __NNT_CORE_TUPLE_E3F27C33473C4BEB9A7E5FFDE1063B86_H_INCLUDED

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

@interface NSPair : NSObject <NSFastEnumeration> {
    id first;
    id second;
}

@property (nonatomic, retain) id first, second;
@property (nonatomic, retain) id v0, v1;

//! init.
- (NSPair*)initWith:(id)first second:(id)second;
+ (NSPair*)pairWith:(id)first second:(id)second;

//! get object at.
- (id)objectAtIndex:(uindex)idx;
- (id)objectAtIndex:(uindex)idx null:(id)null;

//! count.
- (NSUInteger)count;

//! coretype.
- (uint)coreType;

@end

//# define pair(v0, v1) [NSPair pairWith:(v0) second:(v1)]
//# define first(obj)   (((NSPair*)obj).first)
//# define second(obj)  (((NSPair*)obj).second)

inline_impl NSPair* pair(id v0, id v1) {
    return [NSPair pairWith:v0 second:v1];
}

inline_impl id first(id obj) {
    return ((NSPair*)obj).first;
}

inline_impl id second(id obj) {
    return ((NSPair*)obj).second;
}

typedef NSPair NSTuple2;

@interface NSTuple3 : NSPair {
    id v2;
}

@property (nonatomic, retain) id v2;

- (NSTuple3*)initWith:(id)first v1:(id)second v2:(id)v2;
+ (NSTuple3*)tupleWith:(id)first v1:(id)second v2:(id)v2;

@end

@interface NSTuple4 : NSTuple3 {
    id v3;
}

@property (nonatomic, retain) id v3;

- (NSTuple4*)initWith:(id)first v1:(id)second v2:(id)v2 v3:(id)v3;
+ (NSTuple4*)tupleWith:(id)first v1:(id)second v2:(id)v2 v3:(id)v3;

@end

@interface NSTuple5 : NSTuple4 {
    id v4;
}

@property (nonatomic, retain) id v4;

- (NSTuple5*)initWith:(id)_v0 v1:(id)_v1 v2:(id)_v2 v3:(id)_v3 v4:(id)_v4;
+ (NSTuple5*)tupleWith:(id)_v0 v1:(id)_v1 v2:(id)_v2 v3:(id)_v3 v4:(id)_v4;

@end

@interface NSTuple6 : NSTuple5 {
    id v5;
}

@property (nonatomic, retain) id v5;

- (NSTuple6*)initWith:(id)_v0 v1:(id)_v1 v2:(id)_v2 v3:(id)_v3 v4:(id)_v4 v5:(id)_v5;
+ (NSTuple6*)tupleWith:(id)_v0 v1:(id)_v1 v2:(id)_v2 v3:(id)_v3 v4:(id)_v4 v5:(id)_v5;

@end

@interface NSTuple7 : NSTuple6 {
    id v6;
}

@property (nonatomic, retain) id v6;

- (NSTuple7*)initWith:(id)_v0 v1:(id)_v1 v2:(id)_v2 v3:(id)_v3 v4:(id)_v4 v5:(id)_v5 v6:(id)_v6;
+ (NSTuple7*)tupleWith:(id)_v0 v1:(id)_v1 v2:(id)_v2 v3:(id)_v3 v4:(id)_v4 v5:(id)_v5 v6:(id)_v6;

@end

@interface NSTuple8 : NSTuple7 {
    id v7;
}

@property (nonatomic, retain) id v7;

- (NSTuple8*)initWith:(id)_v0 v1:(id)_v1 v2:(id)_v2 v3:(id)_v3 v4:(id)_v4 v5:(id)_v5 v6:(id)_v6 v7:(id)_v7;
+ (NSTuple8*)tupleWith:(id)_v0 v1:(id)_v1 v2:(id)_v2 v3:(id)_v3 v4:(id)_v4 v5:(id)_v5 v6:(id)_v6 v7:(id)_v7;

@end

@interface NSTuple9 : NSTuple8 {
    id v8;
}

@property (nonatomic, retain) id v8;

- (NSTuple9*)initWith:(id)_v0 v1:(id)_v1 v2:(id)_v2 v3:(id)_v3 v4:(id)_v4 v5:(id)_v5 v6:(id)_v6 v7:(id)_v7 v8:(id)_v8;
+ (NSTuple9*)tupleWith:(id)_v0 v1:(id)_v1 v2:(id)_v2 v3:(id)_v3 v4:(id)_v4 v5:(id)_v5 v6:(id)_v6 v7:(id)_v7 v8:(id)_v8;

@end

NNT_EXTERN NSObject *tuple(id v0, id v1, ...);

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ns)

class Pair
: public ns::Object<NSPair>
{
    typedef ns::Object<NSPair> super;
    
public:
    
    Pair()
    {
        PASS;
    }
    
    Pair(id l, id r)
    : super(nil)
    {
        this->_self = [[NSPair alloc] initWith:l second:r];
    }
    
    template <typename valL, typename valR>
    Pair(valL const& l, valR const& r)
    : super(nil)
    {
        id lobj = ::nnt::to_object(l);
        id robj = ::nnt::to_object(r);
        this->_self = [[NSPair alloc] initWith:lobj second:robj];
    }
    
    Pair(Pair const& r)
    : super(r._self)
    {
        PASS;
    }
    
    Pair(NSPair* r)
    : super(r)
    {
        PASS;
    }
    
    Pair& operator = (Pair const& r)
    {
        _set(r._self);
        return *this;
    }
    
    id first() const
    {
        return this->_self.first;
    }
    
    id second() const
    {
        return this->_self.second;
    }
    
};

NNT_END_NS

NNTNS_CONST_POINTER(ns::Pair);

NNT_END_HEADER_CXX

# endif

# endif

# endif