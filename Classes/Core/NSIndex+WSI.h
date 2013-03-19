
# ifndef __NNT_NSINDEX_69D2462138EC42129CFC96EE6D018FD9_H_INCLUDED
# define __NNT_NSINDEX_69D2462138EC42129CFC96EE6D018FD9_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface NNTNSIndexPath : NSIndexPath {
    uint _section;
    uint _row;
}

@property (nonatomic, assign) uint section, row;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ns)

class IndexPath
: public Object<NNTNSIndexPath>
{
    typedef Object<NNTNSIndexPath> super;
    
public:
    
    IndexPath()
    {
        PASS;
    }
    
    IndexPath(id path)
    : super((NNTNSIndexPath*)path)
    {
        PASS;
    }
    
    IndexPath(IndexPath const& r)
    : super(r._self)
    {
        PASS;
    }
    
    uint length() const
    {
        return [this->_self length];
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif