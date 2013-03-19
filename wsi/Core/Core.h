
# ifndef __WSI_CORE_C4207797EACE47B4A2CC42B5539FBAD7_H_INCLUDED
# define __WSI_CORE_C4207797EACE47B4A2CC42B5539FBAD7_H_INCLUDED

# ifdef __cplusplus
#	define WSI_CXX
#   define WSI_C_CXX
#   define WSI_C_COMPATIABLE
#   define CXX_EXPRESS(exp) exp
#   define C_EXPRESS(exp)

#   if __cplusplus < 201103L
#      define WSI_CXX_99 1
#   else
#      define WSI_CXX_11 1
#   endif

# else
#   define WSI_C
#   define WSI_C_COMPATIABLE
#   define CXX_EXPRESS(exp)
#   define C_EXPRESS(exp) exp
# endif

# ifdef __llvm__
#   define WSI_CC_LLVM 1
#   define WSI_LLVM WSI_CC_LLVM
# endif

# ifdef __clang__
#   define WSI_CC_CLANG 1
#   define WSI_CLANG WSI_CC_CLANG
# endif

# ifdef __GNUC__
#   define WSI_CC_GCC 1
#   define WSI_GCC WSI_CC_GCC
# endif

# ifdef __APPLE__
#   define WSI_MACH 1
#   include <TargetConditionals.h>
# endif

# ifdef __amd64
#   define WSI_X64 1
# endif

# if defined(__i386) || defined(_M_IX86)
#   define WSI_X32 1
# endif

# if (defined(__LP64__) && __LP64__) || defined(_M_IA64)
#   define WSI_X64 1
# endif

# ifdef __arm
#   define WSI_ARM 1
# ifndef WSI_X32
#   define WSI_X32 1
# endif
# endif

# if defined(_MSC_VER) && defined(WIN32)
#   ifdef _MFC_VER
#     define WSI_MFC 1 
#   endif
// is windows.
#   define WSI_MSVC 1
#   define WSI_WINDOWS 1
#   if (defined(_USRDLL) && !defined(LIBWSI)) || defined(LIBWSI)
#     define WSI_LIBRARY
#   endif
#   if defined(WSI_LIBRARY)
#     include "stdafx.h"
#   endif
#   include <Windows.h>
//#   include <WinNT.h>
#   include <tchar.h>
#   include <cwchar>
#   ifdef WSI_MFC
#     include <afx.h>
#     include <afxwin.h>
#   endif
# else
// is unix like.
#   define WSI_UNIX 1
# endif

# ifdef WSI_CXX
#   ifdef WSI_CXX_99

struct _nullptr
{
    template <typename T>
    operator T* () const
    {
        return (T*)0;
    }
};

const _nullptr nullptr();

#   endif
# endif

# if defined(_UNICODE)
#   define WSI_UNICODE 1
# endif

# define WSI_VERBOSE 1
# define WSI_VERBOSE_VERBOSE 0

# if defined(WSI_FRAMEWORK) && !defined(LIBWSI)
#   define LIBWSI 1
# endif

# if defined(WSI_LIBRARY)
#   define APPWSI 1
# endif

# if defined(__OBJC__) || defined(__OBJC2__)
#	define WSI_OBJC
#   if __has_feature(objc_arc)
#     define WSI_OBJC_ARC 1
#   endif
# endif

# if defined(WSI_CXX) && !defined(WSI_OBJC)
#   define WSI_PURE_CXX 1
# endif

# if !defined(WSI_CXX) && defined(WSI_OBJC)
#   define WSI_PURE_OBJC 1
# endif

# if defined(WSI_CXX) && defined(WSI_OBJC)
#   define WSI_CXX_OBJC 1
# endif

# if defined(WSI_C) && !defined(WSI_OBJC) && !defined(WSI_CXX)
#   define WSI_PURE_C 1
# endif

# if defined(WSI_C) && defined(WSI_OBJC)
#   define WSI_C_OBJC 1
# endif

# ifdef TARGET_OS_IPHONE

#   define WSI_IOS_MIN __IPHONE_OS_VERSION_MIN_REQUIRED
#   define WSI_IOS_MAX __IPHONE_OS_VERSION_MAX_ALLOWED

typedef struct { enum { VERSION = 2 }; } ios_2;
typedef struct { enum { VERSION = 3 }; } ios_3;
typedef struct { enum { VERSION = 4 }; } ios_4;
typedef struct { enum { VERSION = 5 }; } ios_5;
typedef struct { enum { VERSION = 6 }; } ios_6;
typedef struct { enum { VERSION = 0 }; } ios_unknown;

# define __IPHONE_NA_NA 99999999

# ifndef __IPHONE_6_0
#   define __IPHONE_6_0 __IPHONE_NA_NA
# endif

# ifndef __IPHONE_5_0
#   define __IPHONE_5_0 __IPHONE_NA_NA
# endif

# ifndef __IPHONE_4_0
#   define __IPHONE_4_0 __IPHONE_NA_NA
# endif

# ifndef __IPHONE_3_0
#   define __IPHONE_3_0 __IPHONE_NA_NA
# endif

#   if 0
#   elif WSI_IOS_MIN >= __IPHONE_6_0
typedef ios_6 ios_version;
#   elif WSI_IOS_MIN >= __IPHONE_5_0
typedef ios_5 ios_version;
#   elif WSI_IOS_MIN >= __IPHONE_4_0
typedef ios_4 ios_version;
#   elif WSI_IOS_MIN >= __IPHONE_3_0
typedef ios_3 ios_version;
#   elif WSI_IOS_MIN >= __IPHONE_2_0
typedef ios_2 ios_version;
#   else
typedef ios_unknown ios_version;
# endif

# endif

# define WSI_INLINE inline
# define WSI_STATIC static
# define WSI_STATIC_IMPL
# define WSI_STATIC_CONST static const
# define WSI_STATIC_CONST_IMPL
# define inline_impl inline
# define template_impl

typedef struct {} arch_unknown;
typedef struct {} arch_x32;
typedef struct {} arch_x64;
typedef struct {} arch_arm;

typedef struct {} os_unknown;
typedef struct {} os_windows;
typedef struct {} os_unix;
typedef struct {} os_mach;

typedef struct {} lang_unknown;
typedef struct {} lang_objc;
typedef struct {} lang_c;
typedef struct {} lang_cxx;

typedef struct {} compr_unknown;
typedef struct {} compr_gcc;
typedef struct {} compr_msvc;
typedef struct {} compr_clang;

# ifdef WSI_X64
typedef arch_x64 arch_type;
# endif

# ifdef WSI_X32
typedef arch_x32 arch_type;
# endif

# ifdef WSI_WINDOWS
typedef os_windows os_type;
# elif defined(WSI_MACH)
typedef os_mach os_type;
# elif defined(WSI_UNIX)
typedef os_unix os_type;
# endif

# ifdef WSI_OBJC
typedef lang_objc lang_type;
# elif defined(WSI_CXX)
typedef lang_cxx lang_type;
# elif defined(WSI_C)
typedef lang_c lang_type;
# endif

# ifdef WSI_GCC
typedef compr_gcc compr_type;
# elif defined(WSI_MSVC)
typedef compr_msvc compr_type;
# elif defined(WSI_CLANG)
typedef compr_clang compr_type;
# endif

WSI_STATIC_CONST arch_type arch_object();
WSI_STATIC_CONST os_type os_object();
WSI_STATIC_CONST lang_type lang_object();
WSI_STATIC_CONST compr_type compr_object();

# define WSIASM_BEGIN __asm {
# define WSIASM_END }
# define WSIASM(exp) \
WSIASM_BEGIN\
exp \
WSIASM_END

# define WSI_BEGIN_CXX namespace wsi {
# define WSI_END_CXX   }

# ifdef WSI_CXX
#   define WSI_USINGCXXNAMESPACE using namespace ::wsi;
#	define WSI_BEGIN             WSI_BEGIN_CXX
#	define WSI_END               WSI_END_CXX
#	define WSI_BEGIN_HEADER_C    extern "C" {
#	define WSI_END_HEADER_C      }
#   define WSI_BEGIN_HEADER_CXX  WSI_BEGIN_CXX
#   define WSI_END_HEADER_CXX    WSI_END_CXX
#   define WSI_BEGIN_HEADER_CXX_EXPLICIT WSI_BEGIN_HEADER_CXX namespace cxx {
#   define WSI_END_HEADER_CXX_EXPLICIT WSI_END_HEADER_CXX }
#	define WSI_BEGIN_HEADER      WSI_BEGIN_HEADER_CXX
#	define WSI_END_HEADER        WSI_END_HEADER_CXX
#   define WSI_BEGIN_HEADER_HPP  WSI_BEGIN_HEADER_CXX { namespace tpl {
#   define WSI_END_HEADER_HPP    WSI_END_HEADER_HPP   }}
#   define WSI_BEGIN_OBJC        
#   define WSI_END_OBJC          
#   define WSI_BEGIN_C           extern "C" {
#   define WSI_END_C             }
#   define WSI_NEED_CXX
# else
#   define WSI_USINGCXXNAMESPACE
#	define WSI_BEGIN
#	define WSI_END
#	define WSI_BEGIN_HEADER_C
#	define WSI_END_HEADER_C
#	define WSI_BEGIN_HEADER      WSI_BEGIN_HEADER_C
#	define WSI_END_HEADER        WSI_END_HEADER_C
#   define WSI_BEGIN_OBJC
#   define WSI_END_OBJC
#   define WSI_BEGIN_C
#   define WSI_END_C
#   define WSI_NEED_CXX          error, must be built as c++ source file.
# endif

# ifdef WSI_CXX
#   define CXXEXPRESS(exp) exp
# else
#   define CXXEXPRESS(exp)
# endif

# ifdef WSI_OBJC
#   define OBJCEXPRESS(exp) exp
# else
#   define OBJCEXPRESS(exp)
# endif

# if defined(__BLOCKS__)
#   define WSI_BLOCKS
# endif

# if defined(DEBUG) || defined(_DEBUG)
#   define WSI_DEBUG
# else
#   ifndef WSI_DEBUG
#     define WSI_RELEASE
#   endif
# endif

# ifdef WSI_DEBUG
#	define WSIDEBUG_EXPRESS(express)    express
#	define WSIRELEASE_EXPRESS(express)
# endif

# ifdef WSI_RELEASE
#	define WSIDEBUG_EXPRESS(express)
#	define WSIRELEASE_EXPRESS(express)  express
# endif

# ifndef WSI_DEBUG
#  ifdef WSIDEBUG_BAR
#    undef WSIDEBUG_BAR
#  endif
# endif

# define SPACE
# define TODO(express) {SPACE}
# define PASS {SPACE}

# define WSIMACRO_SELF(val)                    val
# define _WSIMACRO_TOSTR(val)                  #val
# define WSIMACRO_TOSTR(val)                  _WSIMACRO_TOSTR(val)
# define WSIMACRO_COMBINE_2(v0, v1, sep)       WSIMACRO_SELF(v0)##sep##WSIMACRO_SELF(v1)
# define WSIAUTO_NAME                        __wsi_autoname_ ## __LINE__ ## __FUNCTION__

# ifdef WSI_OBJC

# define _WSIMACRO_TOSTR_OBJC(val)             @#val
# define WSIMACRO_TOSTR_OBJC(val)             _WSIMACRO_TOSTR_OBJC(val)

# define _WSIMACRO_TOSTR_OBJC2(val)            @val
# define WSIMACRO_TOSTR_OBJC2(val)            _WSIMACRO_TOSTR_OBJC2(val)

# endif

# ifdef WSI_MSVC
#   define WSI_NOVTABLE __declspec(novtable)
#   define typename_
# else
#   define WSI_NOVTABLE
#   define typename_ typename 
# endif

# define interface_ struct
# define abstrace_

# ifdef WSI_C
#   define _not_  !
#   define _xor_  ^
#   define _and_  &
#   define _or_   |
# endif

# ifdef WSI_OBJC

# import <Foundation/Foundation.h>

# if TARGET_OS_IPHONE
# import <UIKit/UIKit.h>
# endif

# define is_no == NO
# define is_yes == YES

# ifdef WSI_CXX

class segment_accel_type
{
    public:
    
    segment_accel_type()
    {
        pool = [[NSAutoreleasePool alloc] init];
    }
    
    ~segment_accel_type()
    {
        [pool drain];
    }
    
    NSAutoreleasePool* pool;
};

# define segment_accel segment_accel_type __wsi_accel_segment;

# endif

# endif

# ifndef ENUM_DEFINED
typedef unsigned int enum_t;
# endif

# ifndef WORD_DEFINED
typedef short word;
# endif

# ifndef UWORD_DEFINED
typedef unsigned short uword;
# endif

# ifndef DWORD_DEFINED
typedef int dword;
# endif

# ifndef QWORD_DEFINED
typedef long long qword;
# endif

# ifndef LONGLONG_DEFINED
typedef long long longlong;
# endif

# ifndef UQWORD_DEFINED
typedef unsigned long long uqword;
# endif

# ifndef ULONGLONG_DEFINED
typedef unsigned long long ulonglong;
# endif

# ifndef UDWORD_DEFINED
typedef unsigned int udword;
# endif

# ifndef UCHAR_DEFINED
typedef unsigned char uchar;
# endif

# ifndef UBYTE_DEFINED
typedef unsigned char ubyte;
# endif

# ifndef SCHAR_DEFINED
typedef signed char schar;
# endif

# ifndef SBYTE_DEFINED
typedef signed char sbyte;
# endif

# ifndef UBYTE_DEFINED
typedef ubyte byte;
# endif

# ifndef UINT_DEFINED
typedef unsigned int uint;
# endif

# ifndef USHORT_DEFINED
typedef unsigned short ushort;
# endif

# ifndef ULONG_DEFINED
typedef unsigned long ulong;
# endif

typedef ulong uenum;

#ifdef WSI_X64
   typedef double real;
#  define REAL_IS_DOUBLE  1
   typedef ulong uindex, usize, uinteger;
   typedef long sindex, ssize, sinteger;
#else
   typedef float real;
#  define REAL_IS_FLOAT   1
   typedef uint uindex, usize, uinteger;
   typedef int sindex, ssize, sinteger;
#endif

typedef struct _point3df
{
    real x, y, z;
} point3df;

typedef struct _point3di
{
    int x, y, z;
} point3di;

// as color-32bit percent

# define AS_C32P(val)        ((val) * 0.00392156862745)

# define RGBA_RED(value)     (((value) >> 24) & 0xFF)
# define RGBA_GREEN(value)   (((value) & 0xFF0000) >> 16)
# define RGBA_BLUE(value)    (((value) & 0xFF00) >> 8)
# define RGBA_ALPHA(value)   ((value) & 0xFF)

# define RGBA_RED_P(value)   AS_C32P(RGBA_RED(value))
# define RGBA_GREEN_P(value) AS_C32P(RGBA_GREEN(value))
# define RGBA_BLUE_P(value)  AS_C32P(RGBA_BLUE(value))
# define RGBA_ALPHA_P(value) AS_C32P(RGBA_ALPHA(value))

# define ARGB_RED(value)     (((value) & 0xFF0000) >> 16)
# define ARGB_GREEN(value)   (((value) & 0xFF00) >> 8)
# define ARGB_BLUE(value)    ((value) & 0xFF)
# define ARGB_ALPHA(value)   (((value) >> 24) & 0xFF)

# define ARGB_RED_P(value)   AS_C32P(ARGB_RED(value))
# define ARGB_GREEN_P(value) AS_C32P(ARGB_GREEN(value))
# define ARGB_BLUE_P(value)  AS_C32P(ARGB_BLUE(value))
# define ARGB_ALPHA_P(value) AS_C32P(ARGB_ALPHA(value))

# define RGB_ALPHA(value)    0xFF
# define RGB_RESTRICT(value) (((value) <= 0xFF) ? (value) : 0xFF)
# define RGB_RED             ARGB_RED
# define RGB_GREEN           ARGB_GREEN
# define RGB_BLUE            ARGB_BLUE

# define RGB_ALPHA_P(value)  1.f
# define RGB_RED_P           ARGB_RED_P
# define RGB_GREEN_P         ARGB_GREEN_P
# define RGB_BLUE_P          ARGB_BLUE_P

# define ARGB2RGBA(value)    (((value) << 8) | ARGB_ALPHA(value))
# define RGBA2ARGB(value)    (((value) >> 8) | (RGBA_ALPHA(value) << 24))

# define RGBA(red, green, blue, alpha) (((int)(red) << 24) | ((int)(green) << 16) | ((int)(blue) << 8) | (int)(alpha))
# define ARGB(red, green, blue, alpha) (((int)(alpha) << 24) | ((int)(red) << 16) | ((int)(green) << 8) | (int)(blue))

# ifndef RGB
#   define RGB(red, green, blue)         (((int)(red) << 16) | ((int)(green) << 8) | (int)(blue))
# endif

# define RGBA_MUL(value, mul) RGBA(RGBA_RED(value) * (mul), RGBA_GREEN(value) * (mul), RGBA_BLUE(value) * (mul), RGBA_ALPHA(value))
# define ARGB_MUL(value, mul) ARGB(ARGB_RED(value) * (mul), ARGB_GREEN(value) * (mul), ARGB_BLUE(value) * (mul), ARGB_ALPHA(value))
# define RGB_MUL              ARGB_MUL

# define RGBA_ADD_RGBA_RED(v0, v1)     RGB_RESTRICT(RGBA_RED(v0) + RGBA_RED(v1))
# define RGBA_ADD_RGBA_GREEN(v0, v1)   RGB_RESTRICT(RGBA_GREEN(v0) + RGBA_GREEN(v1))
# define RGBA_ADD_RGBA_BLUE(v0, v1)    RGB_RESTRICT(RGBA_BLUE(v0) + RGBA_BLUE(v1))
# define RGBA_ADD_RGBA_ALPHA(v0, v1)   RGB_RESTRICT(RGBA_ALPHA(v0) + RGBA_ALPHA(v1))
# define RGBA_ADD_RGBA(v0, v1)         RGBA(RGBA_ADD_RGBA_RED(v0, v1), RGBA_ADD_RGBA_GREEN(v0, v1), RGBA_ADD_RGBA_BLUE(v0, v1),RGBA_ADD_RGBA_ALPHA(v0, v1))

# define ARGB_ADD_ARGB_RED(v0, v1)     RGB_RESTRICT(ARGB_RED(v0)   + ARGB_RED(v1))
# define ARGB_ADD_ARGB_GREEN(v0, v1)   RGB_RESTRICT(ARGB_GREEN(v0) + ARGB_GREEN(v1))
# define ARGB_ADD_ARGB_BLUE(v0, v1)    RGB_RESTRICT(ARGB_BLUE(v0)  + ARGB_BLUE(v1))
# define ARGB_ADD_ARGB_ALPHA(v0, v1)   RGB_RESTRICT(ARGB_ALPHA(v0) + ARGB_ALPHA(v1))
# define ARGB_ADD_ARGB(v0, v1)         ARGB(ARGB_ADD_ARGB_RED(v0, v1), ARGB_ADD_ARGB_GREEN(v0, v1), ARGB_ADD_ARGB_BLUE(v0, v1),ARGB_ADD_ARGB_ALPHA(v0, v1))

# define RGBA_SET_RED(value, val)    RGBA(val, RGBA_GREEN(value), RGBA_BLUE(value), RGBA_ALPHA(value))
# define RGBA_SET_GREEN(value, val)  RGBA(RGBA_RED(value), val, RGBA_BLUE(value), RGBA_ALPHA(value))
# define RGBA_SET_BLUE(value, val)   RGBA(RGBA_RED(value), RGBA_GREEN(value), val, RGBA_ALPHA(value))
# define RGBA_SET_ALPHA(value, val)  RGBA(RGBA_RED(value), RGBA_GREEN(value), RGBA_BLUE(value), val)

# define ARGB_SET_RED(value, val)    ARGB(val, ARGB_GREEN(value), ARGB_BLUE(value), ARGB_ALPHA(value))
# define ARGB_SET_GREEN(value, val)  ARGB(ARGB_RED(value), val, ARGB_BLUE(value), ARGB_ALPHA(value))
# define ARGB_SET_BLUE(value, val)   ARGB(ARGB_RED(value), ARGB_GREEN(value), val, ARGB_ALPHA(value))
# define ARGB_SET_ALPHA(value, val)  ARGB(ARGB_RED(value), ARGB_GREEN(value), ARGB_BLUE(value), val)

# define RGB_SET_RED                 ARGB_SET_RED
# define RGB_SET_GREEN               ARGB_SET_GREEN
# define RGB_SET_BLUE                ARGB_SET_BLUE
# define RGB_SET_ALPHA(value, val)   (value)

# define RGB_COMP_INV(value)         (0xff - (value))
# define ARGB_INV(value)             ARGB(RGB_COMP_INV(ARGB_RED(value)), RGB_COMP_INV(ARGB_GREEN(value)), RGB_COMP_INV(ARGB_BLUE(value)), ARGB_ALPHA(value))
# define RGBA_INV(value)             RGBA(RGB_COMP_INV(RGBA_RED(value)), RGB_COMP_INV(RGBA_GREEN(value)), RGB_COMP_INV(RGBA_BLUE(value)), RGBA_ALPHA(value))

# define MCOMMA ,
# define MDOT .
# define MSEMICOLON ;
# define MCOLON :

typedef union {
    struct { 
        byte r;
        byte g;
        byte b;
    } d;
    uint v:24;
    int sv:24;
} _rgb_ct;

# ifdef WSI_CXX

class _rgb_cxxt
{
public:
    
    _rgb_cxxt(uint v = 0)
    {
        val.v = v;
    }
    
    _rgb_cxxt(_rgb_ct const& r)
    : val(r)
    {
        PASS;
    }
    
    operator uint () const
    {
        return val.v;
    }
    
    _rgb_cxxt& operator = (uint v)
    {
        val.v = v;
        return *this;
    }
    
    byte red() const
    {
        return val.d.r;
    }
    
    byte green() const
    {
        return val.d.g;
    }
    
    byte blue() const
    {
        return val.d.b;
    }
    
    _rgb_ct val;
};

typedef _rgb_cxxt rgb_t;

# else

typedef _rgb_ct rgb_t;

# endif

inline_impl _rgb_ct rgb(uint v)
{
    _rgb_ct r;
    r.v = v;
    return r;
}

typedef union {
    struct { 
        byte r;
        byte g;
        byte b;
        byte a;
    } d;
    uint v;
    int sv;
} _rgba_ct;

# ifdef WSI_CXX

class _rgba_cxxt
{
public:
    
    _rgba_cxxt(uint v = 0)
    {
        val.v = v;
    }
    
    _rgba_cxxt(_rgba_ct const& r)
    : val(r)
    {
        PASS;
    }
    
    operator uint () const
    {
        return val.v;
    }
    
    _rgba_cxxt& operator = (uint v)
    {
        val.v = v;
        return *this;
    }
    
    byte red() const
    {
        return val.d.r;
    }
    
    byte green() const
    {
        return val.d.g;
    }
    
    byte blue() const
    {
        return val.d.b;
    }
    
    byte alpha() const
    {
        return val.d.a;
    }
    
    _rgba_ct val;
};

typedef _rgba_cxxt rgba_t;

# else

typedef _rgba_ct rgba_t;

# endif

inline_impl _rgba_ct rgba(uint v)
{
    _rgba_ct r;
    r.v = v;
    return r;
}

typedef union {
    struct {
        byte a;
        byte r;
        byte g;
        byte b;
    } d;
    uint v;
    int sv;
} _argb_ct;

# ifdef WSI_CXX

class _argb_cxxt
{
public:
    
    _argb_cxxt(uint v = 0)
    {
        val.v = v;
    }
    
    _argb_cxxt(_argb_ct const& r)
    : val(r)
    {
        PASS;
    }
    
    operator uint () const
    {
        return val.v;
    }
    
    _argb_cxxt& operator = (uint v)
    {
        val.v = v;
        return *this;
    }
    
    byte red() const
    {
        return val.d.r;
    }
    
    byte green() const
    {
        return val.d.g;
    }
    
    byte blue() const
    {
        return val.d.b;
    }
    
    byte alpha() const
    {
        return val.d.a;
    }
    
    _argb_ct val;
};

typedef _argb_cxxt argb_t;

# else

typedef _argb_ct argb_t;

# endif

inline_impl _argb_ct argb(uint v)
{
    _argb_ct r;
    r.v = v;
    return r;
}

// 32 bits map as h1 h0 l1 l0
# define b32_h1(val)                     (((val) & 0xFF000000) >> 24)
# define b32_h0(val)                     (((val) & 0xFF0000) >> 16)
# define b32_l1(val)                     (((val) & 0xFF00) >> 8)
# define b32_l0(val)                     ((val) & 0xFF)
# define b32_h(val)                      (((val) & 0xFFFF0000) >> 16)
# define b32_l(val)                      ((val) & 0xFFFF)
# define b32_make(h1, h0, l1, l0)        (((h1) << 24) | ((h0) << 16) | ((l1) << 8) | (l0))

# define b8_h(val)                       (((val) >> 4) & 0xf)
# define b8_l(val)                       ((val) & 0xf)
# define b8_make(h, l)                   ((h) << 4 | (l))

# define b16_h(val)                      (((val) >> 8) & 0xff)
# define b16_l(val)                      ((val) & 0xff)
# define b16_make(h, l)                  ((h) << 8 | (l))

# define endian_8(val)                   (val)
# define endian_16(val)                  ((((val) & 0xFF) << 8) | (((val) & 0xFF00) >> 8))
# define endian_24(val)                  ((((val) & 0xFF) << 16) | ((val) & 0xFF00) | (((val) & 0xFF0000) >> 16))
# define endian_32(val)                  b32_make(b32_l0(val), b32_l1(val), b32_h0(val), b32_h1(val))

# define bit_at(val, pos)                ((val) & (1 << (pos)))
# define bits_range(val, from, to)  (((val) >> (from)) & (0xffffffff >> (to)))

# ifdef WSI_OBJC

# define WSIDECL_PRIVATE_HEAD(cls) @class cls; @class cls##Private
# define WSIDECL_PRIVATE(cls) @private cls##Private *d_ptr;
# define WSIDECL_PRIVATE_INIT(cls) { if (d_ptr == nil) {d_ptr = [cls##Private alloc]; d_ptr.d_owner = self; [d_ptr init]; }}
# define WSIDECL_PRIVATE_DEALLOC() [d_ptr release];
# define WSIDECL_PRIVATE_EX(cls, name) @private cls##Private *name;
# define WSIDECL_PRIVATE_INIT_EX(cls, name) { if (name == nil) { name = [cls##Private alloc]; name.d_owner = self; [name init]; }}
# define WSIDECL_PRIVATE_DEALLOC_EX(name) [name release];
# define WSIDECL_D(cls) WSIDECL_PRIVATE_INIT(cls);
# define WSIDECL_PRIVATE_BEGIN(cls, base) @interface cls##Private : base
# define WSIDECL_PRIVATE_IMPL(cls) \
@property (nonatomic, assign) cls* d_owner; \
@end \
@implementation cls##Private \
@synthesize d_owner;
# define WSIDECL_PRIVATE_END @end

# endif

# ifdef WSI_CXX

# define WSIDECL_PRIVATE_NAME(cls)\
cls##Private

# define WSIDECL_PRIVATE_HEAD_CXX(cls) \
class cls; class cls##Private;

# define WSIDECL_PRIVATE_CXX(cls) \
friend class cls##Private; \
typedef cls##Private private_type; \
private_type* d_ptr;

# define WSIDECL_PRIVATE_CONSTRUCT(cls) \
d_ptr = new private_type(this);

# define WSIDECL_PRIVATE_DESTROY() \
delete d_ptr;

# define WSIDECL_PRIVATE_BEGIN_CXX(cls) \
class cls##Private : public ::wsi::cxx::Object<> { \
typedef cls##Private self_type, private_type, _class; \
typedef cls owner_type; \
owner_type* d_owner; \
friend class cls; \
cls##Private(cls* obj) : d_owner(obj) { init(); } \
~cls##Private() { dealloc(); }

# define WSIDECL_PRIVATE_END_CXX };

# define WSI_PRIVATE() \
if (d_ptr == NULL) \
d_ptr = new private_type(this);

# define WSIDECL_NOCOPY(cls) \
private: cls(cls const&); cls& operator = (cls const&);

# define WSIDECL_NOCOPY_EX(cls, impl) \
private: cls(impl const&); impl& operator = (impl const&);

# define WSIDECL_NONEW(cls) \
private: static void* operator new (size_t); static void* operator new[] (size_t);

# ifndef WSIDECL_PRIVATE_BEGIN
#   define WSIDECL_PRIVATE_BEGIN WSIDECL_PRIVATE_BEGIN_CXX
# endif

# ifndef WSIDECL_PRIVATE_END
#   define WSIDECL_PRIVATE_END WSIDECL_PRIVATE_END_CXX
# endif

# ifndef WSIDECL_PRIVATE
#   define WSIDECL_PRIVATE WSIDECL_PRIVATE_CXX
# endif

# ifndef WSIDECL_PRIVATE_HEAD
#   define WSIDECL_PRIVATE_HEAD WSIDECL_PRIVATE_HEAD_CXX
# endif

# endif

# if !defined (WSI_EXPORT)
#   ifdef WSI_MSVC
#     define WSI_EXPORT __declspec(dllexport)
#     define WSI_IMPORT __declspec(dllimport)
#   else
#     define WSI_EXPORT __attribute__((visibility("default")))
#     define WSI_IMPORT 
//__attribute__((visibility("default")))
#   endif
# endif

# if !defined (WSI_CONSTRUCTOR)
#   define WSI_CONSTRUCTOR __attribute__((constructor))
# endif

# if !defined (WSI_DESTRUCTOR)
#   define WSI_DESTRUCTOR __attribute__((destructor))
# endif

# if !defined (WSI_EXTERN)
#   if defined WSI_CXX
#      define WSI_EXTERN_C extern "C"
#   else
#      define WSI_EXTERN_C extern
#   endif
#   define WSI_EXTERN extern
# endif

# if defined(LIBWSI)
#   define WSIAPI(retype) WSI_EXPORT retype
#   define WSICLASS(cls)  class WSI_EXPORT cls
#   define WSINTERFACE(itr) interface_ WSI_EXPORT itr
//#   define WSIVAR(retype) WSI_EXTERN WSI_EXPORT retype
# else
#   define WSIAPI(retype) WSI_IMPORT retype
#   define WSICLASS(cls)  class WSI_IMPORT cls
#   define WSINTERFACE(itr) interface_ WSI_IMPORT itr
//#   define WSIVAR(retype) WSI_EXTERN retype WSI_IMPORT 
# endif

# if defined(WSI_LIBRARY)
#   define WSIAPPCLASS(cls) class WSI_EXPORT cls
# else
#   define WSIAPPCLASS(cls) class WSI_IMPORT cls
# endif

// kernel

# ifdef WSI_MACH

# if defined(TARGET_IPHONE_SIMULATOR) && TARGET_IPHONE_SIMULATOR
#    define WSISIM_EXPRESS(exp) exp
#    define WSI_SIMULATOR
# else
#    define WSISIM_EXPRESS(exp) SPACE
#    define WSI_DEVICE
# endif

# if (defined(TARGET_IPHONE_SIMULATOR) && TARGET_IPHONE_SIMULATOR) || (defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE)
#    define WSIOS_EXPRESS(exp) exp
# else
#    define WSIOS_EXPRESS(exp) SPACE
# endif

# if TARGET_OS_IPHONE
#    define WSI_TARGET_IOS 1
#    define IOSEXPRESS(exp) exp
#    define MACEXPRESS(exp) SPACE
#    define MAC_IOS_SELECT(mac, ios) ios
#    define WSI_ISPAD (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
#    define WSI_ISPHONE !WSI_ISPAD
# elif TARGET_OS_MAC
#    define WSI_TARGET_MAC 1
#    define IOSEXPRESS(exp) SPACE
#    define MACEXPRESS(exp) exp
#    define MAC_IOS_SELECT(mac, ios) mac
# endif

# endif

# ifndef WSI_TARGET_OS
#   define WSI_CROSS_PLATFORM 1
# endif

# define WSI_BEGIN_NS(ns)        namespace ns {
# define WSI_END_NS              }

# ifdef WSI_CXX
#   define WSI_BEGIN_HEADER_OBJC   WSI_BEGIN_HEADER_C
#   define WSI_END_HEADER_OBJC     WSI_END_HEADER_C
# else
#   define WSI_BEGIN_HEADER_OBJC
#   define WSI_END_HEADER_OBJC
# endif

# ifdef WSI_GCC

#   define WSI_ATOMIC_ADD(x, v) __sync_fetch_and_add(&x, v)
#   define WSI_ATOMIC_SUB(x, v) __sync_fetch_and_sub(&x, v)

#   define WSI_ADD_ATOMIC(x, v) __sync_add_and_fetch(&x, v)
#   define WSI_SUB_ATOMIC(x, v) __sync_sub_and_fetch(&x, v)

# elif defined(WSI_MSVC)

#   define WSI_ATOMIC_ADD(x, v) InterlockedAdd(&x, v)
#   define WSI_ATOMIC_SUB(x, v) InterlockedAdd(&x, -v)

#   define WSI_ADD_ATOMIC(x, v) InterlockedExchange(&x, v)
#   define WSI_SUB_ATOMIC(x, v) InterlockedExchange(&x, -v)

# endif

#   define WSI_ATOMIC_INC(x) WSI_ADD_ATOMIC(x, 1)
#   define WSI_ATOMIC_DEC(x) WSI_SUB_ATOMIC(x, 1)

# ifdef WSI_OBJC
#   define WSIDECL_EXTERN_CLASS_OBJC(cls)      @class cls;
#   define WSIDECL_EXTERN_INTERFACE_OBJC(cls)  @protocol cls;
#   define WSIDECL_EXTERN_DELEGATE_OBJC(cls)   @protocol cls##Delegate;
# endif

# ifdef WSI_CXX
#   define WSIDECL_EXTERN_CLASS_CXX(cls)      class cls;
#   define WSIDECL_EXTERN_INTERFACE_CXX(cls)  struct cls;
#   define WSIDECL_EXTERN_DELEGATE_CXX(cls)   class cls##Delegate;
#   define WSIDECL_EXTERN_CLASS_NS(ns, cls)   namespace ns { class cls; }
#   define WSIDECL_EXTERN_CLASS_NS2(ns1, ns2, cls) namespace ns1 { namespace ns2 { class cls; }}
#   define WSIDECL_EXTERN_CLASS_NS3(ns1, ns2, ns3, cls) namespace ns1 { namespace ns2 { namespace ns3 { class cls; }}}
#   define WSIDECL_EXTERN_CLASS_NS4(ns1, ns2, ns3, ns4, cls) namespace ns1 { namespace ns2 { namespace ns3 { namespace ns4 { class cls; }}}}
#   define WSIDECL_INTERFACE(cls) public: virtual ~cls() {}
# endif

# ifdef WSI_OBJC
#   define WSIDECL_EXTERN_CLASS               WSIDECL_EXTERN_CLASS_OBJC
#   define WSIDECL_EXTERN_INTERFACE           WSIDECL_EXTERN_INTERFACE_OBJC
#   define WSIDECL_EXTERN_DELEGATE            WSIDECL_EXTERN_DELEGATE_OBJC
# else
#   define WSIDECL_EXTERN_CLASS               WSIDECL_EXTERN_CLASS_CXX
#   define WSIDECL_EXTERN_INTERFACE           WSIDECL_EXTERN_INTERFACE_CXX
#   define WSIDECL_EXTERN_DELEGATE            WSIDECL_EXTERN_DELEGATE_CXX
# endif

# define WSIDECL_EXTERN_PROTOCOL WSIDECL_EXTERN_INTERFACE

# define MIN_NOT(l, r, n) (((l) == (n)) ? (r) : MIN((l), (r)))
# define MAX_NOT(l, r, n) (((l) == (n)) ? (r) : MAX((l), (r)))
# define TRIEXP(sel, tru, fla) ((sel) ? (tru) : (fla))

# define MASK_CHECK(mask, val) (((mask) & (val)) == (mask))
# define MASK_SET(mask, val) \
{ if (MASK_CHECK(mask, val) == false) val |= mask; }
# define MASK_UNSET(mask, val) \
{ if (MASK_CHECK(mask, val)) val ^= mask; }

# ifdef WSI_DEBUG
#	define WSIDEBUG_BREAK WSIDEBUG_EXPRESS(__asm__ int 3)
#	define WSIDEBUG_BREAK_IF(express) WSIDEBUG_EXPRESS(if (express) WSIDEBUG_BREAK)
#	define WSIDEBUG_ASSERT(express) WSIDEBUG_EXPRESS_IF(!(express))
# else
#	define WSIDEBUG_BREAK SPACE
#	define WSIDEBUG_BREAK_IF(express) SPACE
#	define WSIDEBUG_ASSERT(express) SPACE
# endif

# define WSIDECL_CATEGORY(name, cate) \
    @interface WSI_FIX_CATEGORY_LINKBUG_##name##_##cate : name @end

# define WSIIMPL_CATEGORY(name, cate) \
    @implementation WSI_FIX_CATEGORY_LINKBUG_##name##_##cate @end

# define WSIUSE_CATEGORY(name, cate) \
    extern name* __WSI_FIX_CATEGORY_LINKBUG_##name##_##cate (void); \
    name* __WSI_FIX_CATEGORY_LINKBUG_##name##_##cate (void) { WSI_FIX_CATEGORY_LINKBUG_##name##_##cate *ret = [WSI_FIX_CATEGORY_LINKBUG_##name##_##cate new]; return ret; }

# define WSICALL_CATEGORY(name, cate) \
    __WSI_FIX_CATEGORY_LINKBUG_##name##_##cate()

# ifdef WSI_OBJC
# define _W(str) NSLocalizedString(str, SPACE)
# else
# define _W(str) L##str
# endif

# ifdef LIBWSI
#   define WSILIB_EXPRESS(exp) exp
#   define WSIBIN_EXPRESS(exp) SPACE
# else
#   define WSILIB_EXPRESS(exp) SPACE
#   define WSIBIN_EXPRESS(exp) exp
# endif

# ifdef WSI_OBJC
WSI_BEGIN_HEADER_C
extern void _trace_obj         (NSString*, id);
extern void _trace_int         (NSString*, int);
extern void _trace_float       (NSString*, float);
extern void _trace_msg         (NSString*);
WSI_END_HEADER_C

/*
# ifdef WSI_CXX
template <typename StrT>
inline void _trace_msg(StrT const& str) { _trace_msg([NSString stringWithUTF8String:str.c_str()]); }
inline void _trace_msg(char const* str) { _trace_msg([NSString stringWithUTF8String:str]); }
# endif
 */

# endif

# ifdef WSI_DEBUG
#   ifdef WSI_OBJC
#     define trace_rc(obj)       { NSLog(@ #obj "'s retain count is %d ." , [obj retainCount]); }
#     define trace_obj(obj)      _trace_obj(@#obj, obj)
#     define trace_int(val)      _trace_int(@#val, val)
#     define trace_float(val)    _trace_float(@#val, val)
#     define trace_msg(msg)      _trace_msg(msg)
#     define trace_fmt(...)      _trace_msg([NSString stringWithFormat:__VA_ARGS__])
#     define trace_if(exp, msg)  { if (exp) { trace_msg(@ #exp "=> " msg); } }
#     define dthrow(ex)          @throw ex
#     define dexpress(ex)        ex
#   else // non obj-c.

#     define trace_int(val)      printf("%d\n", val)
#     define trace_float(val)    printf("%f\n", val)

#     include <stdio.h>

#     ifdef WSI_CXX

#       ifdef WSI_MSVC

inline_impl void trace_msg(char const* msg)
{
    ::OutputDebugStringA(msg);
    ::OutputDebugStringA("\n");
}

inline_impl void trace_msg(char* msg)
{
    ::OutputDebugStringA(msg);
    ::OutputDebugStringA("\n");
}

template <typename T>
inline_impl void trace_msg(T const& str)
{
    trace_msg(str.c_str());
}

#       else // none msvc.

#       include <iostream>

inline_impl void trace_msg(char const* msg)
{
    ::std::cout << msg << ::std::endl << ::std::flush;
}

inline_impl void trace_msg(char* msg)
{
    ::std::cout << msg << ::std::endl << ::std::flush;
}

template <typename T>
inline_impl void trace_msg(T const& str)
{
    ::std::cout << str << ::std::endl << ::std::flush;
}

#       endif // msvc.

#     else // non cxx.

inline_impl void trace_msg(char const* msg) {
    printf(msg, 0);
    printf("\n");
    fflush(stdout);
}

#     endif // cxx.

//#     define trace_fmt(...)      
#     define trace_if(exp, msg)  { if (exp) { trace_msg(#exp "=> " msg); } }
#     define dthrow(ex)          { throw ex; }
#     define dexpress(ex)        { ex; }
#   endif // obj-c.
# else // non-debug.
#   define trace_rc(obj)       {SPACE}
#   define trace_obj(obj)      {SPACE}
#   define trace_int(val)      {SPACE}
#   define trace_float(val)    {SPACE}
#   define trace_msg(msg)      {SPACE}
#   define trace_fmt(...)      {SPACE}
#   define trace_if(exp, msg)  {SPACE}
#   define dthrow(ex)          {SPACE}
#   define dexpress(ex)        {SPACE}
# endif // debug.

# ifdef WSI_OBJC
#   define dthrow_msg(title, msg) dthrow([NSException exceptionWithName:title reason:msg userInfo:nil]);
# elif defined(WSI_CXX)
#   define dthrow_msg(title, msg) dthrow(::wsi::exception::message(msg, title))
# else
#   define dthrow_msg(title, msg)
# endif

# define b00000001 1
# define b00000010 2
# define b00000100 4
# define b00001000 8
# define b00010000 16
# define b00100000 32
# define b01000000 64
# define b10000000 128

# define GB2B 1073741824
# define MB2B 1048576
# define MB2KB 1024
# define B2GB 9.31322574615479e-10
# define B2MB 9.5367431640625e-7
# define B2KB 9.765625e-4
# define GOLDENRATIO 1.6180339887
# define GOLDENRATIO_1 0.6180339887
# define GOLDENRATIO_1_1 0.3819660113

# define DT_1MIN 60
# define DT_3MIN 180
# define DT_5MIN 300
# define DT_7MIN 420
# define DT_9MIN 540
# define DT_10MIN 600
# define DT_15MIN 900
# define DT_20MIN 1200
# define DT_30MIN 1800
# define DT_40MIN 2400
# define DT_1HOUR 3600
# define DT_3HOUR 10800
# define DT_6HOUR 21600
# define DT_12HOUR 43200
# define DT_1DAY 86400
# define DT_3DAY 259200
# define DT_1WEEK 604800
# define DT_2WEEK 1209600
# define DT_1MON 2592000
# define DT_1YEAR 946080000

inline_impl void* ptr_offset(void* ptr, usize val)
{
    return (void*)((byte*)ptr + val);
}

# if defined(WSI_C) && !defined(WSI_OBJC)
typedef int bool;
# ifndef true
#   define true  1
# endif
# ifndef false
#   define false 0
# endif
# endif

# ifdef WSI_OBJC
#   define OBJCMutable 1
#   define OBJCNormal  0
# endif

//! @macro self_release auto release once after alloc
# ifdef WSI_OBJC
#   define self_release(express) [(express) release]
#   define safe_release(obj) { if (1 == [obj retainCount]) { [obj release]; obj = nil; } else { [obj release]; } }
#   define zero_release(obj) { [obj release]; obj = nil; }
#   define safe_replace(src, obj) { safe_release(src); src = obj; }
# else
//#   define self_release(express) {}
//#   define safe_release(obj) {}
//#   define zero_release(obj) {}
# endif

# define safe_delete(obj) { if (obj) { delete obj; obj = 0; } }
# define safe_delete_arr(arr) { if (arr) { delete [] arr; arr = 0; } }
# define safe_delete_type(obj, type) { if (obj) { delete (type)obj; obj = 0; } }
# define safe_delete_arr_type(arr, type) { if (arr) { delete [] (type)arr; arr = 0; } }
# define zero_drop(obj) { if(obj) { obj->drop(); obj = 0; } }
# define safe_drop(obj) { if (obj && obj->drop()) obj = 0; }
# define safe_grab(obj) { if (obj) obj->grab(); }

WSI_BEGIN_HEADER_C

WSIAPI(void) sleep_second(ulonglong);
WSIAPI(void) sleep_millisecond(ulonglong);
WSIAPI(void) sleep_microsecond(ulonglong);
WSIAPI(void) sleep_nanosecond(ulonglong);
WSIAPI(ulong) timestamp();

WSI_END_HEADER_C

# ifndef IN
#   define IN
# endif

# ifndef OUT
#   define OUT
# endif

# ifndef INOUT
#   define INOUT
# endif

# ifndef NEED
#   define NEED
# endif

# ifndef OPTIONAL
#   define OPTIONAL
# endif

# ifndef RESULT
#   define RESULT
# endif

static void null_func(void) {};
typedef struct {} null_struct;
C_EXPRESS( typedef struct {} null_op; \
typedef struct {} null_obj; \
);
CXX_EXPRESS( class null_class { \
public: \
    void operator ()() {} \
    void operator ()(void*) {} \
    void operator ()(void*, void*) {} \
}; typedef null_class null_op; \
template <typename ValT> struct null_obj {}; \
);
typedef null_struct error_op;

typedef struct { CXX_EXPRESS(enum { VALUE=1 };) } true_op;
typedef struct { CXX_EXPRESS(enum { VALUE=0 };) } false_op;

typedef struct _int_b8 {
    char _0;
    char _1;
    char _2;
    char _3;
} int_b8;

typedef struct _short_b8 {
    char _0;
    char _1;
} short_b8;

typedef struct _char_b4 {
    int _0:4;
    int _1:4;
} char_b4;

typedef struct _int_b4 {
    int _0:4;
    int _1:4;
    int _2:4;
    int _3:4;
    int _4:4;
    int _5:4;
    int _6:4;
    int _7:4;
} int_b4;

typedef struct _short_b4 {
    int _0:4;
    int _1:4;
    int _2:4;
    int _3:4;
} short_b4;

typedef enum _WSIValueType {
    WSIValueTypeUnknown,
    WSIValueTypeInt,
    WSIValueTypeUInt,
    WSIValueTypeShort,
    WSIValueTypeUShort,
    WSIValueTypeChar,
    WSIValueTypeUChar,
    WSIValueTypeLong,
    WSIValueTypeULong,
    WSIValueTypeLongLong,
    WSIValueTypeULongLong,
    WSIValueTypeString,
    WSIValueTypeFloat,
    WSIValueTypeDouble,
} WSIValueType;

typedef struct {
    uint major;
    uint minor;
    uint patch;
    char const* ver;
} version_t;

//! 0: equal, 1: greater, -1: lesser
extern int VersionCmp(version_t const* l, version_t const* r);

# ifdef WSI_CXX

# define WSI_OPERATOR_IMPL(type) \
inline_impl bool operator != (type const& l, type const& r) \
{ return !(l == r); } \
inline_impl bool operator <= (type const& l, type const& r) \
{ return (l < r) || (l == r); } \
inline_impl bool operator >= (type const& l, type const& r) \
{ return (l > r) || (l == r); }

inline_impl bool operator == (version_t const& l, version_t const& r)
{
    return 0 == VersionCmp(&l, &r);
}

inline_impl bool operator < (version_t const& l, version_t const& r)
{
    return -1 == VersionCmp(&l, &r);
}

inline_impl bool operator > (version_t const& l, version_t const& r)
{
    return 1 == VersionCmp(&l, &r);
}

WSI_OPERATOR_IMPL(version_t);

# endif

# ifdef WSI_LIBONLY
#   undef WSI_LIBONLY
# endif
//# define WSI_LIBONLY                1

// wsi preprocess define.
# define WSI_VERSION_MAJOR			1
# define WSI_VERSION_MIN			0
# define WSI_VERSION_FIX			0
# define WSI_CODENAME               strawberry

// configuration.
# define WSI_VERSION_STR            WSIMACRO_TOSTR(WSI_VERSION_MAJOR) "_" WSIMACRO_TOSTR(WSI_VERSION_MIN) "_" WSIMACRO_TOSTR(WSI_VERSION_FIX)
# define WSI_VERSION_VALUE          ((WSI_VERSION_MAJOR << 16 & 0xff0000) | (WSI_VERSION_MIN << 8 & 0xff00) | (WSI_VERSION_FIX & 0xff))
# define WSI_CODENAME_STR           WSIMACRO_TOSTR(WSI_CODENAME)

WSI_STATIC_CONST version_t WSIVERSION = {WSI_VERSION_MAJOR, WSI_VERSION_MIN, WSI_VERSION_FIX, WSI_VERSION_STR};

WSI_BEGIN_HEADER_C

//! get version string.
WSIAPI(char const*) WSIVersion();

WSI_END_HEADER_C

# define WSI_SETTING_BUNDLE			@"Settings.bundle"
# define WSI_SETTING_FILE			@"Root.plist"
# define WSI_USE_SBJSON				1
# define WSI_USE_TBXML              1
# define WSI_USE_BASE64             1
# define WSI_USE_COREPLOT           1
# define WSI_USE_BDB                1
# define WSI_USE_OPENCV             1
# define WSI_DEBUGBAR_HEIGHT        20

// team infomation.
# define WSI_BASE_URL				wybosys.com
# define WSI_BASE_DOMAIN            com.wybosys.wsi
# define WSI_PROJECT_URL            sf.net/p/libwsi
# define WSI_PROJECT_DOMAIN         WSI_BASE_DOMAIN
# define WSI_MAJOR_AUTHOR           wybosys <wybosys@gmail.com>
# define WSI_FEEDBACK_EMAIL         wybosys@gmail.com

//! build for iOS version. <=
# define WSI_iOS                    0x4FF

//! the framework is build for AppStore.
# define WSI_APPSTORE               1

//! the framework is build for test jailbreak device or private device.
# define WSI_JAILBREAK              0

# if WSI_APPSTORE == 0
#   undef WSI_APPSTORE
# endif

# if WSI_JAILBREAK == 0
#   undef WSI_JAILBREAK
# endif

# ifdef WSI_APPSTORE
#   ifdef WSI_JAILBREAK
#     ifndef WSI_DEBUG
#       undef WSI_JAILBREAK
#     else
#       define WSI_JAILBREAK_DEBUG
#     endif
#   endif
# endif

# if !WSI_VERBOSE
#   undef WSI_VERBOSE
# endif

# if !WSI_VERBOSE_VERBOSE
#   undef WSI_VERBOSE_VERBOSE
# endif

# ifdef WSI_DEBUG
# else
#   ifdef WSI_VERBOSE
#     undef WSI_VERBOSE
#   endif
#   ifdef WSI_VERBOSE_VERBOSE
#     undef WSI_VERBOSE_VERBOSE
#   endif
# endif

# ifdef WSI_TARGET_IOS

# if WSI_iOS < 0x300
#   define WSI_iOS_1
#   define WSI_iOS_2
#   define WSI_iOS2
#   undef __IPHONE_OS_VERSION_MAX_ALLOWED
#   define __IPHONE_OS_VERSION_MAX_ALLOWED __IPHONE_2_2
# endif

# if WSI_iOS < 0x400 && WSI_iOS >= 0x300
#   define WSI_iOS_1
#   define WSI_iOS_2
#   define WSI_iOS_3
#   define WSI_iOS3
#   undef __IPHONE_OS_VERSION_MAX_ALLOWED
#   define __IPHONE_OS_VERSION_MAX_ALLOWED __IPHONE_3_2
# endif

# if WSI_iOS < 0x500 && WSI_iOS >= 0x400
#   define WSI_iOS_1
#   define WSI_iOS_2
#   define WSI_iOS_3
#   define WSI_iOS_4
#   define WSI_iOS4
#   undef __IPHONE_OS_VERSION_MAX_ALLOWED
#   define __IPHONE_OS_VERSION_MAX_ALLOWED __IPHONE_4_3
# endif

# if WSI_iOS < 0x600 && WSI_iOS >= 0x500
#   define WSI_iOS_1
#   define WSI_iOS_2
#   define WSI_iOS_3
#   define WSI_iOS_4
#   define WSI_iOS_5
#   define WSI_iOS5
#   undef __IPHONE_OS_VERSION_MAX_ALLOWED
#   define __IPHONE_OS_VERSION_MAX_ALLOWED __IPHONE_5_0
# endif

# if WSI_iOS < 0x700 && WSI_iOS >= 0x600
#   define WSI_iOS_1
#   define WSI_iOS_2
#   define WSI_iOS_3
#   define WSI_iOS_4
#   define WSI_iOS_5
#   define WSI_iOS_6
#   define WSI_iOS6
#   undef __IPHONE_OS_VERSION_MAX_ALLOWED
#   define __IPHONE_OS_VERSION_MAX_ALLOWED __IPHONE_NA
# endif

# endif

// global include

# ifdef WSI_MSVC
#   pragma warning (disable: 4996)
#   pragma warning (disable: 4068)
#   pragma warning (disable: 4273)
#   pragma warning (disable: 4251)
#   pragma warning (disable: 4275) // disable dll-interface warning.
#   pragma warning (disable: 4819)
# endif

# ifdef WSI_CLANG
#   pragma GCC diagnostic ignored "-Wbind-to-temporary-copy"
#   ifdef WSI_DEBUG
#     pragma GCC diagnostic ignored "-Wshorten-64-to-32"
#   endif
# endif

# ifdef WSI_UNIX
#   include <unistd.h>
#   include <pthread.h>
#   include <sys/errno.h>
# endif

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <sys/types.h>
# include <signal.h>

# ifdef WSI_CXX

# include <iostream>
# include <iomanip>
# include <string>
# include <algorithm>

WSI_BEGIN_HEADER_CXX

//using namespace std;

struct _ignore_null;
typedef _ignore_null *ignore_null;

namespace cxx {}

# ifdef WSI_PURE_CXX
using namespace cxx;
# endif

WSI_END_HEADER_CXX

# endif

// include all base class.
# include "./Object.h"

// pre include objc's object for may inherited by C++ object.
# ifdef WSI_OBJC

#   ifdef WSI_TARGET_MAC
#     import <Cocoa/Cocoa.h>
#   endif

#   define NSInfinite NSNotFound
#   define discard assign
typedef struct {} objc_type;

#   import <Foundation/Foundation.h>
#   import "./NSObject+WSI.h"
#   import "./NSLock+WSI.h"

# endif

# ifndef autocollect
#   define autocollect
# endif

// include C++ Base Classes.
# include "../WTL/Exception+WSI.h"
# include "../WTL/Types+WSI.h"
# include "../WTL/Operator+WSI.h"
# include "../WTL/Function+WSI.h"
# include "../WTL/String+WSI.h"
# include "../WTL/Vector+WSI.h"
# include "../WTL/List+WSI.h"
# include "../WTL/Map+WSI.h"
//# include "../WTL/Bimap+WSI.h"
# include "../WTL/Tuple+WSI.h"
# include "../WTL/Data+WSI.h"
# include "../WTL/Algorithm+WSI.h"
# include "../WTL/Regex+WSI.h"
# include "../WTL/SmartPtr+WSI.h"
# include "../WTL/Closure+WSI.h"
# include "../WTL/Variant+WSI.h"

// ignore assert.
# include <assert.h>
# ifdef assert
#   define WSI_ASSERT assert
#   undef assert
# endif

// include unit test.
# include "UnitTest.h"

# ifdef WSI_OBJC

// include Objective-C Base Classes.
#   import "NSString+WSI.h"
#   import "NSNumber+WSI.h"
#   import "NSArray+WSI.h"
#   import "NSDictionary+WSI.h"
#   import "NSData+WSI.h"
#   import "NSSet+WSI.h"
#   import "NSIndex+WSI.h"
#   import "NSURL+WSI.h"
#   import "NSURLConnection+WSI.h"
#   import "NSDate+WSI.h"
#   import "NSLocale+WSI.h"
#   import "NSRunLoop+WSI.h"
#   import "Time+WSI.h"
#   import "Msgbox.h"
#   import "Console+WSI.h"

# endif

// hook
# ifdef WSI_OBJC

@interface func_object : NSObject {
	void* addr; //! address of function
	IMP imp; //! impl of object
};

@property (nonatomic) void* addr;
@property (nonatomic) IMP imp;

+ (func_object*)withAddr:(void*)addr;
+ (func_object*)withHandler:(IMP)imp;

@end

typedef enum {
	WSIHookTypeInit     = 0,
	WSIHookTypeFin      = 1,
    WSIHookTypeActive   = 2,
    WSIHookTypeInactive = 3,
    WSIHookTypeBoot     = 4,
    WSIHookTypeAll      = 9999,
} WSIHookType;

WSIDECL_PRIVATE_HEAD(WSI);

@interface WSI : WSIObject {
    WSIDECL_PRIVATE(WSI);
}

//! shared wsi.
+ (WSI*)shared;

//! Init WSI environment [static].
+ (void)Init;

//! Finalize WSI enviromnet [static].
+ (void)Fin;

//! other
+ (void)Active;
+ (void)Inactive;
+ (void)Boot;

//! register HOOK. [static].
+ (void)Register:(WSIHookType)__type hookFunc:(func_object*)__func;

//! invoke hooks
+ (void)InvokeHook:(WSIHookType)__type;

//! thread.
+ (void)ThreadUse;
+ (void)ThreadFree;

@end

WSI_EXTERN NSString* WSIGetMajorAuthor();
WSI_EXTERN NSString* WSIGetBaseURL();
WSI_EXTERN NSString* WSIGetProjectURL();
WSI_EXTERN NSString* WSIGetFeedbackEmail();

# else

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX

WSICLASS(WSI);

class WSI
: public cxx::Object<>
{
public:
    
    //! environment pack.
	WSI_STATIC void Init();
	WSI_STATIC void Fini();
    
    //! state.
    WSI_STATIC bool IsRunning;
    
};

inline_impl void Init()
{
    WSI::Init();
}

inline_impl void Fini()
{
    WSI::Fini();
}

WSI_END_HEADER_CXX

# endif
# endif

inline_impl real rand01()
{
    return (real)rand() / RAND_MAX;
}

# ifndef YES
#   define YES true
# endif

# ifndef NO
#   define NO false
# endif

# ifndef nil
#   define nil NULL
# endif

# ifndef MIN
#   define MIN(a, b) (((a) < (b)) ? (a) : (b)) 
# endif

# ifndef MAX
#   define MAX(a, b) (((a) > (b)) ? (a) : (b)) 
# endif

# if !WSI_USE_OPENCV
# undef WSI_USE_OPENCV
# endif

# endif
