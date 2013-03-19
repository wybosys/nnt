
# include "Foundation+NNT.h"
# include "MainController.h"
# include "OrmCube.hpp"
# include "OrmSlice.hpp"
# include "OrmSqlite.hpp"

NNTAPP_BEGIN

MainView::MainView()
{
    
}

void MainView::layout_subviews()
{
    
}

MainController::MainController()
{
    
}

class Test
: public orm::RSlice
{
public:
    
    Test()
    {
        name = "Test";
        
        fields["name"] = orm::type::string();
        fields["address"] = orm::type::string() | orm::type::nullable();
        fields["avatar"] = orm::type::blob() | orm::type::nullable();
    }
    
};

void MainController::view_loaded()
{
    orm::SqliteCube cube;
    cube.use(@"test");
    Test slice;
    orm::SqliteBlock block = cube.get(slice);
    if (block.count() == 0)
    {
        block["name"] = "A";
        block["address"] = core::tostr(rand());
        block.save();
        
        block["name"] = "B";
        block["address"] = core::tostr(rand());
        core::data da;
        da.append(0xab00cd);
        block["avatar"] = da;
        block.save();
    }
    else
    {
        block << (orm::Filter("_id") > 1);
        while (block.next())
        {
            core::string str = block["address"];
            core::data da = block["avatar"];
            trace_msg(core::type_cast<ns::String>(str));
            trace_int(TRIEXP(da.empty(), 0, (int)da));
        }
    }
    
}

NNTAPP_END
