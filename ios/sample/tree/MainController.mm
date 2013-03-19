
# include "WSIFoundation.h"
# include "MainController.h"
# include "AlphabetFlow.h"

WSIAPP_BEGIN

Cell::Cell()
{    
    set_background(cg::Gradient(cg::Color::White(), cg::Color::Orange(), 0, 4, M_PI_2));
}

void Cell::layout_subviews()
{
 
}

void Cell::update()
{
    core::string var = (char const*)object();
    this->text().set_text(var);
}

GroupCell::GroupCell()
{
    set_background(cg::Gradient(cg::Color::White(), cg::Color::Black(), 0, 4, M_PI_2));
}

void GroupCell::layout_subviews()
{
    super::layout_subviews();
}

void GroupCell::update()
{
    super::update();
    
    core::string var = (char const*)object();
    this->text().set_text(var);
}

void GroupCell::did_expanded()
{
    set_accessory(UITableViewCellAccessoryCheckmark);
}

void GroupCell::did_collapsed()
{
    set_accessory(UITableViewCellAccessoryDisclosureIndicator);
}

Table::Table()
{
    
}

Table::cell_type Table::makecell(IndexPath const& idx) const
{
    return new Cell;
}

Table::cell_type Table::makegroupcell(IndexPath const& idx) const
{
    return new GroupCell;
}

MainView::MainView()
{
    add_sub(tree);
}

void MainView::layout_subviews()
{
    tree.view().set_frame(bounds());
}

MainController::MainController()
{

}

void MainController::view_loaded()
{
    ::wsi::AlphabetFlow af;
    
    Table& tree = view().tree;
    
    ui::TableTreeSection* sec = new ui::TableTreeSection;
    sec->header = "EXPAND A";
    tree.add(sec);
    sec->drop();
    
    // insert data.
    for (uint i = 0; i < 3; ++i)
    {
        sec->add(af.next());
        
        ui::TableTreeSection* item = &sec->item_at(sec->count() - 1);
        for (uint i = 0; i < 4; ++i)
        {
            item->add(af.next());
            
            if (1)
            {
                ui::TableTreeSection* subitem = &item->item_at(item->count() - 1);
                for (uint i = 0; i < 3; ++i)
                    subitem->add(af.next());
            }
        }
    }
    
    sec = new ui::TableTreeSection;
    sec->header = "EXPAND B";
    tree.add(sec);
    sec->drop();
    
    // insert data.
    for (uint i = 0; i < 3; ++i)
    {
        sec->add(af.next());
    }
}

WSIAPP_END