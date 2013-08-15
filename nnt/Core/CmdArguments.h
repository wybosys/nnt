
# ifndef __NNT_CMDARGUMENTS_8d75c9578a2944b8b50e8f054bba511a_H_INCLUDED
# define __NNT_CMDARGUMENTS_8d75c9578a2944b8b50e8f054bba511a_H_INCLUDED

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(cmd)

class Arguments
{
public:

    Arguments(int argc = 0, char** argv = NULL);
    Arguments(core::string const&);
    ~Arguments();

    void set(int argc, char** argv);
    void set(core::string const&);
    void clear();

    usize count() const;
    core::string& operator [] (int idx);
    core::string last() const;

    core::string cmd;
    
    typedef core::vector<core::string> arguments_type;
    arguments_type arguments;
    
protected:
    
    class _Finder
    {
    public:                
        
        _Finder& operator = (arguments_type::const_iterator);
        
        arguments_type::const_iterator _pos;
        arguments_type const* _argus;
        
        core::string value() const;
        
    };
    
public:

    _Finder find(core::string const&) const;
    _Finder operator [] (core::string const& k) const
    {
        return find(k);
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
