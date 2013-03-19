
# ifndef __NNTNS_TABLEVIEW_BF92B562F8204EF9A9F32671A485C426_H_INCLUDED
# define __NNTNS_TABLEVIEW_BF92B562F8204EF9A9F32671A485C426_H_INCLUDED

# include "NSControl+NNT.h"
# include "NSScrollView+NNT.h"

NNT_BEGIN_HEADER_OBJC

@interface NNTNSTableView : NSTableView

- (void)deselectSelection;

@end

# ifdef NNT_CXX

@interface _cxx_nstableview : NNTNSTableView <NSTableViewDelegate, NSTableViewDataSource>

@end

# endif

NNT_EXTERN signal_t kSignalSelectChanged;

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX 
NNT_BEGIN_NS(ui)

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

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif