
# ifndef __WSI_NSINDEX_69D2462138EC42129CFC96EE6D018FD9_H_INCLUDED
# define __WSI_NSINDEX_69D2462138EC42129CFC96EE6D018FD9_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface WSINSIndexPath : NSIndexPath {
    uint _section;
    uint _row;
}

@property (nonatomic, assign) uint section, row;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ns)

class IndexPath
: public Object<WSINSIndexPath>
{
    typedef Object<WSINSIndexPath> super;
    
public:
    
    IndexPath()
    {
        PASS;
    }
    
    IndexPath(id path)
    : super((WSINSIndexPath*)path)
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

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif