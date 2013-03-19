
# ifndef __NNT_NSNUMBER_FD5B7122D88D49CBBC72C830A0BF95AE_H_INCLUDED
# define __NNT_NSNUMBER_FD5B7122D88D49CBBC72C830A0BF95AE_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface NSNumber (NNT)

//! convert to string in binary.
- (NSString*) stringValueBinary;
+ (NSString*) StringValueBinary:(int)__val;

//! get real value.
- (real)realValue;

//! from real value.
+ (NSNumber*)numberWithReal:(real)val;

//! value type.
- (NNTValueType)valueType;

@end

NNTDECL_CATEGORY(NSNumber, NNT);

NNT_EXTERN NSNumber* NSNumberN1;
NNT_EXTERN NSNumber* NSNumber0;
NNT_EXTERN NSNumber* NSNumber1;
NNT_EXTERN NSNumber* NSNumber2;
NNT_EXTERN NSNumber* NSNumber3;
NNT_EXTERN NSNumber* NSNumber4;
NNT_EXTERN NSNumber* NSNumber5;
NNT_EXTERN NSNumber* NSNumber6;
NNT_EXTERN NSNumber* NSNumber7;
NNT_EXTERN NSNumber* NSNumber8;
NNT_EXTERN NSNumber* NSNumber9;
NNT_EXTERN NSNumber* NSNumberYes;
NNT_EXTERN NSNumber* NSNumberNo;

# define BoolObject(bval) ((bval) ? NSNumberYes : NSNumberNo)

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX

NNT_EXTERN NSNumber* number(int val);
NNT_EXTERN NSNumber* number(uint val);
NNT_EXTERN NSNumber* number(long val);
NNT_EXTERN NSNumber* number(ulong val);
NNT_EXTERN NSNumber* number(longlong val);
NNT_EXTERN NSNumber* number(ulonglong val);
NNT_EXTERN NSNumber* number(float val);
NNT_EXTERN NSNumber* number(double val);
NNT_EXTERN NSNumber* number(char val);
NNT_EXTERN NSNumber* number(bool val);
NNT_EXTERN NSNumber* boolnum(int val);

template <>
inline_impl id to_object<int> (int const& val) {
    return number(val);
}

template <>
inline_impl id to_object<uint> (uint const& val) {
    return number(val);
}

template <>
inline_impl id to_object<long> (long const& val) {
    return number(val);
}

template <>
inline_impl id to_object<ulong> (ulong const& val) {
    return number(val);
}

template <>
inline_impl id to_object<longlong> (longlong const& val) {
    return number(val);
}

template <>
inline_impl id to_object<ulonglong> (ulonglong const& val) {
    return number(val);
}

template <>
inline_impl id to_object<float> (float const& val) {
    return number(val);
}

template <>
inline_impl id to_object<double> (double const& val) {
    return number(val);
}

template <>
inline_impl id to_object<char> (char const& val) {
    return number(val);
}

template <>
inline_impl id to_object<bool> (bool const& val) {
    return number(val);
}

NNT_BEGIN_NS(ns)

NNT_BEGIN_NS(tpl)

template <typename numberT>
class Number
{
    
    typedef Number<numberT> self_type;
    
public:
    
    typedef numberT value_type;
    
    Number()
    {
        _number = [[value_type alloc] init];
    }
    
    Number(id obj)
    {
        _number = [obj retain];
    }
    
    ~Number()
    {
        safe_release(_number);
    }
    
    bool operator == (value_type* r) const
    {
        return [_number isEqualToNumber:r];
    }
    
    bool operator == (BOOL val) const
    {
        return *this == NSNumberYes;
    }
    
# define NNTNSNUMBER_OPERATORS(type, value) \
bool operator == (type val) const { \
return [_number value] == val; \
} \
bool operator != (type val) const { \
return [_number value] != val; \
} \
bool operator > (type val) const { \
return [_number value] > val; \
} \
bool operator < (type val) const { \
return [_number value] < val; \
} \
bool operator >= (type val) const { \
return [_number value] >= val; \
} \
bool operator <= (type val) const { \
return [_number value] <= val; \
}
    
    NNTNSNUMBER_OPERATORS(int, intValue);
    NNTNSNUMBER_OPERATORS(float, floatValue);
    NNTNSNUMBER_OPERATORS(double, doubleValue);
    NNTNSNUMBER_OPERATORS(long, longValue);
    
    operator BOOL() const
    {
        return [_number isEqualToNumber:YES];
    }
    
    operator value_type* () const
    {
        return (value_type*)_number;
    }
    
    operator NSString* () const
    {
        return [_number stringValue];
    }
    
    operator char () const
    {
        return [_number charValue];
    }
    
    operator uchar () const
    {
        return [_number unsignedCharValue];
    }
    
    operator short () const
    {
        return [_number shortValue];
    }
    
    operator ushort () const
    {
        return [_number unsignedShortValue];
    }
    
    operator int () const
    {
        return [_number intValue];
    }
    
    operator uint () const
    {
        return [_number unsignedIntValue];
    }
    
    operator float () const
    {
        return [_number floatValue];
    }
    
    operator double () const
    {
        return [_number doubleValue];
    }
    
    operator long() const
    {
        return [_number longValue];
    }
    
    operator ulong() const
    {
        return [_number unsignedLongValue];
    }
    
    operator longlong () const
    {
        return [_number longLongValue];
    }
    
    operator ulonglong () const
    {
        return [_number unsignedLongLongValue];
    }
    
    self_type& operator = (int val)
    {
        safe_release(_number);
        _number = [value_type numberWithIntValue:val];
        return *this;
    }
    
    value_type* operator * () const
    {
        return (value_type*)_number;
    }
    
protected:
    
    void _set(id obj)
    {
        safe_release(_number);
        _number = [obj retain];
    }
    
    value_type* _number;
    
};

NNT_END_NS

class Number
: public tpl::Number< NSNumber >
{
    
    typedef tpl::Number< NSNumber > super;
    
public:
    
    Number()
    {
        
    }
    
    Number(id obj)
    : super(obj)
    {
        
    }
    
    Number(int val)
    : super(nil)
    {
        this->_number = [[NSNumber numberWithInt:val] retain];
    }
    
    Number(uint val)
    : super(nil)
    {
        this->_number = [[NSNumber numberWithUnsignedInt:val] retain];
    }
    
    Number(long val)
    : super(nil)
    {
        this->_number = [[NSNumber numberWithLong:val] retain];
    }
    
    Number(ulong val)
    : super(nil)
    {
        this->_number = [[NSNumber numberWithUnsignedLong:val] retain];
    }
    
    Number(longlong val)
    : super(nil)
    {
        this->_number = [[NSNumber numberWithLongLong:val] retain];
    }
    
    Number(ulonglong val)
    : super(nil)
    {
        this->_number = [[NSNumber numberWithUnsignedLongLong:val] retain];
    }
    
    Number(float val)
    : super(nil)
    {
        this->_number = [[NSNumber numberWithFloat:val] retain];
    }
    
    Number(double val)
    : super(nil)
    {
        this->_number = [[NSNumber numberWithDouble:val] retain];
    }
    
    Number(char val)
    : super(nil)
    {
        this->_number = [[NSNumber numberWithChar:val] retain];
    }
    
    Number(bool val)
    : super(nil)
    {
        this->_number = [[NSNumber numberWithBool:val] retain];
    }
    
    ~Number()
    {
        
    }
    
};

class Decimal
: public tpl::Number < NSDecimalNumber >
{
    typedef tpl::Number < NSDecimalNumber > super;
    
public:
    
    Decimal()
    {
        
    }
    
    Decimal(id obj)
    : super(obj)
    {
        
    }
    
    ~Decimal()
    {
        
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
