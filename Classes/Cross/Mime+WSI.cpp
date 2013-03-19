
# include "Core.h"
# include "Mime+WSI.h"

WSI_BEGIN_CXX
WSI_BEGIN_NS(cross)
WSI_BEGIN_NS(mime)

class MimeMap
{
public:
    
    MimeMap()
    {
        map.insert(core::make_pair("image/jpeg", IMAGE_JPEG));
        map.insert(core::make_pair("image/gif", IMAGE_GIF));
        map.insert(core::make_pair("image/bmp", IMAGE_BMP));
        map.insert(core::make_pair("image/png", IMAGE_PNG));
        map.insert(core::make_pair("image/tiff", IMAGE_TIFF));
        
        map.insert(core::make_pair("text/plain", TEXT_PLAIN));
        map.insert(core::make_pair("text/css", TEXT_CSS));
        map.insert(core::make_pair("text/html", TEXT_HTML));
        map.insert(core::make_pair("text/javascript", TEXT_JAVASCRIPT));
        map.insert(core::make_pair("text/rtf", TEXT_RTF));
    }
  
    typedef core::map<core::string, MimeType> map_type;
    map_type map;
    
    static map_type& shared()
    {
        static MimeMap __gs_mimes = MimeMap();
        return __gs_mimes.map;
    }
};

MimeType MimeFromString(core::string const& str)
{
    MimeMap::map_type::const_iterator found = MimeMap::shared().find(str);
    if (found != MimeMap::shared().end())
        return found->second;
    return UNKNOWN;
}

core::string MimeToString(MimeType type)
{
    core::string ret;
    switch (type)
    {
        default:
        case UNKNOWN: break;
        case IMAGE_JPEG: ret = "image/jpeg"; break;
        case IMAGE_BMP: ret = "image/bmp"; break;
        case IMAGE_GIF: ret = "image/gif"; break;
        case IMAGE_PNG: ret = "image/png"; break;
        case IMAGE_TIFF: ret = "image/tiff"; break;
        case TEXT_CSS: ret = "text/css"; break;
        case TEXT_HTML: ret = "text/html"; break;
        case TEXT_JAVASCRIPT: ret = "text/javascript"; break;
        case TEXT_PLAIN: ret = "text/plain"; break;
        case TEXT_RTF: ret = "text/rtf"; break;
    }
    return ret;
}

core::string MimeNameMake(core::string const& name, MimeType type)
{
    core::string ret = name + "." + MimeToExt(type);
    return ret;
}

class MimeExtMap
{
public:
    
    MimeExtMap()
    {
        map.insert(core::make_pair("jpg", IMAGE_JPEG));
        map.insert(core::make_pair("gif", IMAGE_GIF));
        map.insert(core::make_pair("bmp", IMAGE_BMP));
        map.insert(core::make_pair("png", IMAGE_PNG));
        map.insert(core::make_pair("tif", IMAGE_TIFF));
    }
    
    typedef core::map<core::string, MimeType> map_type;
    map_type map;
    
    static map_type& shared()
    {
        static MimeExtMap __gs_mimes = MimeExtMap();
        return __gs_mimes.map;
    }
};

MimeType MimeFromExt(core::string const& str)
{
    MimeExtMap::map_type::const_iterator found = MimeExtMap::shared().find(str);
    if (found != MimeExtMap::shared().end())
        return found->second;
    return UNKNOWN;
}

core::string MimeToExt(MimeType type)
{
    core::string ret;
    switch (type)
    {
        default:
        case UNKNOWN: break;
        case IMAGE_JPEG: ret = "jpg"; break;
        case IMAGE_BMP: ret = "bmp"; break;
        case IMAGE_GIF: ret = "gif"; break;
        case IMAGE_PNG: ret = "png"; break;
        case IMAGE_TIFF: ret = "tif"; break;
    }
    return ret;
}

core::string MimeToExt(core::string const& str)
{
    MimeType mt = MimeFromString(str);
    return MimeToExt(mt);
}

WSI_END_NS
WSI_END_NS
WSI_END_CXX
