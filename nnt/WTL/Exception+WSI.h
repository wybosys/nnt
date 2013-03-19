
# ifndef __WSI_CORE_EXCEPTION_B611A762AA994DF9BC32058B51941D64_H_INCLUDED
# define __WSI_CORE_EXCEPTION_B611A762AA994DF9BC32058B51941D64_H_INCLUDED

# ifdef WSI_CXX

# include <string>
# include <exception>

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(exception)

class overdrop
: public ::std::exception
{
    
};

class earlydrop
: public ::std::exception
{
    
};

class message
: public ::std::exception
{
public:
    
	message(::std::string const& str, ::std::string const& title = "Exception") throw()
    : _str(str), _title(title)
    {
		PASS;
    }
    
    ~message() throw()
    {
        PASS;
    }

	::std::string const& title() const
	{
		return _title;
	}
    
    virtual const char* what() const throw()
    {
        return _str.c_str();
    }
    
	void set(::std::string const& str) throw()
    {
        _str = str;
    }

	void set(::std::string const& str, ::std::string const& title) throw()
	{
		_str = str;
		_title = title;
	}
    
    ::std::string const& get() const throw()
    {
        return _str;
    }
    
protected:
   
	::std::string _title; 
    ::std::string _str;
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif