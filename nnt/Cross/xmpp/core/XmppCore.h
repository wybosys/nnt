
# ifndef __XMPP_CORE_84EB2812913D4B499ED56D3743C190AA_H_INCLUDED
# define __XMPP_CORE_84EB2812913D4B499ED56D3743C190AA_H_INCLUDED

# include "../XmppObject.h"

# define XMPPCORE_HEADER_BEGIN \
NNT_BEGIN_HEADER_CXX \
NNT_BEGIN_NS(xmpp) \
NNT_BEGIN_NS(cor)

# define XMPPCORE_HEADER_END \
NNT_END_NS \
NNT_END_NS \
NNT_END_HEADER_CXX

# define XMPPCORE_BEGIN \
NNT_BEGIN_CXX \
NNT_BEGIN_NS(xmpp) \
NNT_BEGIN_NS(cor)

# define XMPPCORE_END \
NNT_END_NS \
NNT_END_NS \
NNT_END_CXX

XMPPCORE_HEADER_BEGIN

typedef enum
{
    MECHANISM_UNKNOWN = 0,
    MECHANISM_MD5DIGEST = 0x1,
    MECHANISM_PLAIN = 0x2,
    MECHANISM_MD5CRAM = 0x4,
    MECHANISM_ANONYMOUS = 0x8,
}
MechanismType;

typedef enum
{
    COMPRESSION_UNKNOWN = 0,
    COMPRESSION_ZLIB = 0x1,
}
CompressionType;

typedef enum
{
    IQ_UNKNOWN = 0,
    IQ_GET,
    IQ_SET,
    IQ_RESULT,
    IQ_ERROR,
}
IqType;

NNTAPI(IqType) IqTypeFromString(core::string const&);
NNTAPI(core::string) IqTypeToString(IqType);

enum
{
    ERR_UNKNOWN = 0xF0000000,
    ERR_NOT_AUTHORIZED = 0x00000001,
};
typedef uint ErrorCode;

ErrorCode ErrorCodeFromString(core::string const&);

template <typename implT,
typename objT = Object
>
class ObjectImpl
: public objT,
public ResponseObject<implT>
{
protected:
    
    typedef objT super;
    
};

XMPPCORE_HEADER_END

# endif