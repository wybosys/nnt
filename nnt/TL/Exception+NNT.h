
# ifndef __NNT_CORE_EXCEPTION_B611A762AA994DF9BC32058B51941D64_H_INCLUDED
# define __NNT_CORE_EXCEPTION_B611A762AA994DF9BC32058B51941D64_H_INCLUDED

# if defined(NNT_CXX)

# ifdef NNT_USER_SPACE

# include <string>
# include <exception>

# endif

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(exception)

# ifdef NNT_USER_SPACE

class basic
    : public ::std::exception
{
public:

    basic() throw()
        : line(0)
    {
        PASS;
    }

    ::std::string file;
    ulong line;

};

class overdrop
: public basic
{
    
};

class earlydrop
: public basic
{
    
};

class overflow
    : public basic
{

};

class assert
    : public basic
{

};

class message
: public basic
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

# endif

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
