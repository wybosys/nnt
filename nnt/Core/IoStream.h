
# ifndef __NNT_IOSTREAM_28F34FBAAF6B45529F9B7D195BFDA1D5_H_INCLUDED
# define __NNT_IOSTREAM_28F34FBAAF6B45529F9B7D195BFDA1D5_H_INCLUDED

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(core)

class Io
{
public:
    
    typedef ntl::mpl::position<0> read;
    typedef ntl::mpl::position<1> write;
    typedef ntl::mpl::position<2> create;
    typedef ntl::mpl::position<3> close;
    typedef ntl::mpl::position<4> binary;
    typedef ntl::mpl::position<5> append;
    
    enum seek
    {
        seek_cur = 0,
        seek_end = 1,
        seek_set = 2,
    };
    
};

class IoStream
: public VirObject
{
public:
    
    virtual usize write(core::data const&) = 0;
    virtual usize read(core::data&) = 0;
    virtual usize position() const = 0;
    virtual void seek(offset, Io::seek) = 0;
    virtual usize length() const = 0;
    
};

NNT_END_NS

using core::Io;

NNT_END_HEADER_CXX

# endif

# endif
