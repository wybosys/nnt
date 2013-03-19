
# ifndef __WSI_UIKIT_TABLETREEVIEW_88A682FF0DD9440194B66973039F9277_H_INCLUDED
# define __WSI_UIKIT_TABLETREEVIEW_88A682FF0DD9440194B66973039F9277_H_INCLUDED

# import "UITableView+WSI.h"
# import "UITableTreeCell.h"

WSI_BEGIN_HEADER_OBJC

@protocol UITableTreeViewDataSource < UITableViewDataSource >

@end

@protocol UITableTreeViewDelegate < UITableViewDelegate >

@end

@interface UITableTreeView : WSIUITableView

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class TableTreeView
: public tpl::TableView<UITableTreeView>
{
    
    typedef tpl::TableView<UITableTreeView> super;
    
public:
    
    TableTreeView(view_type* view,
                  bool needremove = false)
    : super(view, needremove)
    {
        PASS;
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif