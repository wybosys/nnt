
# ifndef __WAE_SAPI_ALL_361322E114BC45D2B65A15700AB8F574_H_INCLUDED
# define __WAE_SAPI_ALL_361322E114BC45D2B65A15700AB8F574_H_INCLUDED

# include "WaeController.h"

WAE_BEGIN_NS2(guide, sapi)

class AllCell
: public ui::TableCell<AllCell>
{
public:
    
    AllCell();
    void update();
    void selected();
    
};

class AllTable
: public ui::PlainTable<AllTable, AllCell>
{

};

class MethodCell
: public ui::TableCell<MethodCell>
{
public:
    
    void update();
    void selected();
    
protected:
    
    void mdl_doc(AnyObject&);
    
};

class MethodTable
: public ui::PlainTable<MethodTable, MethodCell>
{
public:
    
    MethodTable();
    void view_loaded();
    void* cls;
    
};

class AllView
: public ui::View<AllView>
{
public:
    
    AllView();
    void layout_subviews();
    
    AllTable tbl_all;

};

class AllController
: public ui::Controller<AllController, AllView>,
public IWorkController
{
public:
    
    AllController();
    void view_loaded();
    void refresh();
    
protected:
    
    void mdl_all(AnyObject&);
    
};

WAE_END_NS2

# endif
