
# ifndef __WSI_PARSER_HTTP_1c1af7ed6efd43d59d0d52591b9d4a94_H_INCLUDED
# define __WSI_PARSER_HTTP_1c1af7ed6efd43d59d0d52591b9d4a94_H_INCLUDED

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(parser)

WSICLASS(Http);

class Http
{
public:

    Http();
    ~Http();

    virtual core::data doctype() const;
    virtual core::data header() const;
    virtual core::data body() const;
    virtual core::data full() const;

    core::string version;
    core::string newline;
    core::data data;

};

WSICLASS(Http11);

class Http11
    : public Http
{
public:

    Http11();
    ~Http11();

    uint req_code;
    core::string req_message;
    core::string content_type;

};

WSICLASS(Http11Response);

class Http11Response
    : public Http11
{
public:

    virtual core::data doctype() const;
    virtual core::data header() const;

};

WSI_END_NS
WSI_END_HEADER_CXX

# endif
