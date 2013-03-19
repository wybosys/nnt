
# include "Core.h"
# include "OrmBlock.hpp"
# include "OrmSlice.hpp"

NNT_BEGIN_ORM

Field::Field()
:type(FT_Null),
feature(FF_Null),
length(0),
decimals(0),
nullable(false),
key(false)
{
    PASS;
}

Field::Field(Field const& r)
{
    *this = r;
}

Field& Field::operator = (Field const& r)
{
    type = r.type;
    feature = r.feature;
    length = r.length;
    decimals = r.decimals;
    nullable = r.nullable;
    key = r.key;
    if (!r.name.empty())
        name = r.name;
    return *this;
}

Field Field::operator | (Field const& r) const
{
    Field ret = *this;
    if (r.type)
        ret.type = r.type;
    ret.feature |= r.feature;
    ret.nullable |= r.nullable;
    ret.key |= r.key;
    return ret;
}

NNT_BEGIN_NS(type)

nullable::nullable()
{
    Field::nullable = true;
}

string::string(uint len, uint dec)
{
    type = FT_String;
    length = len;
    decimals = dec;
}

integer::integer(uint len, uint dec, bool autoincr)
{
    type = FT_Integer;
    length = len;
    decimals = dec;
    if (autoincr)
        feature = FF_AutoIncrement;
}

blob::blob()
{
    type = FT_Blob;
}

NNT_END_NS

Field& Fields::at(core::string const& name)
{
    fields_store_type::iterator found = _fields.find(name);
    if (found != _fields.end())
        return found->second;
    
    // add map.
    Field fd;
    fd.name = name;
    Field& ret = _fields.insert(core::make_pair(name, fd)).first->second;
    
    // add order.
    _ofields.push_back(&ret);
    
    return ret;
}

Field& Fields::at(uint idx)
{
    return *_ofields[idx];
}

Field& Fields::operator [] (core::string const& name)
{
    return at(name);
}

Field& Fields::operator [] (uint idx)
{
    return at(idx);
}

uint Fields::count() const
{
    return _ofields.size();
}

uint Fields::count_keys() const
{
    return _okeys.size();
}

void Fields::add_key(core::string const& name)
{
    fields_store_type::iterator found = _fields.find(name);
    if (found == _fields.end())
        return;
    Field& fd = found->second;
    if (fd.key)
        return;
    fd.key = true;
    _okeys.push_back(&fd);
}

void Fields::clear()
{
    _ofields.clear();
    _okeys.clear();
    _fields.clear();
}

Block::Block()
: slice(NULL),
cube(NULL)
{
    
}

Block::~Block()
{

}

void Block::begin()
{
    
}

void Block::commit()
{
    
}

void Block::rollback()
{
    
}

void Block::add(Filter const& filter)
{
    _filters.push_back(filter);
}

Block& Block::operator << (Filter const& filter)
{
    add(filter);
    return *this;
}

Variant::Variant()
: field(NULL), var(NULL)
{
    
}

Variant::~Variant()
{
    safe_delete(var);
}

bool Variant::empty() const
{
    return var == NULL;
}

Variant::operator Field const& () const
{
    return *field;
}

Variant::operator variant_t& ()
{
    return *var;
}

RBlock::RBlock()
{
    
}

RBlock::~RBlock()
{
    
}

void RBlock::clear()
{
    _vars.clear();
}

Variant& RBlock::at(Field const& fd)
{
    variants_store_type::iterator found = _vars.find(&fd);
    if (found != _vars.end())
        return found->second;
    return _vars[&fd];
}

Variant& RBlock::at(core::string const& name)
{
    use<RSlice> slice = this->slice;
    Field const& fd = slice->fields.at(name);
    return at(fd);
}

Variant& RBlock::operator [] (core::string const& name)
{
    return at(name);
}

NNT_END_ORM
