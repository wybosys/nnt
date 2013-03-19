
# ifndef __NNT_MIME_273008C7893E4BA59C0BB8533F0E5643_H_INCLUDED
# define __NNT_MIME_273008C7893E4BA59C0BB8533F0E5643_H_INCLUDED

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(cross)
NNT_BEGIN_NS(mime)

typedef enum
{
    UNKNOWN,
    
    IMAGE_JPEG,
    IMAGE_BMP,
    IMAGE_PNG,
    IMAGE_GIF,
    IMAGE_TIFF,
    
    TEXT_PLAIN,
    TEXT_CSS,
    TEXT_HTML,
    TEXT_JAVASCRIPT,
    TEXT_RTF,
}
MimeType;

NNTAPI(MimeType) MimeFromString(core::string const&);
NNTAPI(core::string) MimeToString(MimeType);
NNTAPI(core::string) MimeNameMake(core::string const& name, MimeType);
NNTAPI(core::string) MimeToExt(MimeType);
NNTAPI(MimeType) MimeFromExt(core::string const&);
NNTAPI(core::string) MimeToExt(core::string const&);

NNT_END_NS
NNT_END_NS
NNT_END_HEADER_CXX

# endif

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

NNT_EXTERN NSString* kMimeTypeFormUrlEncoded;
NNT_EXTERN NSString* kMimeTypeTextPlain;
NNT_EXTERN NSString* kMimeTypeTextHtml;
NNT_EXTERN NSString* kMimeTypeTextJson;
NNT_EXTERN NSString* kMimeTypeTextXml;

NNT_END_HEADER_OBJC

# endif

# endif
