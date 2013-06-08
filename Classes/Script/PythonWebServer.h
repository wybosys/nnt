
# ifndef __NNT_SCRIPT_PYTHONWEBSERVER_0829BB066646412C9C9B9663C582C471_H_INCLUDED
# define __NNT_SCRIPT_PYTHONWEBSERVER_0829BB066646412C9C9B9663C582C471_H_INCLUDED

# include "../TL/URI+NNT.h"

NNT_BEGIN_HEADER_CXX

NNTDECL_EXTERN_CLASS_NS(script, Python);

NNT_BEGIN_NS(python)

NNTDECL_PRIVATE_HEAD_CXX(HttpRequest);

class HttpRequest
{
    NNTDECL_PRIVATE_CXX(HttpRequest);
    
public:
    
    HttpRequest();
    ~HttpRequest();
    
    bool process();
    script::Python& py();

    core::string method;
    core::uri uri;
    core::data stream;
    
};

class WebRequest
: public HttpRequest
{
public:
    
    WebRequest();
    ~WebRequest();
    
};

class FileRequest
: public HttpRequest
{
public:
    
    FileRequest();
    ~FileRequest();
    
    bool process();
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
