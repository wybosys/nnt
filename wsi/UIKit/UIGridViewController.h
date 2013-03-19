
# ifndef __WSI_UIKIT_GRIDVIEWCONTROLLER_562689865C2A4AB0ACC98598A4543F12_H_INCLUDED
# define __WSI_UIKIT_GRIDVIEWCONTROLLER_562689865C2A4AB0ACC98598A4543F12_H_INCLUDED

# import "UIViewController+WSI.h"

WSI_BEGIN_HEADER_OBJC

@interface UIGridViewController : WSIUIViewController {
    usize rows, cols;
}

@property (nonatomic, assign) usize rows, cols;
@property (nonatomic, readonly) UIGridView* gridView;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# include "UIViewController+WSI.h"

WSI_BEGIN_HEADER_OBJC
_CXXCONTROLLER_DECL(UIGridViewController);
WSI_END_HEADER_OBJC

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class GridViewController
: public SimpleController<GridViewController,
_CXXCONTROLLER(UIGridViewController), WSIUIView
>
{
    typedef SimpleController<GridViewController,
    _CXXCONTROLLER(UIGridViewController),
    WSIUIView
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

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif