
# ifndef __WSI_UIKIT_UITABLEVIEW_9936255BA1494E9FAFFA4EC2EB1D651B_H_INCLUDED
# define __WSI_UIKIT_UITABLEVIEW_9936255BA1494E9FAFFA4EC2EB1D651B_H_INCLUDED

# import "UIView+WSI.h"
# import "UIScrollHeaderView.h"
# import "UIHeaderView.h"

WSI_BEGIN_HEADER_OBJC

@interface WSIUITableView : UITableView <WSIUITablePullRefreshDelegate, WSIUITablePullMoreDelegate> {    
    WSIOBJECT_DECL;
    
    //! pull header.
    UIPullRefreshHeaderView *pullRefreshHeader;
    UIPullMoreHeaderView *pullMoreHeader;
    
    //! header view. default is nil.
    UIHeaderView* topHeaderView;
    UIHeaderView* bottomHeaderView;
}

@property (nonatomic, retain) UIPullRefreshHeaderView *pullRefreshHeader;
@property (nonatomic, retain) UIPullMoreHeaderView *pullMoreHeader;
@property (nonatomic, readonly) BOOL isPullRefreshHeaderReloading, isPullMoreHeaderloading;
@property (nonatomic, retain) UIHeaderView *topHeaderView, *bottomHeaderView;

//! send global event. default is YES.
@property (nonatomic, assign) BOOL sendGlobalEvent;

- (UIPullRefreshHeaderView*)enablePullRefreshHeader;
- (UIPullMoreHeaderView*)enablePullMoreHeader;

//! start pull header.
//! refresh header will be auto create.
- (void)startPullRefreshHeader;

//! u should make more-header avalidable by use initPullMoreHeader.
- (void)startPullMoreHeader;

//! end pull header.
- (void)endPullRefreshHeader;
- (void)endPullMoreHeader;

//! remove pull header.
- (void)removePullRefreshHeader;
- (void)removePullMoreHeader;

//! reload data.
- (void)reloadDataSourceByPullRefreshHeader;
- (void)loadDataSourceByPullMoreHeader;

//! finish loading,
- (void)didFinishedLoadingByPullRefreshHeader;
- (void)didFinishedLoadingByPullMoreHeader;

WSIOBJECT_PROP;

@end

WSI_EXTERN signal_t kSignalViewClicked;

# define UITABLEVIEW_IMPL_PULLMOREHEADER \
- (void)scrollViewDidScroll:(WSIUITableView *)tabview{ \
[tabview startPullMoreHeader]; \
} \
- (void)scrollViewDidEndDragging:(WSIUITableView *)tabview willDecelerate:(BOOL)decelerate{	\
[tabview endPullMoreHeader]; \
}


WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# include "UIScrollView+WSI.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

WSI_BEGIN_NS(tpl)

template <typename viewT>
class TableView
: public ScrollView<TableView<viewT>, viewT>
{
    typedef ScrollView<TableView<viewT>, viewT> super;
    
public:
    
    typedef ::wsi::Object* cell_pointer;
    
    TableView(viewT* view,
              bool needremove = false)
    : super(view, needremove)
    {
        PASS;
    }
  
    void set_editable(bool val, bool ani = true)
    {
        [this->_self setEditing:val animated:ani];
    }
    
    bool is_editable() const
    {
        return this->_self.editing;
    }
    
    void set_separator(UITableViewCellSeparatorStyle style)
    {
        this->_self.separatorStyle = style;
    }
    
    UITableViewCellSeparatorStyle separator_style() const
    {
        return this->_self.separatorStyle;
    }
    
    void set_separator(ui::Color const& cor)
    {
        this->_self.separatorColor = cor;
    }
    
    UIColor* separator_color() const
    {
        return this->_self.separatorColor;
    }
    
    virtual core::vector<cell_pointer> visible_cells() const;
            
};

WSI_END_NS

typedef tpl::TableView<WSIUITableView> TableView;

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif