
# ifndef __NNT_UIKIT_TABLETREEVIEW_88A682FF0DD9440194B66973039F9277_H_INCLUDED
# define __NNT_UIKIT_TABLETREEVIEW_88A682FF0DD9440194B66973039F9277_H_INCLUDED

# import "UITableView+NNT.h"
# import "UITableTreeCell.h"

NNT_BEGIN_HEADER_OBJC

@protocol UITableTreeViewDataSource < UITableViewDataSource >

@end

@protocol UITableTreeViewDelegate < UITableViewDelegate >

@end

@interface UITableTreeView : NNTUITableView

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

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

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif