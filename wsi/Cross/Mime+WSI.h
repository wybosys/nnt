
# ifndef __WSI_MIME_273008C7893E4BA59C0BB8533F0E5643_H_INCLUDED
# define __WSI_MIME_273008C7893E4BA59C0BB8533F0E5643_H_INCLUDED

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(cross)
WSI_BEGIN_NS(mime)

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

WSIAPI(MimeType) MimeFromString(core::string const&);
WSIAPI(core::string) MimeToString(MimeType);
WSIAPI(core::string) MimeNameMake(core::string const& name, MimeType);
WSIAPI(core::string) MimeToExt(MimeType);
WSIAPI(MimeType) MimeFromExt(core::string const&);
WSIAPI(core::string) MimeToExt(core::string const&);

WSI_END_NS
WSI_END_NS
WSI_END_HEADER_CXX

# endif

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

WSI_EXTERN NSString* kMimeTypeFormUrlEncoded;
WSI_EXTERN NSString* kMimeTypeTextPlain;
WSI_EXTERN NSString* kMimeTypeTextHtml;
WSI_EXTERN NSString* kMimeTypeTextJson;
WSI_EXTERN NSString* kMimeTypeTextXml;

WSI_END_HEADER_OBJC

# endif

# endif
