
# ifndef __NNT_PARSER_HTTP_1c1af7ed6efd43d59d0d52591b9d4a94_H_INCLUDED
# define __NNT_PARSER_HTTP_1c1af7ed6efd43d59d0d52591b9d4a94_H_INCLUDED

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(parser)

NNTCLASS(Http);

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

NNTCLASS(Http11);

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

NNTCLASS(Http11Response);

class Http11Response
    : public Http11
{
public:

    virtual core::data doctype() const;
    virtual core::data header() const;

};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
