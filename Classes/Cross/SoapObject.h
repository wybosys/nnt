
# ifndef __NNT_SOAPOBJECT_8C66FD46EE3841BD872C2C5A110B0F90_H_INCLUDED
# define __NNT_SOAPOBJECT_8C66FD46EE3841BD872C2C5A110B0F90_H_INCLUDED

# include "../Core/ObjectDL.h"

# define SOAPDECL_BEGIN_CLASS_EX(clsnm, inst) \
static ::wsi::lang::Class* Class() { \
typedef clsnm soapclass_type;                                          \
::wsi::lang::Class* cls = new ::wsi::lang::Class(#clsnm, (::wsi::lang::Class::instance_type)clsnm::inst); {

# define SOAPDECL_BEGIN_CLASS(clsnm) \
static clsnm* instance() { return new clsnm; } \
SOAPDECL_BEGIN_CLASS_EX(clsnm, instance);

# define SOAPDECL_END_CLASS return cls; }}

# define SOAPDECL_METHOD_BEGIN_EX(mtdnm, func) \
{\
::wsi::lang::Method* mtd = new ::wsi::lang::Method(#mtdnm, \
(::wsi::lang::Method::method_type)\
(int (soapclass_type::*)(::wsi::lang::Method::params_type const&, ::wsi::lang::Method::returns_type&, void*)) \
&soapclass_type::func);

# define SOAPDECL_METHOD_BEGIN(func) \
SOAPDECL_METHOD_BEGIN_EX(func, func)

# define SOAPDECL_METHOD_END cls->methods.push_back(mtd); }

# define SOAPDECL_ARGUMENT(nm) mtd->params[#nm] = new ::wsi::lang::Parameter(#nm);
# define SOAPDECL_OPTIONAL(nm) mtd->params[#nm] = new ::wsi::lang::Parameter(#nm, true);

# define SOAPDECL_ARGUMENTS2(v0, v1) SOAPDECL_ARGUMENT(v0); SOAPDECL_ARGUMENT(v1);
# define SOAPDECL_ARGUMENTS3(v0, v1, v2) SOAPDECL_ARGUMENTS2(v0, v1); SOAPDECL_ARGUMENT(v2);
# define SOAPDECL_ARGUMENTS4(v0, v1, v2, v3) SOAPDECL_ARGUMENTS3(v0, v1, v2); SOAPDECL_ARGUMENT(v3);
# define SOAPDECL_ARGUMENTS5(v0, v1, v2, v3, v4) SOAPDECL_ARGUMENTS4(v0, v1, v2, v3); SOAPDECL_ARGUMENT(v4);
# define SOAPDECL_ARGUMENTS6(v0, v1, v2, v3, v4, v5) SOAPDECL_ARGUMENTS5(v0, v1, v2, v3, v4); SOAPDECL_ARGUMENT(v5);
# define SOAPDECL_ARGUMENTS7(v0, v1, v2, v3, v4, v5, v6) SOAPDECL_ARGUMENTS6(v0, v1, v2, v3, v4, v5); SOAPDECL_ARGUMENT(v6);
# define SOAPDECL_ARGUMENTS8(v0, v1, v2, v3, v4, v5, v6, v7) SOAPDECL_ARGUMENTS7(v0, v1, v2, v3, v4, v5, v6); SOAPDECL_ARGUMENT(v7);
# define SOAPDECL_ARGUMENTS9(v0, v1, v2, v3, v4, v5, v6, v7, v8) SOAPDECL_ARGUMENTS8(v0, v1, v2, v3, v4, v5, v6, v7); SOAPDECL_ARGUMENT(v8);

# define SOAPDECL_RETURN(nm) mtd->returns[#nm] = new ::wsi::lang::Field(#nm);
# define SOAPDECL_RETURNS2(v0, v1) SOAPDECL_RETURN(v0); SOAPDECL_RETURN(v1);
# define SOAPDECL_RETURNS3(v0, v1, v2) SOAPDECL_RETURNS2(v0, v1); SOAPDECL_RETURN(v2);
# define SOAPDECL_RETURNS4(v0, v1, v2, v3) SOAPDECL_RETURNS3(v0, v1, v2); SOAPDECL_RETURN(v3);
# define SOAPDECL_RETURNS5(v0, v1, v2, v3, v4) SOAPDECL_RETURNS4(v0, v1, v2, v3); SOAPDECL_RETURN(v4);
# define SOAPDECL_RETURNS6(v0, v1, v2, v3, v4, v5) SOAPDECL_RETURNS5(v0, v1, v2, v3, v4); SOAPDECL_RETURN(v5);
# define SOAPDECL_RETURNS7(v0, v1, v2, v3, v4, v5, v6) SOAPDECL_RETURNS6(v0, v1, v2, v3, v4, v5); SOAPDECL_RETURN(v6);
# define SOAPDECL_RETURNS8(v0, v1, v2, v3, v4, v5, v6, v7) SOAPDECL_RETURNS7(v0, v1, v2, v3, v4, v5, v6); SOAPDECL_RETURN(v7);
# define SOAPDECL_RETURNS9(v0, v1, v2, v3, v4, v5, v6, v7, v8) SOAPDECL_RETURNS8(v0, v1, v2, v3, v4, v5, v6, v7); SOAPDECL_RETURN(v8);

# define SOAPDECL_METHOD(nm) int nm (::wsi::lang::Method::params_type const& params, ::wsi::lang::Method::returns_type& returns, void* data)

# define SOAPIMPL_METHOD(nm, cls) int cls::nm (::wsi::lang::Method::params_type const& params, ::wsi::lang::Method::returns_type& returns, void* data)

NNT_BEGIN_HEADER_CXX 

NNTDECL_EXTERN_CLASS_NS(parser, SoapDocument);

NNT_BEGIN_NS(soap)

class Fault
{
public:
    
    Fault()
    : code(0)
    {
        PASS;
    }
    
    int code;
    core::string message;
    core::string actor;
};

NNTCLASS(Object);
class Object
: public ::wsi::lang::Object
{
public:
    Fault fault;
    
    int error(int cd, core::string const& msg = core::null_string, core::string const& act = core::null_string)
    {
        fault.code = cd;
        fault.message = msg;
        fault.actor = act;
        return cd;
    }
    
    int error(core::string const& msg, int cd = -1, core::string const& act = core::null_string)
    {
        fault.code = cd;
        fault.message = msg;
        fault.actor = act;
        return cd;
    }
    
    int error(core::string const& msg, core::string const& act = core::null_string, int cd = -1)
    {
        fault.code = cd;
        fault.message = msg;
        fault.actor = act;
        return cd;
    }
    
    variant_t const& param(core::string const& key, ::wsi::lang::Method::params_type const& params) const
    {
        ::wsi::lang::Method::params_type::const_iterator found = params.find(key);
        if (found == params.end())
            return variant_t::Null();
        return *found->second;
    }
    
    variant_t& ret(core::string const& key, ::wsi::lang::Method::returns_type& returns) const
    {
        ::wsi::lang::Method::returns_type::iterator found = returns.find(key);
        if (found == returns.end())
			return core::ref(variant_t::Null());
        return *found->second;
    }
    
};

NNTAPI(lang::Namespace*) getNamespace();

NNTCLASS(Invoker);
class Invoker
{
public:
    Invoker(parser::SoapDocument&);
    
protected:
    
    //! create class from soap.
    lang::Class* to_class() const;
    
    //! free the temp class.
    void free(lang::Class*) const;
    
    //! instance a soap object.
    lang::Object* instance() const;
    lang::Object* instance(lang::Class const*) const;
    
public:
    //! invoke.
    void invoke(void* data, lang::Namespace* = NULL);
    void invoke(lang::Namespace*, void* data = NULL);
    void invoke() { _invoke(NULL, NULL); }

protected:
    void _invoke(void* data, lang::Namespace*);
    
protected:
    parser::SoapDocument* _doc;
};

NNT_END_NS 
NNT_END_HEADER_CXX

# endif
