
# include "Core.h"
# include "HttpParser.h"

WSI_BEGIN_CXX
WSI_BEGIN_NS(parser)

Http::Http()
{
    newline = "\r\n";
}

Http::~Http()
{

}

core::data Http::doctype() const
{
    return core::null_data;
}

core::data Http::header() const
{
    return core::null_data;
}

core::data Http::body() const
{
    return data;
}

core::data Http::full() const
{
    core::data ret;

    ret.append(doctype());
    ret.append(newline);
    ret.append(header());
    ret.append(newline);
    ret.append(body());
    ret.append(newline);

    return ret;
}

Http11::Http11()
{
    version = "HTTP/1.1";

    req_code = 200;
    req_message = "OK";

    content_type = "text/plain";
}

Http11::~Http11()
{

}

core::data Http11Response::doctype() const
{
    core::string str = version + " " + core::tostr(req_code) + " " + req_message;
    return core::dup_cast<core::data>(str);
}

core::data Http11Response::header() const
{
    core::string str = "Content-Type: " + content_type + newline;
    str += "Content-Length: " + core::tostr(data.length()) + newline;
    return core::dup_cast<core::data>(str);
}

WSI_END_NS
WSI_END_CXX
