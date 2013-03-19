
# include "Core.h"
# include "XepField.h"

XMPPXEP_BEGIN

Field::Field()
{
    
}

Field::Field(core::string const& str)
{
    set(str);
}

Field::~Field()
{
    
}

void Field::set(core::string const& str)
{
    core::split(str, ":", path);
}

core::string Field::to_string() const
{
    return core::combine(path, core::string(":"));
}

bool Field::operator == (Field const& r) const
{
    if (path.size() != r.path.size())
        return false;
    return ::std::equal(path.begin(), path.end(), r.path.begin());
}

core::string Field::protocol() const
{
    if (path.size())
        return path.front();
    return core::null_string;
}

core::string Field::data() const
{
    if (path.size() == 0)
        return core::null_string;
    path_type tem = path;
    tem.erase(tem.begin());
    return core::combine(tem, core::string(":"));
}

XMPPXEP_END
