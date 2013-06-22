
# ifndef __NNT_UIKIT_UITABLEVIEW_9936255BA1494E9FAFFA4EC2EB1D651B_H_INCLUDED
# define __NNT_UIKIT_UITABLEVIEW_9936255BA1494E9FAFFA4EC2EB1D651B_H_INCLUDED

# import "UIView+NNT.h"
# import "UIScrollHeaderView.h"
# import "UIHeaderView.h"

NNT_BEGIN_HEADER_OBJC

@interface NNTUITableView : UITableView <NNTUITablePullRefreshDelegate, NNTUITablePullMoreDelegate> {    
    NNTOBJECT_DECL;
    
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

NNTOBJECT_PROP;

@end

NNT_EXTERN signal_t kSignalViewClicked;

# define UITABLEVIEW_IMPL_PULLMOREHEADER \
- (void)scrollViewDidScroll:(NNTUITableView *)tabview{ \
[tabview startPullMoreHeader]; \
} \
- (void)scrollViewDidEndDragging:(NNTUITableView *)tabview willDecelerate:(BOOL)decelerate{	\
[tabview endPullMoreHeader]; \
}


NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "UIScrollView+NNT.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

NNT_BEGIN_NS(tpl)

template <typename viewT>
class TableView
: public ScrollView<TableView<viewT>, viewT>
{
    typedef ScrollView<TableView<viewT>, viewT> super;
    
public:
    
    typedef ::nnt::Object* cell_pointer;
    
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

NNT_END_NS

typedef tpl::TableView<NNTUITableView> TableView;

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif