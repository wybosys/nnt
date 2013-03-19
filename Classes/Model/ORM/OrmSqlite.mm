
# include "Core.h"
# include "OrmSqlite.hpp"
# include "Directory+WSI.h"

WSI_BEGIN_ORM

bool SqliteCube::use(ns::String const& name)
{    
    ns::URL url = core::mkdir(@"orm", NSAppVarDirectory);
    url += name + @".sqlt";
    
    return use(core::type_cast<core::string>(url));
}

WSI_END_ORM
