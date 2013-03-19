/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */
/* Turn off the GCC specific __attribute__ keyword */
#if !defined (__GNUC__) || __GNUC__ < 2
# define __attribute__(x)
#endif



/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* location of authentication plugins. */
#define AUTHPLUGINDIR "/usr/local/lib/esmtp-plugins"

/* support non-standard EHLO AUTH= response */
#define AUTH_ID_HACK 1

/* Enable additional debugging code */
/* #undef DEBUG */

/* Define to 1 if you have the declaration of `tzname', and to 0 if you don't.
   */
/* #undef HAVE_DECL_TZNAME */

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* the dlsym() function is available */
#define HAVE_DLSYM 1

/* Does system provide RFC 2553/Posix getaddrinfo? */
#define HAVE_GETADDRINFO 1

/* Number of parameters to gethostbyname_r or 0 if not available */
/* #undef HAVE_GETHOSTBYNAME_R */

/* Define to 1 if you have the `gethostname' function. */
#define HAVE_GETHOSTNAME 1

/* Set when getipnodebyname is available */
/* #undef HAVE_GETIPNODEBYNAME */

/* Define to 1 if you have the `gettimeofday' function. */
#define HAVE_GETTIMEOFDAY 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Set when -lcrypto from OpenSSL is available */
#define HAVE_LIBCRYPTO 1

/* Define to 1 if you have the `lwres' library (-llwres). */
/* #undef HAVE_LIBLWRES */

/* Define to 1 if you have the `localtime' function. */
/* #undef HAVE_LOCALTIME */

/* Set when localtime_r is available */
#define HAVE_LOCALTIME_R 1

/* Define to 1 if you have the <lwres/netdb.h> header file. */
/* #undef HAVE_LWRES_NETDB_H */

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `memrchr' function. */
/* #undef HAVE_MEMRCHR */

/* Define if you have POSIX threads libraries and header files. */
/* #undef HAVE_PTHREAD */

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strcasecmp' function. */
#define HAVE_STRCASECMP 1

/* Define to 1 if you have the `strdup' function. */
#define HAVE_STRDUP 1

/* Define to 1 if you have the `strerror' function. */
/* #undef HAVE_STRERROR */

/* Define to 1 if you have the `strerror_r' function. */
#define HAVE_STRERROR_R 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strncasecmp' function. */
#define HAVE_STRNCASECMP 1

/* Define to 1 if you have the `strtol' function. */
#define HAVE_STRTOL 1

/* Define to 1 if `tm_zone' is a member of `struct tm'. */
#define HAVE_STRUCT_TM_TM_ZONE 1

/* Define to 1 if you have the <sys/ioctl.h> header file. */
#define HAVE_SYS_IOCTL_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if your `struct tm' has `tm_zone'. Deprecated, use
   `HAVE_STRUCT_TM_TM_ZONE' instead. */
#define HAVE_TM_ZONE 1

/* Define to 1 if you don't have `tm_zone' but do have the external array
   `tzname'. */
/* #undef HAVE_TZNAME */

/* Define to 1 if you have the `uname' function. */
#define HAVE_UNAME 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* snprintf correctly terminates the buffer on overflow */
#define HAVE_WORKING_SNPRINTF 1

/* strerror_r works! */
#define HAVE_WORKING_STRERROR_R 1

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Disable assertions */
#define NDEBUG 1

/* Name of package */
#define PACKAGE "libesmtp"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME ""

/* Define to the full name and version of this package. */
#define PACKAGE_STRING ""

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME ""

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION ""

/* Define to the necessary symbol if this constant uses a non-standard name on
   your system. */
/* #undef PTHREAD_CREATE_JOINABLE */

/* The size of `unsigned int', as computed by sizeof. */
#define SIZEOF_UNSIGNED_INT 4

/* The size of `unsigned long', as computed by sizeof. */
#define SIZEOF_UNSIGNED_LONG 8

/* The size of `unsigned short', as computed by sizeof. */
#define SIZEOF_UNSIGNED_SHORT 2

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define to 1 if you can safely include both <sys/time.h> and <time.h>. */
#define TIME_WITH_SYS_TIME 1

/* Define to 1 if your <sys/time.h> declares `struct tm'. */
/* #undef TM_IN_SYS_TIME */

/* Enable experimental support for SMTP CHUNKING extension */
#define USE_CHUNKING 1

/* Enable experimental support for SMTP ETRN extension */
/* #undef USE_ETRN */

/* Enable IPv6 support */
/* #undef USE_IPV6 */

/* Build with support for Posix threading */
#define USE_PTHREADS 1

/* Build with support for SMTP AUTH using SASL */
#define USE_SASL 1

/* Build with support for SMTP STARTTLS extension */
#define USE_TLS 1

/* Enable support for sendmail XUSR extension */
#define USE_XUSR 1

/* Version number of package */
#define VERSION "1.0.6"

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
/* #  undef WORDS_BIGENDIAN */
# endif
#endif

/* GNU needs this for strcasecmp etc */
/* #undef _GNU_SOURCE */

/* ISO compliant code */
#define _ISOC99_SOURCE 1

/* ISO compliant code */
#define _ISOC9X_SOURCE 1

/* OSF needs this for getaddrinfo */
/* #undef _OSF_SOURCE */

/* POSIX compliant code */
#define _POSIX_C_SOURCE 199506L

/* Single Unix conformance */
#define _XOPEN_SOURCE 500

/* Sun's netdb.h needs this for getaddrinfo */
/* #undef __EXTENSIONS__ */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif
