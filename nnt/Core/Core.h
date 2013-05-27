
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

#   if defined(_MSC_EXTENSIONS) && defined(NNT_CXX_99)
#     if _MSC_EXTENSIONS == 1
#       define NNT_CXX_EXP_11 1
#     endif
#   endif

#   ifdef __STDC_ISO_10646__
#     define NNT_CXX_EXP_11 1
#   endif

#   ifdef NNT_CXX_EXP_11
#     ifdef NNT_CXX_99
#       undef NNT_CXX_99
#       define NNT_CXX_11 1
#     endif
#   endif

# elif defined(__OPENCL_C__) && __OPENCL_C__

#   define NNT_C_OPENCL 1
#   define CXX_EXPRESS(exp)
#   define C_EXPRESS(exp)

# else
    
#   define NNT_C 1
#   define NNT_C_COMPATIABLE 1
#   define CXX_EXPRESS(exp)
#   define C_EXPRESS(exp) exp

# endif // c++

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

#   include <TargetConditionals.h>

#   if defined(TARGET_OS_MAC) || defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)

#     define NNT_MACH 1

#   endif

#   ifndef __unix__
#     define __unix__ 1
#   endif

# endif

# ifdef __FreeBSD__
#   define NNT_BSD 1
# endif

# if defined(__linux__) || defined(__linux)
#   define NNT_LINUX 1
# endif

# if defined(__unix__) || defined(__unix)
#   define NNT_UNIX 1
# endif

# if (defined(__LP64__) && __LP64__) || defined(_M_IA64) || defined(__amd64) || defined(_M_X64) || (defined(_LP64) && _LP64)
#   define NNT_X64 1
# endif

# if defined(__i386) || defined(_M_IX86) || (defined(__POINTER_WIDTH__) && __POINTER_WIDTH__ == 32)
#   define NNT_X32 1
# endif

# ifdef __arm

#   define NNT_ARM 1

#   ifndef NNT_X32
#     define NNT_X32 1
#   endif

# endif

# ifdef __OPENCL__
#   define NNT_OPENCL 1
# endif

# if defined(LIBNNT) || defined(DLLNNT)
#   define NNT_LIBRARY 1
# endif

# ifdef KERNELNNT

#   define NNT_KERNEL_SPACE 1
#   define NNT_CPU_SPACE 1

# elif defined(NNT_C_OPENCL)

#   define NNT_GPU_SPACE 1

# else

#   define NNT_USER_SPACE 1
#   define NNT_CPU_SPACE 1

# endif

# ifdef NNT_KERNEL_SPACE

#   ifdef NNT_BSD
#     ifndef _KERNEL
#       define _KERNEL 1
#     endif
#   endif

#   ifdef NNT_LINUX
#     ifndef __KERNEL__
#       define __KERNEL__ 1
#     endif
#   endif

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
#   if defined(NNT_LIBRARY) && defined(NNT_USER_SPACE)
#     include "stdafx.h"
#   endif
#   ifndef WINVER
#     define WINVER 0x0500
#   endif
#   ifndef _WIN32_WINNT
#     define _WIN32_WINNT 0x0501
#   endif
#   ifndef _WIN32_WINDOWS
#     define _WIN32_WINDOWS 0x0410
#   endif
#   ifndef _WIN32_IE
#     define _WIN32_IE 0x0700
#   endif
#   ifdef NNT_USER_SPACE
#     ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN 1
#     endif
#     include <Windows.h>
#   else // kernel space
#     include <ntddk.h>
#   endif // user space
#   include <tchar.h>
#   ifdef NNT_USER_SPACE
#     include <cwchar>
#   endif
#   ifdef NNT_MFC
#     include <afx.h>
#     include <afxwin.h>
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

# if defined(DEBUG) || defined(_DEBUG) || defined(DBG)
#   define NNT_DEBUG 1
# else
#   ifndef NNT_DEBUG
#     define NNT_RELEASE 1
#   endif
# endif

# ifdef NNT_MACH

#   if TARGET_IPHONE_SIMULATOR
#     define NNT_SIMULATOR 1
#   else
#     define NNT_DEVICE 1
#   endif

#   if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#     define NNT_TARGET_IOS 1
#   elif TARGET_OS_MAC
#     define NNT_TARGET_MAC 1
#   endif

# endif

# ifdef NNT_TARGET_MAC

#   ifndef NNT_OPENCL
#     define NNT_OPENCL 1
#   endif

#   ifndef NNT_CUDA
#     define NNT_CUDA 1
#   endif

# endif

# ifdef NNT_MSVC
#   pragma warning (disable: 4996)
#   pragma warning (disable: 4068)
#   pragma warning (disable: 4273)
#   pragma warning (disable: 4251)
#   pragma warning (disable: 4275) // disable dll-interface warning.
#   pragma warning (disable: 4819)
#   pragma warning (disable: 4244)
# endif

# ifdef NNT_CLANG
#   pragma GCC diagnostic ignored "-Wbind-to-temporary-copy"
#   ifdef NNT_DEBUG
#     pragma GCC diagnostic ignored "-Wshorten-64-to-32"
#   endif
# endif

# ifdef NNT_GCC
#   pragma GCC diagnostic ignored "-Wunused-function"
#   pragma GCC diagnostic ignored "-Wreorder"
# endif

# ifdef __BLOCKS__
#   define NNT_BLOCKS 1
# endif

# ifdef NNT_C_OPENCL
#   define NNT_CONST __constant
#   define NNT_GLOBAL __global
#   define NNT_LOCAL __local
//#   define NNT_PRIVATE __private
#   define NNT_STATIC static
# else
#   define NNT_CONST const
#   define NNT_GLOBAL
#   define NNT_LOCAL
//#   define NNT_PRIVATE
#   define NNT_STATIC static
# endif

# ifdef NNT_CXX

#   define NNT_CONST_VAR(type, var) NNT_CONST type var = type ()

# else

#   define NNT_CONST_VAR(type, var) NNT_CONST type var

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

NNT_CONST_VAR(_nullptr, nullptr);

#   endif

class _nullobj
{
public:

    template <typename valT>
        operator valT* () const
    {
        return (valT*)0;
    }

    template <typename valT>
        operator valT const* () const
    {
        return (valT const*)0;
    }

    template <typename valT>
        operator valT () const
    {
        return (valT)0;
    }
    
};

NNT_CONST_VAR(_nullobj, nullobj);

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
# endif

# if defined(LIBNNT)
#   define NNT_LIBRARY_STAIC 1
# else
#   define NNT_LIBRARY_SHARED 1
# endif

# ifdef NNT_KERNEL_SPACE

#   define NNTKS_EXPRESS(exp) exp
#   define NNTUS_EXPRESS(exp) SPACE
#   define NNTKUS_EXPRESS(ks, us) ks

#   define NNTKS_PAGED_CODE code_seg("PAGE")
#   define NNTKS_LOCKED_CODE code_seg()
#   define NNTKS_INIT_CODE code_seg("INIT")
#   define NNTKS_PAGED_DATA data_seg("PAGE")
#   define NNTKS_LOCKED_DATA data_seg()
#   define NNTKS_INIT_DATA data_seg("INIT")

# else

#   define NNTKS_EXPRESS(exp) SPACE
#   define NNTUS_EXPRESS(exp) exp
#   define NNTKUS_EXPRESS(ks, us) us

# endif

# define NNT_INLINE inline
# define NNT_STATIC static
# define NNT_STATIC_IMPL
# define NNT_STATIC_CONST NNT_STATIC NNT_CONST
# define NNT_STATIC_CONST_IMPL
# define inline_impl inline
# define template_impl

# ifdef NNT_MSVC
#   define NNT_MSVC_EXPRESS(exp) exp 
# else
#   define NNT_MSVC_EXPRESS(exp) SPACE
# endif

# ifdef NNT_UNIX
#   define NNT_UNIX_EXPRESS(exp) exp
# else
#   define NNT_UNIX_EXPRESS(exp) SPACE
# endif
    
# ifdef NNT_GCC
#   define NNT_GCC_EXPRESS(exp) exp
# else
#   define NNT_GCC_EXPRESS(exp) SPACE
# endif

# ifdef NNT_BSD
#   define NNT_BSD_EXPRESS(exp) exp
# else
#   define NNT_BSD_EXPRESS(exp) SPACE
# endif

# ifdef NNT_LINUX
#   define NNT_LINUX_EXPRESS(exp) exp
# else
#   define NNT_LINUX_EXPRESS(exp) SPACE
# endif

typedef struct {} arch_unknown;
typedef struct {} arch_x32;
typedef struct {} arch_x64;
typedef struct {} arch_arm;

typedef struct {} os_unknown;
typedef struct {} os_windows;
typedef struct {} os_unix;
typedef struct {} os_mach;
typedef struct {} os_bsd;
typedef struct {} os_linux;

typedef struct {} lang_unknown;
typedef struct {} lang_objc;
typedef struct {} lang_c;
typedef struct {} lang_cxx;
typedef struct {} lang_opencl;

typedef struct {} compr_unknown;
typedef struct {} compr_gcc;
typedef struct {} compr_msvc;
typedef struct {} compr_clang;

typedef struct {} space_kernel;
typedef struct {} space_user;
typedef struct {} space_gpu;

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
# elif defined(NNT_LINUX)
typedef os_linux os_type;
# elif defined(NNT_BSD)
typedef os_bsd os_type;
# elif defined(NNT_UNIX)
typedef os_unix os_type;
# endif

# ifdef NNT_OBJC
typedef lang_objc lang_type;
# elif defined(NNT_CXX)
typedef lang_cxx lang_type;
# elif defined(NNT_C_OPENCL)
typedef lang_opencl lang_type;
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

# ifdef NNT_KERNEL_SPACE
typedef space_kernel space_type;
# elif defined(NNT_GPU_SPACE)
typedef space_gpu space_type;
# else
typedef space_user space_type;
# endif

NNT_CONST_VAR(arch_type, arch_object);
NNT_CONST_VAR(lang_type, lang_object);
NNT_CONST_VAR(compr_type, compr_object);
NNT_CONST_VAR(space_type, space_object);

# ifdef NNT_CPU_SPACE
NNT_CONST_VAR(os_type, os_object);
# endif

# define NNTASM_BEGIN __asm {
# define NNTASM_END }
# define NNTASM(exp) \
NNTASM_BEGIN\
exp \
NNTASM_END

# define NNT_NAMESPACE nnt

# ifdef NNT_CXX
namespace nnt {}
# endif

# define NNT_BEGIN_CXX namespace NNT_NAMESPACE {
# define NNT_END_CXX   }
# define NNT_TYPE(type) ::NNT_NAMESPACE::type

# ifdef NNT_CXX
#   define NNT_USINGCXXNAMESPACE using namespace ::NNT_NAMESPACE;
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

# define NNT_USINGNAMESPACE      NNT_USINGCXXNAMESPACE

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

# ifdef NNT_DEBUG
#	define NNTDEBUG_EXPRESS(express)    express
#	define NNTRELEASE_EXPRESS(express)  SPACE
# else
#	define NNTDEBUG_EXPRESS(express)    SPACE
#	define NNTRELEASE_EXPRESS(express)  express
# endif

# define SPACE
# define TODO(express) {SPACE}
# define PASS {SPACE}

# define NNTMACRO_SELF(val)                    val
# define _NNTMACRO_TOSTR(val)                  #val
# define NNTMACRO_TOSTR(val)                  _NNTMACRO_TOSTR(val)
# define NNTMACRO_COMBINE_2(v0, v1, sep)       NNTMACRO_SELF(v0)##sep##NNTMACRO_SELF(v1)
# define NNTAUTO_NAME                        __nnt_autoname_ ## __LINE__ ## _ ## __FUNCTION__
# define NNTAUTO_NAMED(name)                 __nnt_autoname_ ## name ## _ ## __LINE__ ## _ ## __FUNCTION__

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
#   import <UIKit/UIKit.h>
# endif

# define is_no == NO
# define is_yes == YES

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

# ifndef ENUM_DEFINED
typedef uint enum_t;
# endif

# if defined(NNT_KERNEL_SPACE)
#   define NNT_NO_FLOAT 1
#   define NNT_FLOAT_EXPRESS(exp)
# else
#   define NNT_HAS_FLOAT 1
#   define NNT_FLOAT_EXPRESS(exp) exp
# endif

#ifdef NNT_X64
#  define REAL_IS_DOUBLE  1
NNT_FLOAT_EXPRESS(typedef double real);
   typedef ulonglong uindex, usize, uinteger;
   typedef longlong sindex, ssize, sinteger, integer;
#else
#  define REAL_IS_FLOAT   1
NNT_FLOAT_EXPRESS(typedef float real);
   typedef uint uindex, usize, uinteger;
   typedef int sindex, ssize, sinteger, integer;
#endif

# define MCOMMA ,
# define MDOT .
# define MSEMICOLON ;
# define MCOLON :

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

# ifdef NNT_SIMULATOR
#    define NNTSIM_EXPRESS(exp) exp
# else
#    define NNTSIM_EXPRESS(exp) SPACE
# endif

# if TARGET_OS_IPHONE
#    define IOSEXPRESS(exp) exp
#    define MACEXPRESS(exp) SPACE
#    define MAC_IOS_SELECT(mac, ios) ios
#    define NNT_ISPAD (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
#    define NNT_ISPHONE !NNT_ISPAD
# elif TARGET_OS_MAC
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
#   ifdef NNT_USER_SPACE
#     ifdef NNT_X32
#       define NNTDEBUG_BREAK NNTASM_BEGIN int 3 NNTASM_END
#     else
#       define NNTDEBUG_BREAK SPACE
#     endif
#   else
#     ifdef NNT_MSVC
#       define NNTDEBUG_BREAK KdBreakPoint();
#     else
#       define NNTDEBUG_BREAK SPACE
#     endif
#   endif
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

static void* ptr_offset(void* ptr, usize val)
{
    return (void*)((byte*)ptr + val);
}

# if defined(NNT_C) && !defined(NNT_OBJC) && defined(NNT_USER_SPACE)

#   ifndef bool
typedef int bool;
#   endif

#   ifndef true
#     define true  1
#   endif
#   ifndef false
#     define false 0
#   endif

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
NNTAPI(ulong) timestamp(void);

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

typedef struct {
    uint major;
    uint minor;
    uint patch;
    char const* ver;
} version_t;

//! 0: equal, 1: greater, -1: lesser
NNT_EXTERN int VersionCmp(version_t const* l, version_t const* r);

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

# ifdef NNT_CPU_SPACE
NNT_STATIC_CONST version_t NNTVERSION = {NNT_VERSION_MAJOR, NNT_VERSION_MIN, NNT_VERSION_FIX, NNT_VERSION_STR};
# endif

NNT_BEGIN_HEADER_C

//! get version string.
NNTAPI(char const*) NNTVersion(void);

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

NNT_BEGIN_HEADER_C

# ifdef NNT_USER_SPACE

#   include <stdlib.h>
#   include <stdio.h>
#   include <string.h>
#   include <math.h>
#   include <signal.h>
#   include <sys/types.h>

#   ifdef NNT_UNIX

#     include <unistd.h>
#     include <pthread.h>
#     include <sys/errno.h>

#   endif

# endif // us

# ifdef NNT_KERNEL_SPACE

#   ifdef NNT_BSD

#     include <sys/types.h>
#     include <sys/param.h>
#     include <sys/queue.h>
#     include <sys/module.h>
#     include <sys/kernel.h>
#     include <sys/systm.h>
#     include <sys/conf.h>
#     include <sys/malloc.h>
#     include <sys/uio.h>

#   endif

#   ifdef NNT_LINUX

#     ifdef NNT_CXX

#       define new _keyword_ignore_new_for_c
#       define private _keyword_ignore_private_for_c
#       define namespace _keyword_ignore_namespace_for_c
#       define class _keyword_ignore_class_for_c

#     endif

#     include <linux/init.h>
#     include <linux/kernel.h>
#     include <linux/kdev_t.h>

#     ifdef NNT_PURE_C
#       include <linux/cdev.h>
#       include <linux/slab.h>
#       include <linux/gfp.h>
#       include <linux/fs.h>
#       include <linux/module.h>
#       include <linux/device.h>
#       include <asm-generic/uaccess.h>
#     endif

#     include <queue.h>
#     include <linux/string.h>
#     include <asm-generic/errno.h>

#     ifdef NNT_CXX

#       undef new
#       undef private
#       undef namespace
#       undef class

#     endif

#   endif

# endif // ks

NNT_END_HEADER_C

# ifdef NNT_CXX

# ifdef NNT_USER_SPACE

#   include <string>
#   include <iostream>
#   include <iomanip>
#   include <algorithm>
#   include <exception>

# endif

NNT_BEGIN_HEADER_CXX

typedef struct {} _ignore_null, *ignore_null;

namespace cxx {}
namespace ntl {}
namespace core { using namespace ntl; }

# ifdef NNT_PURE_CXX

using namespace cxx;

# endif

NNT_END_HEADER_CXX

# endif // cxx

// trace.

# ifdef NNT_DEBUG

#   ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

NNT_EXTERN void _trace_obj         (NSString*, id);
NNT_EXTERN void _trace_int         (NSString*, int);
NNT_EXTERN void _trace_float       (NSString*, float);
NNT_EXTERN void _trace_msg         (NSString*);

NNT_END_HEADER_OBJC

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

#     ifdef NNT_CXX

#       ifdef NNT_MSVC

inline_impl void trace_msg(char const* msg)
{
# ifdef NNT_USER_SPACE
    // print into debug view.
    ::OutputDebugStringA("nnt: ");
    ::OutputDebugStringA(msg);
    ::OutputDebugStringA(".\n");
    // print into console.
    ::printf("nnt: %s.\n", msg);
# else
    KdPrint(("nnt: %s.\n", msg));
# endif
}

inline_impl void trace_msg(char* msg)
{
    trace_msg((char const*)msg);
}

template <typename T>
inline_impl void trace_msg(T const& msg)
{
    trace_msg((char const*)msg.c_str());
}

#       else // none msvc.

inline_impl void trace_msg(char const* msg)
{
# ifdef NNT_USER_SPACE
    ::std::cout << msg << ::std::endl << ::std::flush;
# else
    NNT_BSD_EXPRESS(uprintf("nnt: %s.\n", msg));
    NNT_LINUX_EXPRESS(printk(KERN_DEBUG "nnt: %s.\n", msg));
# endif
}

inline_impl void trace_msg(char* msg)
{
    trace_msg((char const*)msg);
}

template <typename T>
inline_impl void trace_msg(T const& str)
{
    trace_msg(str.c_str());
}

#       endif // msvc.

#     else // non cxx.

static void trace_msg(char const* msg)
{
# ifdef NNT_USER_SPACE
    printf(msg, 0);
    printf("\n");
    fflush(stdout);
# else
    NNT_BSD_EXPRESS(uprintf("nnt: %s.\n", msg));
    NNT_LINUX_EXPRESS(printk(KERN_DEBUG "nnt: %s.\n", msg));
# endif
}

#     endif // cxx

#     define trace_if(exp, msg)  { if (exp) { trace_msg(#exp "=> " msg); } }
#     define dthrow(ex)          { throw ex; }
#     define dexpress(ex)        { ex; }

#   endif

# else // release

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

# ifndef YES
#   define YES true
# endif

# ifndef NO
#   define NO false
# endif

# ifndef NULL
#   define NULL 0
# endif

# ifndef nil
#   define nil NULL
# endif

// include all base class.
# include "./CoreTypes.h"
# include "./Object.h"

// pre include objc's object for may inherited by C++ object.
# ifdef NNT_OBJC

#   ifdef NNT_TARGET_MAC
#     import <Cocoa/Cocoa.h>
#   endif

#   define NSInfinite NSNotFound
#   define discard assign

#   import <Foundation/Foundation.h>
#   import "./NSObject+NNT.h"
#   import "./NSLock+NNT.h"

# endif

# ifndef autocollect
#   define autocollect
# endif

// include C++ Base Classes.

# include "../TL/Allocate+NNT.h"
# include "../TL/Memory+NNT.h"
# include "../TL/Stdtype+NNT.h"
# include "../TL/Exception+NNT.h"
# include "../TL/Operator+NNT.h"
# include "../TL/Types+NNT.h"
# include "../TL/Function+NNT.h"
# include "../TL/Closure+NNT.h"
# include "../TL/SmartPtr+NNT.h"

# ifdef NNT_USER_SPACE

# include "../TL/Vector+NNT.h"
# include "../TL/Map+NNT.h"
# include "../TL/Regex+NNT.h"

# endif

# include "../TL/String+NNT.h"
# include "../TL/List+NNT.h"
# include "../TL/Data+NNT.h"
# include "../TL/Tuple+NNT.h"
# include "../TL/Variant+NNT.h"
# include "../TL/Algorithm+NNT.h"

# ifdef NNT_USER_SPACE

// ignore assert.
# include <assert.h>

static void nnt_assert(bool exp, char const* file, ulong line)
{
# ifdef NNT_CXX

    if (!exp)
    {
        NNT_USINGNAMESPACE;
        exception::assert exp;
        exp.file = file;
        exp.line = line;
        throw exp;
    }

# endif

    assert(exp);
}

# ifdef NNT_DEBUG
#   define NNT_ASSERT(exp) nnt_assert((exp), __FILE__, __LINE__)
# else
#   define NNT_ASSERT(exp) {SPACE}
# endif

# ifdef assert
#   undef assert
# endif

// include unit test.
# include "UnitTest.h"

# endif // us

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

# if defined(NNT_CXX) && defined(NNT_USER_SPACE)

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

# endif // cxx

# endif // objc

# ifdef NNT_USER_SPACE

inline_impl real rand01()
{
    return (real)rand() / RAND_MAX;
}

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
