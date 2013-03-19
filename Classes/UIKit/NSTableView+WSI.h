
# ifndef __WSINS_TABLEVIEW_BF92B562F8204EF9A9F32671A485C426_H_INCLUDED
# define __WSINS_TABLEVIEW_BF92B562F8204EF9A9F32671A485C426_H_INCLUDED

# include "NSControl+WSI.h"
# include "NSScrollView+WSI.h"

WSI_BEGIN_HEADER_OBJC

@interface WSINSTableView : NSTableView

- (void)deselectSelection;

@end

# ifdef WSI_CXX

@interface _cxx_nstableview : WSINSTableView <NSTableViewDelegate, NSTableViewDataSource>

@end

# endif

WSI_EXTERN signal_t kSignalSelectChanged;

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX 
WSI_BEGIN_NS(ui)

class TableView
: public Control < TableView,
_cxx_nstableview
>
{    
    typedef Control < TableView,
    _cxx_nstableview
    > super;
    
public:
    
    TableView()
    {
        PASS;
    }
    
    ~TableView()
    {
        PASS;
    }

};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif