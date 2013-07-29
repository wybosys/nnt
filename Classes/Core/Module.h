
# ifndef __NNT_CORE_MODULE_D3A8AE56C9884A5F92B513B0AC1EFFBA_H_INCLUDED
# define __NNT_CORE_MODULE_D3A8AE56C9884A5F92B513B0AC1EFFBA_H_INCLUDED

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(core)

NNTCLASS(Module);

NNTDECL_PRIVATE_HEAD_CXX(Module);

class Module
{
    NNTDECL_PRIVATE_CXX(Module);
    
public:
    
    Module();
    Module(core::string const&);
    ~Module();
    
    bool open(core::string const&);
    bool is_opened() const;
    void close();
    void* find(core::string const&) const;

    static core::string PrefixName();
    static core::string ExtName();
    
    inline void* operator [] (core::string const& name) const
    {
        return find(name);
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
