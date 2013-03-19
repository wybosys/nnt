
# include "WSIFoundation.h"
# include "MainController.h"

WSIAPP_BEGIN

void SearchCell::update()
{
    ns::String str = (id)object();
    text().set_text(str);
}

void SearchCell::selected()
{
    /*
    SearchTable* table = dynamic_cast<SearchTable*>(owner());
    typedef ui::Controllerize<ui::TextField> textfield_type;
    textfield_type* ctlr = textfield_type::New();
    ctlr->control().set_text((id)object());
    table->navigation().push(ctlr);
    ctlr->Release();
     */
    
    core::Msgbox::info((id)object());
    
    SearchDisplayer* displayer = (SearchDisplayer*)SearchDisplayer::From(owner());
    displayer->set_active(false);
}

::wsi::Object* SearchTable::makecell(IndexPath const& ip) const
{
    return new SearchCell;
}

bool SearchDisplayer::searchByString(ns::String const& str)
{
    table().clear();
    
    // datas.
    ns::MutableArray arr, result;
    arr << @"ABC" << @"A12" << @"B33" << @"CFSF" << @"XQSDF" << @"PPPOJ" << @"7099780" << @"9009878";
    for (NSString* each in arr())
    {
        ns::String data(each);
        if (data.contain(str))
            result << each;
    }
    
    // sec.
    if (result.size())
    {
        ui::TableSection* sec = new ui::TableSection;
        table().add(sec);
        sec->drop();
        
        for (NSString* each in result())
        {
            sec->add(each);
        }
    }
    
    return true;
}

MainView::MainView()
{
    dock.set_background(ui::Color::Orange());
    
    searchctlr.set_according(dock);
    
    add_sub(searchctlr.searchbar());
    add_sub(dock);
}

void MainView::layout_subviews()
{
    CGRectLayoutVBox lyt(bounds());
    CGRectLayoutLinear lnr(lyt);
    lnr << (pixel)50 << (flex)1 << (flex)1;
    
    searchctlr.searchbar().set_frame(lyt << lnr);
    dock.set_frame(lyt << lnr);
}

MainController::MainController()
{

}

void MainController::view_loaded()
{

}

WSIAPP_END
