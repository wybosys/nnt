
# ifndef __NNT_UIKIT_GRIDVIEWCONTROLLER_562689865C2A4AB0ACC98598A4543F12_H_INCLUDED
# define __NNT_UIKIT_GRIDVIEWCONTROLLER_562689865C2A4AB0ACC98598A4543F12_H_INCLUDED

# import "UIViewController+NNT.h"

NNT_BEGIN_HEADER_OBJC

@interface UIGridViewController : NNTUIViewController {
    usize rows, cols;
}

@property (nonatomic, assign) usize rows, cols;
@property (nonatomic, readonly) UIGridView* gridView;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "UIViewController+NNT.h"

NNT_BEGIN_HEADER_OBJC
_CXXCONTROLLER_DECL(UIGridViewController);
NNT_END_HEADER_OBJC

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class GridViewController
: public SimpleController<GridViewController,
_CXXCONTROLLER(UIGridViewController), NNTUIView
>
{
    typedef SimpleController<GridViewController,
    _CXXCONTROLLER(UIGridViewController),
    NNTUIView
    > super;
    
public:
    
    usize rows() const
    {
        return this->_self.rows;
    }
    
    usize cols() const
    {
        return this->_self.cols;
    }
    
    void set_rows(uint rows)
    {
        this->_self.rows = rows;
    }
    
    void set_cols(uint cols)
    {
        this->_self.cols = cols;
    }
    
    UIGridView* gridView()
    {
        return this->_self.gridView;
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif