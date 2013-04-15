
# ifndef __NNT_CORE_C4207797EACE47B4A2CC42B5539FBAD7_H_INCLUDED
# define __NNT_CORE_C4207797EACE47B4A2CC42B5539FBAD7_H_INCLUDED

# ifdef __cplusplus
#	define NNT_CXX
#   define NNT_C_CXX
#   define NNT_C_COMPATIABLE
#   define CXX_EXPRESS(exp) exp
#   define C_EXPRESS(exp)

#   if (__cplusplus < 201103L)
#      define NNT_CXX_99 1
#   else
#      define NNT_CXX_11 1
#   endif

# if defined(_MSC_EXTENSIONS) && defined(NNT_CXX_99)
#   if _MSC_EXTENSIONS == 1
#     undef NNT_CXX_99
#     define NNT_CXX_11 1
#   endif
# endif

# else
#   define NNT_C
#   define NNT_C_COMPATIABLE
#   define CXX_EXPRESS(exp)
#   define C_EXPRESS(exp) exp
# endif

# ifdef __llvm__
#   define NNT_CC_LLVM 1
#   define NNT_LLVM NNT_CC_LLVM
# endif

# ifdef __clang__
#   define NNT_CC_CLANG 1
#   define NNT_CLANG NNT_CC_CLANG
# endif

# ifdef __GNUC__
#   define NNT_CC_GCC 1
#   define NNT_GCC NNT_CC_GCC
# endif

# ifdef __APPLE__
#   define NNT_MACH 1
#   include <TargetConditionals.h>
# endif

# if defined(__amd64) || defined(_M_X64)
#   define NNT_X64 1
# endif

# if defined(__i386) || defined(_M_IX86)
#   define NNT_X32 1
# endif

# if (defined(__LP64__) && __LP64__) || defined(_M_IA64)
#   define NNT_X64 1
# endif

# ifdef __arm
#   define NNT_ARM 1
# ifndef NNT_X32
#   define NNT_X32 1
# endif
# endif

# if defined(LIBNNT) || defined(DLLNNT)
#   define NNT_LIBRARY 1
# endif

# if defined(_MSC_VER) && defined(WIN32)
#   ifdef _MFC_VER
#     define NNT_MFC 1 
#   endif
// is windows.
#   define NNT_MSVC 1
#   define NNT_WINDOWS 1
#   if defined(_USRDLL) && !defined(NNT_LIBRARY)
#     define NNT_LIBRARY 1
#   endif
#   if defined(NNT_LIBRARY)
#     include "stdafx.h"
#   endif
#   include <Windows.h>
//#   include <WinNT.h>
#   include <tchar.h>
#   include <cwchar>
#   ifdef NNT_MFC
#     include <afx.h>
#     include <afxwin.h>
#   endif
# else
// is unix like.
#   define NNT_UNIX 1
# endif

# ifdef NNT_CXX
#   ifdef NNT_CXX_99

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
#   define NNT_UNICODE 1
# endif

# define NNT_VERBOSE 1
# define NNT_VERBOSE_VERBOSE 0

# if defined(__OBJC__) || defined(__OBJC2__)
#	define NNT_OBJC
#   if __has_feature(objc_arc)
#     define NNT_OBJC_ARC 1
#   endif
# endif

# if defined(NNT_CXX) && !defined(NNT_OBJC)
#   define NNT_PURE_CXX 1
# endif

# if !defined(NNT_CXX) && defined(NNT_OBJC)
#   define NNT_PURE_OBJC 1
# endif

# if defined(NNT_CXX) && defined(NNT_OBJC)
#   define NNT_CXX_OBJC 1
# endif

# if defined(NNT_C) && !defined(NNT_OBJC) && !defined(NNT_CXX)
#   define NNT_PURE_C 1
# endif

# if defined(NNT_C) && defined(NNT_OBJC)
#   define NNT_C_OBJC 1
# endif

# ifdef TARGET_OS_IPHONE

#   define NNT_IOS_MIN __IPHONE_OS_VERSION_MIN_REQUIRED
#   define NNT_IOS_MAX __IPHONE_OS_VERSION_MAX_ALLOWED

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
#   elif NNT_IOS_MIN >= __IPHONE_6_0
typedef ios_6 ios_version;
#   elif NNT_IOS_MIN >= __IPHONE_5_0
typedef ios_5 ios_version;
#   elif NNT_IOS_MIN >= __IPHONE_4_0
typedef ios_4 ios_version;
#   elif NNT_IOS_MIN >= __IPHONE_3_0
typedef ios_3 ios_version;
#   elif NNT_IOS_MIN >= __IPHONE_2_0
typedef ios_2 ios_version;
#   else
typedef ios_unknown ios_version;
# endif

# endif

# ifdef NNT_LIBRARY
#   define APPNNT 1
#   if defined(LIBNNT)
#     define NNT_LIBRARY_STAIC 1
#   else
#     define NNT_LIBRARY_SHARED 1
#   endif
# endif

# ifdef KERNELNNT
#   define NNT_KERNEL_SPACE 1
# else
#   define NNT_USER_SPACE 1
# endif

# ifdef NNT_KERNEL_SPACE
#   define NNTKS_EXPRESS(exp) exp
#   define NNTUS_EXPRESS(exp) exp
# else
#   define NNTKS_EXPRESS(exp)
#   define NNTUS_EXPRESS(exp) exp
# endif

# define NNT_INLINE inline
# define NNT_STATIC static
# define NNT_STATIC_IMPL
# define NNT_STATIC_CONST static const
# define NNT_STATIC_CONST_IMPL
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

# ifdef NNT_X64
typedef arch_x64 arch_type;
# endif

# ifdef NNT_X32
typedef arch_x32 arch_type;
# endif

# ifdef NNT_WINDOWS
typedef os_windows os_type;
# elif defined(NNT_MACH)
typedef os_mach os_type;
# elif defined(NNT_UNIX)
typedef os_unix os_type;
# endif

# ifdef NNT_OBJC
typedef lang_objc lang_type;
# elif defined(NNT_CXX)
typedef lang_cxx lang_type;
# elif defined(NNT_C)
typedef lang_c lang_type;
# endif

# ifdef NNT_GCC
typedef compr_gcc compr_type;
# elif defined(NNT_MSVC)
typedef compr_msvc compr_type;
# elif defined(NNT_CLANG)
typedef compr_clang compr_type;
# endif

NNT_STATIC_CONST arch_type arch_object();
NNT_STATIC_CONST os_type os_object();
NNT_STATIC_CONST lang_type lang_object();
NNT_STATIC_CONST compr_type compr_object();

# define NNTASM_BEGIN __asm {
# define NNTASM_END }
# define NNTASM(exp) \
NNTASM_BEGIN\
exp \
NNTASM_END

# define NNT_BEGIN_CXX namespace nnt {
# define NNT_END_CXX   }

# ifdef NNT_CXX
#   define NNT_USINGCXXNAMESPACE using namespace ::nnt;
#	define NNT_BEGIN             NNT_BEGIN_CXX
#	define NNT_END               NNT_END_CXX
#	define NNT_BEGIN_HEADER_C    extern "C" {
#	define NNT_END_HEADER_C      }
#   define NNT_BEGIN_HEADER_CXX  NNT_BEGIN_CXX
#   define NNT_END_HEADER_CXX    NNT_END_CXX
#   define NNT_BEGIN_HEADER_CXX_EXPLICIT NNT_BEGIN_HEADER_CXX namespace cxx {
#   define NNT_END_HEADER_CXX_EXPLICIT NNT_END_HEADER_CXX }
#	define NNT_BEGIN_HEADER      NNT_BEGIN_HEADER_CXX
#	define NNT_END_HEADER        NNT_END_HEADER_CXX
#   define NNT_BEGIN_HEADER_HPP  NNT_BEGIN_HEADER_CXX { namespace tpl {
#   define NNT_END_HEADER_HPP    NNT_END_HEADER_HPP   }}
#   define NNT_BEGIN_OBJC        
#   define NNT_END_OBJC          
#   define NNT_BEGIN_C           extern "C" {
#   define NNT_END_C             }
#   define NNT_NEED_CXX
# else
#   define NNT_USINGCXXNAMESPACE
#	define NNT_BEGIN
#	define NNT_END
#	define NNT_BEGIN_HEADER_C
#	define NNT_END_HEADER_C
#	define NNT_BEGIN_HEADER      NNT_BEGIN_HEADER_C
#	define NNT_END_HEADER        NNT_END_HEADER_C
#   define NNT_BEGIN_OBJC
#   define NNT_END_OBJC
#   define NNT_BEGIN_C
#   define NNT_END_C
#   define NNT_NEED_CXX          error, must be built as c++ source file.
# endif

# ifdef NNT_CXX
#   define CXXEXPRESS(exp) exp
# else
#   define CXXEXPRESS(exp)
# endif

# ifdef NNT_OBJC
#   define OBJCEXPRESS(exp) exp
# else
#   define OBJCEXPRESS(exp)
# endif

# if defined(__BLOCKS__)
#   define NNT_BLOCKS
# endif

# if defined(DEBUG) || defined(_DEBUG)
#   define NNT_DEBUG
# else
#   ifndef NNT_DEBUG
#     define NNT_RELEASE
#   endif
# endif

# ifdef NNT_DEBUG
#	define NNTDEBUG_EXPRESS(express)    express
#	define NNTRELEASE_EXPRESS(express)
# endif

# ifdef NNT_RELEASE
#	define NNTDEBUG_EXPRESS(express)
#	define NNTRELEASE_EXPRESS(express)  express
# endif

# define SPACE
# define TODO(express) {SPACE}
# define PASS {SPACE}

# define NNTMACRO_SELF(val)                    val
# define _NNTMACRO_TOSTR(val)                  #val
# define NNTMACRO_TOSTR(val)                  _NNTMACRO_TOSTR(val)
# define NNTMACRO_COMBINE_2(v0, v1, sep)       NNTMACRO_SELF(v0)##sep##NNTMACRO_SELF(v1)
# define NNTAUTO_NAME                        __nnt_autoname_ ## __LINE__ ## __FUNCTION__

# ifdef NNT_OBJC

# define _NNTMACRO_TOSTR_OBJC(val)             @#val
# define NNTMACRO_TOSTR_OBJC(val)             _NNTMACRO_TOSTR_OBJC(val)

# define _NNTMACRO_TOSTR_OBJC2(val)            @val
# define NNTMACRO_TOSTR_OBJC2(val)            _NNTMACRO_TOSTR_OBJC2(val)

# endif

# ifdef NNT_MSVC
#   define NNT_NOVTABLE __declspec(novtable)
#   define typename_
# else
#   define NNT_NOVTABLE
#   define typename_ typename 
# endif

# define interface_ struct
# define abstrace_

# ifdef NNT_C
#   define _not_  !
#   define _xor_  ^
#   define _and_  &
#   define _or_   |
# endif

# ifdef NNT_OBJC

# import <Foundation/Foundation.h>

# if TARGET_OS_IPHONE
# import <UIKit/UIKit.h>
# endif

# define is_no == NO
# define is_yes == YES

# ifdef NNT_CXX

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

# define segment_accel segment_accel_type __nnt_accel_segment;

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

#ifdef NNT_X64
   typedef double real;
#  define REAL_IS_DOUBLE  1
   typedef ulonglong uindex, usize, uinteger;
   typedef long sindex, ssize, sinteger, integer;
#else
   typedef float real;
#  define REAL_IS_FLOAT   1
   typedef uint uindex, usize, uinteger;
   typedef int sindex, ssize, sinteger, integer;
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

# ifdef NNT_CXX

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

# ifdef NNT_CXX

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

# ifdef NNT_CXX

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

# ifdef NNT_OBJC

# define NNTDECL_PRIVATE_HEAD(cls) @class cls; @class cls##Private
# define NNTDECL_PRIVATE(cls) @private cls##Private *d_ptr;
# define NNTDECL_PRIVATE_INIT(cls) { if (d_ptr == nil) {d_ptr = [cls##Private alloc]; d_ptr.d_owner = self; [d_ptr init]; }}
# define NNTDECL_PRIVATE_DEALLOC() [d_ptr release];
# define NNTDECL_PRIVATE_EX(cls, name) @private cls##Private *name;
# define NNTDECL_PRIVATE_INIT_EX(cls, name) { if (name == nil) { name = [cls##Private alloc]; name.d_owner = self; [name init]; }}
# define NNTDECL_PRIVATE_DEALLOC_EX(name) [name release];
# define NNTDECL_D(cls) NNTDECL_PRIVATE_INIT(cls);
# define NNTDECL_PRIVATE_BEGIN(cls, base) @interface cls##Private : base
# define NNTDECL_PRIVATE_IMPL(cls) \
@property (nonatomic, assign) cls* d_owner; \
@end \
@implementation cls##Private \
@synthesize d_owner;
# define NNTDECL_PRIVATE_END @end

# endif

# ifdef NNT_CXX

# define NNTDECL_PRIVATE_NAME(cls)\
cls##Private

# define NNTDECL_PRIVATE_HEAD_CXX(cls) \
class cls; class cls##Private;

# define NNTDECL_PRIVATE_CXX(cls) \
friend class cls##Private; \
typedef cls##Private private_type; \
private_type* d_ptr;

# define NNTDECL_PRIVATE_CONSTRUCT(cls) \
d_ptr = new private_type(this);

# define NNTDECL_PRIVATE_DESTROY() \
delete d_ptr;

# define NNTDECL_PRIVATE_BEGIN_CXX(cls) \
class cls##Private : public ::nnt::cxx::Object<> { \
typedef cls##Private self_type, private_type, _class; \
typedef cls owner_type; \
owner_type* d_owner; \
friend class cls; \
cls##Private(cls* obj) : d_owner(obj) { init(); } \
~cls##Private() { dealloc(); }

# define NNTDECL_PRIVATE_END_CXX };

# define NNT_PRIVATE() \
if (d_ptr == NULL) \
d_ptr = new private_type(this);

# define NNTDECL_NOCOPY(cls) \
private: cls(cls const&); cls& operator = (cls const&);

# define NNTDECL_NOCOPY_EX(cls, impl) \
private: cls(impl const&); impl& operator = (impl const&);

# define NNTDECL_NONEW(cls) \
private: static void* operator new (size_t); static void* operator new[] (size_t);

# ifndef NNTDECL_PRIVATE_BEGIN
#   define NNTDECL_PRIVATE_BEGIN NNTDECL_PRIVATE_BEGIN_CXX
# endif

# ifndef NNTDECL_PRIVATE_END
#   define NNTDECL_PRIVATE_END NNTDECL_PRIVATE_END_CXX
# endif

# ifndef NNTDECL_PRIVATE
#   define NNTDECL_PRIVATE NNTDECL_PRIVATE_CXX
# endif

# ifndef NNTDECL_PRIVATE_HEAD
#   define NNTDECL_PRIVATE_HEAD NNTDECL_PRIVATE_HEAD_CXX
# endif

# endif

# ifdef NNT_LIBRARY_SHARED
#   ifdef NNT_MSVC
#     define NNT_EXPORT __declspec(dllexport)
#     define NNT_IMPORT __declspec(dllimport)
#   endif
# endif

# ifndef NNT_EXPORT
#   define NNT_EXPORT  
# endif

# ifndef NNT_IMPORT
#   define NNT_IMPORT
# endif

# if !defined (NNT_CONSTRUCTOR)
#   define NNT_CONSTRUCTOR __attribute__((constructor))
# endif

# if !defined (NNT_DESTRUCTOR)
#   define NNT_DESTRUCTOR __attribute__((destructor))
# endif

# if !defined (NNT_EXTERN)
#   if defined NNT_CXX
#      define NNT_EXTERN_C extern "C"
#   else
#      define NNT_EXTERN_C extern
#   endif
#   define NNT_EXTERN extern
# endif

# if defined(NNT_LIBRARY)
#   define NNTAPI(retype) NNT_EXPORT retype
#   define NNTCLASS(cls)  class NNT_EXPORT cls
#   define NNTNTERFACE(itr) interface_ NNT_EXPORT itr
#   define NNTVAR(retype) NNT_EXTERN NNT_EXPORT retype
# else
#   define NNTAPI(retype) NNT_IMPORT retype
#   define NNTCLASS(cls)  class NNT_IMPORT cls
#   define NNTNTERFACE(itr) interface_ NNT_IMPORT itr
#   define NNTVAR(retype) NNT_EXTERN NNT_IMPORT retype
# endif

# define NNTVAR_USE(retype) NNT_EXTERN NNT_IMPORT retype

# ifdef NNT_WINDOWS
#   ifdef NNT_X32
#     define NNTAPI_ASM(method) method##_
#   else
#     define NNTAPI_ASM(method) _##method##_
#   endif
# else
#   define NNTAPI_ASM(method) _##method
# endif

# if defined(NNT_LIBRARY)
#   define NNTAPPCLASS(cls) class NNT_EXPORT cls
# else
#   define NNTAPPCLASS(cls) class NNT_IMPORT cls
# endif

// kernel

# ifdef NNT_MACH

# if defined(TARGET_IPHONE_SIMULATOR) && TARGET_IPHONE_SIMULATOR
#    define NNTSIM_EXPRESS(exp) exp
#    define NNT_SIMULATOR
# else
#    define NNTSIM_EXPRESS(exp) SPACE
#    define NNT_DEVICE
# endif

# if (defined(TARGET_IPHONE_SIMULATOR) && TARGET_IPHONE_SIMULATOR) || (defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE)
#    define NNTOS_EXPRESS(exp) exp
# else
#    define NNTOS_EXPRESS(exp) SPACE
# endif

# if TARGET_OS_IPHONE
#    define NNT_TARGET_IOS 1
#    define IOSEXPRESS(exp) exp
#    define MACEXPRESS(exp) SPACE
#    define MAC_IOS_SELECT(mac, ios) ios
#    define NNT_ISPAD (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
#    define NNT_ISPHONE !NNT_ISPAD
# elif TARGET_OS_MAC
#    define NNT_TARGET_MAC 1
#    define IOSEXPRESS(exp) SPACE
#    define MACEXPRESS(exp) exp
#    define MAC_IOS_SELECT(mac, ios) mac
# endif

# endif

# ifndef NNT_TARGET_OS
#   define NNT_CROSS_PLATFORM 1
# endif

# define NNT_BEGIN_NS(ns)        namespace ns {
# define NNT_END_NS              }

# ifdef NNT_CXX
#   define NNT_BEGIN_HEADER_OBJC   NNT_BEGIN_HEADER_C
#   define NNT_END_HEADER_OBJC     NNT_END_HEADER_C
# else
#   define NNT_BEGIN_HEADER_OBJC
#   define NNT_END_HEADER_OBJC
# endif

# ifdef NNT_GCC

#   define NNT_ATOMIC_ADD(x, v) __sync_fetch_and_add(&x, v)
#   define NNT_ATOMIC_SUB(x, v) __sync_fetch_and_sub(&x, v)

#   define NNT_ADD_ATOMIC(x, v) __sync_add_and_fetch(&x, v)
#   define NNT_SUB_ATOMIC(x, v) __sync_sub_and_fetch(&x, v)

# elif defined(NNT_MSVC)

#   define NNT_ATOMIC_ADD(x, v) InterlockedAdd(&x, v)
#   define NNT_ATOMIC_SUB(x, v) InterlockedAdd(&x, -v)

#   define NNT_ADD_ATOMIC(x, v) InterlockedExchange(&x, v)
#   define NNT_SUB_ATOMIC(x, v) InterlockedExchange(&x, -v)

# endif

#   define NNT_ATOMIC_INC(x) NNT_ADD_ATOMIC(x, 1)
#   define NNT_ATOMIC_DEC(x) NNT_SUB_ATOMIC(x, 1)

# ifdef NNT_OBJC
#   define NNTDECL_EXTERN_CLASS_OBJC(cls)      @class cls;
#   define NNTDECL_EXTERN_INTERFACE_OBJC(cls)  @protocol cls;
#   define NNTDECL_EXTERN_DELEGATE_OBJC(cls)   @protocol cls##Delegate;
# endif

# ifdef NNT_CXX
#   define NNTDECL_EXTERN_CLASS_CXX(cls)      class cls;
#   define NNTDECL_EXTERN_INTERFACE_CXX(cls)  struct cls;
#   define NNTDECL_EXTERN_DELEGATE_CXX(cls)   class cls##Delegate;
#   define NNTDECL_EXTERN_CLASS_NS(ns, cls)   namespace ns { class cls; }
#   define NNTDECL_EXTERN_CLASS_NS2(ns1, ns2, cls) namespace ns1 { namespace ns2 { class cls; }}
#   define NNTDECL_EXTERN_CLASS_NS3(ns1, ns2, ns3, cls) namespace ns1 { namespace ns2 { namespace ns3 { class cls; }}}
#   define NNTDECL_EXTERN_CLASS_NS4(ns1, ns2, ns3, ns4, cls) namespace ns1 { namespace ns2 { namespace ns3 { namespace ns4 { class cls; }}}}
#   define NNTDECL_INTERFACE(cls) public: virtual ~cls() {}
# endif

# ifdef NNT_OBJC
#   define NNTDECL_EXTERN_CLASS               NNTDECL_EXTERN_CLASS_OBJC
#   define NNTDECL_EXTERN_INTERFACE           NNTDECL_EXTERN_INTERFACE_OBJC
#   define NNTDECL_EXTERN_DELEGATE            NNTDECL_EXTERN_DELEGATE_OBJC
# else
#   define NNTDECL_EXTERN_CLASS               NNTDECL_EXTERN_CLASS_CXX
#   define NNTDECL_EXTERN_INTERFACE           NNTDECL_EXTERN_INTERFACE_CXX
#   define NNTDECL_EXTERN_DELEGATE            NNTDECL_EXTERN_DELEGATE_CXX
# endif

# define NNTDECL_EXTERN_PROTOCOL NNTDECL_EXTERN_INTERFACE

# define MIN_NOT(l, r, n) (((l) == (n)) ? (r) : MIN((l), (r)))
# define MAX_NOT(l, r, n) (((l) == (n)) ? (r) : MAX((l), (r)))
# define TRIEXP(sel, tru, fla) ((sel) ? (tru) : (fla))

# define MASK_CHECK(mask, val) (((mask) & (val)) == (mask))
# define MASK_SET(mask, val) \
{ if (MASK_CHECK(mask, val) == false) val |= mask; }
# define MASK_UNSET(mask, val) \
{ if (MASK_CHECK(mask, val)) val ^= mask; }

# ifdef NNT_DEBUG
#	define NNTDEBUG_BREAK NNTDEBUG_EXPRESS(__asm__ int 3)
#	define NNTDEBUG_BREAK_IF(express) NNTDEBUG_EXPRESS(if (express) NNTDEBUG_BREAK)
#	define NNTDEBUG_ASSERT(express) NNTDEBUG_EXPRESS_IF(!(express))
# else
#	define NNTDEBUG_BREAK SPACE
#	define NNTDEBUG_BREAK_IF(express) SPACE
#	define NNTDEBUG_ASSERT(express) SPACE
# endif

# define NNTDECL_CATEGORY(name, cate) \
    @interface NNT_FIX_CATEGORY_LINKBUG_##name##_##cate : name @end

# define NNTIMPL_CATEGORY(name, cate) \
    @implementation NNT_FIX_CATEGORY_LINKBUG_##name##_##cate @end

# define NNTUSE_CATEGORY(name, cate) \
    extern name* __NNT_FIX_CATEGORY_LINKBUG_##name##_##cate (void); \
    name* __NNT_FIX_CATEGORY_LINKBUG_##name##_##cate (void) { NNT_FIX_CATEGORY_LINKBUG_##name##_##cate *ret = [NNT_FIX_CATEGORY_LINKBUG_##name##_##cate new]; return ret; }

# define NNTCALL_CATEGORY(name, cate) \
    __NNT_FIX_CATEGORY_LINKBUG_##name##_##cate()

# ifdef NNT_OBJC
# define _W(str) NSLocalizedString(str, SPACE)
# else
# define _W(str) L##str
# endif

# ifdef LIBNNT
#   define NNTLIB_EXPRESS(exp) exp
#   define NNTBIN_EXPRESS(exp) SPACE
# else
#   define NNTLIB_EXPRESS(exp) SPACE
#   define NNTBIN_EXPRESS(exp) exp
# endif

# ifdef NNT_OBJC
NNT_BEGIN_HEADER_C
extern void _trace_obj         (NSString*, id);
extern void _trace_int         (NSString*, int);
extern void _trace_float       (NSString*, float);
extern void _trace_msg         (NSString*);
NNT_END_HEADER_C

/*
# ifdef NNT_CXX
template <typename StrT>
inline void _trace_msg(StrT const& str) { _trace_msg([NSString stringWithUTF8String:str.c_str()]); }
inline void _trace_msg(char const* str) { _trace_msg([NSString stringWithUTF8String:str]); }
# endif
 */

# endif

# ifdef NNT_DEBUG
#   ifdef NNT_OBJC
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

#     ifdef NNT_CXX

#       ifdef NNT_MSVC

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

# ifdef NNT_OBJC
#   define dthrow_msg(title, msg) dthrow([NSException exceptionWithName:title reason:msg userInfo:nil]);
# elif defined(NNT_CXX)
#   define dthrow_msg(title, msg) dthrow(::nnt::exception::message(msg, title))
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

# if defined(NNT_C) && !defined(NNT_OBJC)
typedef int bool;
# ifndef true
#   define true  1
# endif
# ifndef false
#   define false 0
# endif
# endif

# ifdef NNT_OBJC
#   define OBJCMutable 1
#   define OBJCNormal  0
# endif

//! @macro self_release auto release once after alloc
# ifdef NNT_OBJC
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

NNT_BEGIN_HEADER_C

NNTAPI(void) sleep_second(ulonglong);
NNTAPI(void) sleep_millisecond(ulonglong);
NNTAPI(void) sleep_microsecond(ulonglong);
NNTAPI(void) sleep_nanosecond(ulonglong);
NNTAPI(ulong) timestamp();

NNT_END_HEADER_C

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

typedef enum _NNTValueType {
    NNTValueTypeUnknown,
    NNTValueTypeInt,
    NNTValueTypeUInt,
    NNTValueTypeShort,
    NNTValueTypeUShort,
    NNTValueTypeChar,
    NNTValueTypeUChar,
    NNTValueTypeLong,
    NNTValueTypeULong,
    NNTValueTypeLongLong,
    NNTValueTypeULongLong,
    NNTValueTypeString,
    NNTValueTypeFloat,
    NNTValueTypeDouble,
} NNTValueType;

typedef struct {
    uint major;
    uint minor;
    uint patch;
    char const* ver;
} version_t;

//! 0: equal, 1: greater, -1: lesser
extern int VersionCmp(version_t const* l, version_t const* r);

# ifdef NNT_CXX

# define NNT_OPERATOR_IMPL(type) \
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

NNT_OPERATOR_IMPL(version_t);

# endif

# ifdef NNT_LIBONLY
#   undef NNT_LIBONLY
# endif
//# define NNT_LIBONLY                1

// nnt preprocess define.
# define NNT_VERSION_MAJOR			1
# define NNT_VERSION_MIN			0
# define NNT_VERSION_FIX			0
# define NNT_CODENAME               strawberry

// configuration.
# define NNT_VERSION_STR            NNTMACRO_TOSTR(NNT_VERSION_MAJOR) "_" NNTMACRO_TOSTR(NNT_VERSION_MIN) "_" NNTMACRO_TOSTR(NNT_VERSION_FIX)
# define NNT_VERSION_VALUE          ((NNT_VERSION_MAJOR << 16 & 0xff0000) | (NNT_VERSION_MIN << 8 & 0xff00) | (NNT_VERSION_FIX & 0xff))
# define NNT_CODENAME_STR           NNTMACRO_TOSTR(NNT_CODENAME)

NNT_STATIC_CONST version_t NNTVERSION = {NNT_VERSION_MAJOR, NNT_VERSION_MIN, NNT_VERSION_FIX, NNT_VERSION_STR};

NNT_BEGIN_HEADER_C

//! get version string.
NNTAPI(char const*) NNTVersion();

NNT_END_HEADER_C

# define NNT_SETTING_BUNDLE			@"Settings.bundle"
# define NNT_SETTING_FILE			@"Root.plist"
# define NNT_USE_SBJSON				1
# define NNT_USE_TBXML              1
# define NNT_USE_BASE64             1
# define NNT_USE_COREPLOT           1
# define NNT_USE_BDB                1
# define NNT_USE_OPENCV             1
# define NNT_DEBUGBAR_HEIGHT        20

// team infomation.
# define NNT_BASE_URL				wybosys.com
# define NNT_BASE_DOMAIN            com.wybosys.nnt
# define NNT_PROJECT_URL            sf.net/p/nnt
# define NNT_PROJECT_DOMAIN         NNT_BASE_DOMAIN
# define NNT_MAJOR_AUTHOR           wybosys <wybosys@gmail.com>
# define NNT_FEEDBACK_EMAIL         wybosys@gmail.com

//! build for iOS version. <=
# define NNT_iOS                    0x4FF

//! the framework is build for AppStore.
# define NNT_APPSTORE               1

//! the framework is build for test jailbreak device or private device.
# define NNT_JAILBREAK              0

# if NNT_APPSTORE == 0
#   undef NNT_APPSTORE
# endif

# if NNT_JAILBREAK == 0
#   undef NNT_JAILBREAK
# endif

# ifdef NNT_APPSTORE
#   ifdef NNT_JAILBREAK
#     ifndef NNT_DEBUG
#       undef NNT_JAILBREAK
#     else
#       define NNT_JAILBREAK_DEBUG
#     endif
#   endif
# endif

# if !NNT_VERBOSE
#   undef NNT_VERBOSE
# endif

# if !NNT_VERBOSE_VERBOSE
#   undef NNT_VERBOSE_VERBOSE
# endif

# ifdef NNT_DEBUG
# else
#   ifdef NNT_VERBOSE
#     undef NNT_VERBOSE
#   endif
#   ifdef NNT_VERBOSE_VERBOSE
#     undef NNT_VERBOSE_VERBOSE
#   endif
# endif

# ifdef NNT_TARGET_IOS

# if NNT_iOS < 0x300
#   define NNT_iOS_1
#   define NNT_iOS_2
#   define NNT_iOS2
#   undef __IPHONE_OS_VERSION_MAX_ALLOWED
#   define __IPHONE_OS_VERSION_MAX_ALLOWED __IPHONE_2_2
# endif

# if NNT_iOS < 0x400 && NNT_iOS >= 0x300
#   define NNT_iOS_1
#   define NNT_iOS_2
#   define NNT_iOS_3
#   define NNT_iOS3
#   undef __IPHONE_OS_VERSION_MAX_ALLOWED
#   define __IPHONE_OS_VERSION_MAX_ALLOWED __IPHONE_3_2
# endif

# if NNT_iOS < 0x500 && NNT_iOS >= 0x400
#   define NNT_iOS_1
#   define NNT_iOS_2
#   define NNT_iOS_3
#   define NNT_iOS_4
#   define NNT_iOS4
#   undef __IPHONE_OS_VERSION_MAX_ALLOWED
#   define __IPHONE_OS_VERSION_MAX_ALLOWED __IPHONE_4_3
# endif

# if NNT_iOS < 0x600 && NNT_iOS >= 0x500
#   define NNT_iOS_1
#   define NNT_iOS_2
#   define NNT_iOS_3
#   define NNT_iOS_4
#   define NNT_iOS_5
#   define NNT_iOS5
#   undef __IPHONE_OS_VERSION_MAX_ALLOWED
#   define __IPHONE_OS_VERSION_MAX_ALLOWED __IPHONE_5_0
# endif

# if NNT_iOS < 0x700 && NNT_iOS >= 0x600
#   define NNT_iOS_1
#   define NNT_iOS_2
#   define NNT_iOS_3
#   define NNT_iOS_4
#   define NNT_iOS_5
#   define NNT_iOS_6
#   define NNT_iOS6
#   undef __IPHONE_OS_VERSION_MAX_ALLOWED
#   define __IPHONE_OS_VERSION_MAX_ALLOWED __IPHONE_NA
# endif

# endif

// global include

# ifdef NNT_MSVC
#   pragma warning (disable: 4996)
#   pragma warning (disable: 4068)
#   pragma warning (disable: 4273)
#   pragma warning (disable: 4251)
#   pragma warning (disable: 4275) // disable dll-interface warning.
#   pragma warning (disable: 4819)
# endif

# ifdef NNT_CLANG
#   pragma GCC diagnostic ignored "-Wbind-to-temporary-copy"
#   ifdef NNT_DEBUG
#     pragma GCC diagnostic ignored "-Wshorten-64-to-32"
#   endif
# endif

# ifdef NNT_UNIX
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

# ifdef NNT_CXX

# include <iostream>
# include <iomanip>
# include <string>
# include <algorithm>

NNT_BEGIN_HEADER_CXX

//using namespace std;

struct _ignore_null;
typedef _ignore_null *ignore_null;

namespace cxx {}

# ifdef NNT_PURE_CXX
using namespace cxx;
# endif

NNT_END_HEADER_CXX

# endif

// include all base class.
# include "./Object.h"

// pre include objc's object for may inherited by C++ object.
# ifdef NNT_OBJC

#   ifdef NNT_TARGET_MAC
#     import <Cocoa/Cocoa.h>
#   endif

#   define NSInfinite NSNotFound
#   define discard assign
typedef struct {} objc_type;

#   import <Foundation/Foundation.h>
#   import "./NSObject+NNT.h"
#   import "./NSLock+NNT.h"

# endif

# ifndef autocollect
#   define autocollect
# endif

// include C++ Base Classes.
# include "../TL/Exception+NNT.h"
# include "../TL/Types+NNT.h"
# include "../TL/Operator+NNT.h"
# include "../TL/Function+NNT.h"
# include "../TL/String+NNT.h"
# include "../TL/Vector+NNT.h"
# include "../TL/List+NNT.h"
# include "../TL/Map+NNT.h"
//# include "../TL/Bimap+NNT.h"
# include "../TL/Tuple+NNT.h"
# include "../TL/Data+NNT.h"
# include "../TL/Algorithm+NNT.h"
# include "../TL/Regex+NNT.h"
# include "../TL/SmartPtr+NNT.h"
# include "../TL/Closure+NNT.h"
# include "../TL/Variant+NNT.h"

// ignore assert.
# include <assert.h>
# ifdef assert
#   define NNT_ASSERT assert
#   undef assert
# endif

// include unit test.
# include "UnitTest.h"

# ifdef NNT_OBJC

// include Objective-C Base Classes.
#   import "NSString+NNT.h"
#   import "NSNumber+NNT.h"
#   import "NSArray+NNT.h"
#   import "NSDictionary+NNT.h"
#   import "NSData+NNT.h"
#   import "NSSet+NNT.h"
#   import "NSIndex+NNT.h"
#   import "NSURL+NNT.h"
#   import "NSURLConnection+NNT.h"
#   import "NSDate+NNT.h"
#   import "NSLocale+NNT.h"
#   import "NSRunLoop+NNT.h"
#   import "Time+NNT.h"
#   import "Msgbox.h"
#   import "Console+NNT.h"

# endif

// hook
# ifdef NNT_OBJC

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
	NNTHookTypeInit     = 0,
	NNTHookTypeFin      = 1,
    NNTHookTypeActive   = 2,
    NNTHookTypeInactive = 3,
    NNTHookTypeBoot     = 4,
    NNTHookTypeAll      = 9999,
} NNTHookType;

NNTDECL_PRIVATE_HEAD(NNT);

@interface NNT : NNTObject {
    NNTDECL_PRIVATE(NNT);
}

//! shared nnt.
+ (NNT*)shared;

//! Init NNT environment [static].
+ (void)Init;

//! Finalize NNT enviromnet [static].
+ (void)Fin;

//! other
+ (void)Active;
+ (void)Inactive;
+ (void)Boot;

//! register HOOK. [static].
+ (void)Register:(NNTHookType)__type hookFunc:(func_object*)__func;

//! invoke hooks
+ (void)InvokeHook:(NNTHookType)__type;

//! thread.
+ (void)ThreadUse;
+ (void)ThreadFree;

@end

NNT_EXTERN NSString* NNTGetMajorAuthor();
NNT_EXTERN NSString* NNTGetBaseURL();
NNT_EXTERN NSString* NNTGetProjectURL();
NNT_EXTERN NSString* NNTGetFeedbackEmail();

# else

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX

NNTCLASS(NNT);

class NNT
: public cxx::Object<>
{
public:
    
    //! environment pack.
	NNT_STATIC void Init();
	NNT_STATIC void Fini();
    
    //! state.
    NNT_STATIC bool IsRunning;
    
};

inline_impl void Init()
{
    NNT::Init();
}

inline_impl void Fini()
{
    NNT::Fini();
}

NNT_END_HEADER_CXX

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

# if !NNT_USE_OPENCV
# undef NNT_USE_OPENCV
# endif

# endif
