
# include "Core.h"
# include "JsonObjParser.h"

NNT_BEGIN_HEADER_C
# include "../../contrib/json/json.h"
NNT_END_HEADER_C

NNT_BEGIN_CXX
NNT_BEGIN_NS(parser)

NNTDECL_PRIVATE_BEGIN_CXX(JsonDocument)

void init()
{
    root = NULL;
}

void dealloc()
{
    clear();
}

void clear()
{
    if (root)
    {
        json_object_put(root);
        root = NULL;
    }
}

json_object* root;

NNTDECL_PRIVATE_END_CXX

JsonDocument::JsonDocument()
{
    NNTDECL_PRIVATE_CONSTRUCT(JsonDocument);
}

JsonDocument::~JsonDocument()
{
    NNTDECL_PRIVATE_DESTROY();
}

void JsonDocument::clear()
{
    d_ptr->clear();
}

bool JsonDocument::parse(core::data const& da)
{
    clear();
    
    json_tokener* tok = json_tokener_new();
    d_ptr->root = json_tokener_parse_ex(tok, (char const*)da.bytes(), (int)da.length());
    bool ret = tok->err == json_tokener_success;
    json_tokener_free(tok);

    return ret;
}

bool JsonDocument::save(core::data& da) const
{
    if (d_ptr->root == NULL)
        return false;
    
    char const* str = json_object_to_json_string(d_ptr->root);
    usize len = strlen(str);
    da = core::data((byte*)str, len, core::copy);
    return true;
}

JsonObj::JsonObj(JsonDocument& doc)
: _doc(doc)
{
    
}

JsonObj::~JsonObj()
{
    
}

lang::Object* JsonObj::to_object() const
{
    return NULL;
}

bool JsonObj::to_data(lang::Object const* obj)
{
    return false;
}

NNT_END_NS
NNT_END_CXX
