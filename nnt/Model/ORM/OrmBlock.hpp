
# ifndef __NNT_ORM_BLOCK_E0B3BB5E3D3D4520AA704C02773045D3_H_INCLUDED
# define __NNT_ORM_BLOCK_E0B3BB5E3D3D4520AA704C02773045D3_H_INCLUDED

# include "OrmObject.hpp"

NNT_BEGIN_HEADER_ORM

class Field
{
public:
    
    enum FieldType
    {
        FT_Null,
        FT_String,
        FT_Integer,
        FT_Real,
        FT_Blob,
    };
    
    enum FieldFeature
    {
        FF_Null = 0x0,
        FF_AutoIncrement = 0x1,
    };
    
    Field();
    Field(Field const& r);
        
    Field& operator = (Field const& r);    
    Field operator | (Field const& r) const;
    
    core::string name;
    Enum<FieldType> type;
    Enum<FieldFeature> feature;
    uint length, decimals;
    bool nullable, key;
    
};

NNT_BEGIN_NS(type)

class nullable
: public Field
{
public:
    
    nullable();
    
};

class string
: public Field
{
public:
    
    string(uint len = 0, uint dec = 0);
    
};

class integer
: public Field
{
public:
    
    integer(uint len = 0, uint dec = 0, bool autoincr = false);
    
};

class blob
: public Field
{
public:
    
    blob();
    
};

NNT_END_NS

class Fields
{    
public:
    
    uint count() const;
    void clear();
    void add_key(core::string const& name);
    uint count_keys() const;
    Field& at(core::string const& name);
    Field& at(uint idx);
    
    Field& operator [] (core::string const& name);
    Field& operator [] (uint idx);
    
protected:
    
    typedef core::map<core::string, Field> fields_store_type;
    typedef core::vector<Field*> fields_order_type;
    fields_order_type _ofields, _okeys;
    fields_store_type _fields;
    
};

class Variant
{
public:
    
    Variant();
    ~Variant();
    
    template <typename valT>
    Variant& operator = (valT const& r)
    {
        if (var == NULL)
            var = new variant_t;
        *var = r;
        return *this;
    }
    
    template <typename valT>
    operator valT () const
    {
        return (valT)*var;
    }
    
    operator core::string () const
    {
        return core::tostr(*var);
    }
    
    operator core::data () const
    {
        return *var;
    }
    
    bool empty() const;
    operator Field const& () const;
    operator variant_t& ();
    
    Field const* field;
    variant_t* var;
    
};

class Filter
{
public:
    
    enum Operator
    {
        LESS,
        GREATER,
        EQUAL,
        NOTEQUAL,
        LESSEQUAL,
        GREATEREQUAL,
    };
    
    Filter(core::string const& fieldname)
    : field(fieldname)
    {
        PASS;
    }
    
    template <typename T>
    Filter& operator < (T const& val)
    {
        oper = LESS;
        value = val;
        return *this;
    }
    
    template <typename T>
    Filter& operator > (T const& val)
    {
        oper = GREATER;
        value = val;
        return *this;
    }
    
    template <typename T>
    Filter& operator == (T const& val)
    {
        oper = EQUAL;
        value = val;
        return *this;
    }
    
    template <typename T>
    Filter& operator != (T const& val)
    {
        oper = NOTEQUAL;
        value = val;
        return *this;
    }
    
    template <typename T>
    Filter& operator <= (T const& val)
    {
        oper = LESSEQUAL;
        value = val;
        return *this;
    }
    
    template <typename T>
    Filter& operator >= (T const& val)
    {
        oper = GREATEREQUAL;
        value = val;
        return *this;
    }
    
    core::string field;
    Enum<Operator> oper;
    variant_t value;
    
};

class Slice;
class Cube;

class Block
: public RefObject
{
public:
    
    Block();
    ~Block();
    
    Slice* slice;
    Cube* cube;
    
    virtual void begin();
    virtual void commit();
    virtual void rollback();
    
    void add(Filter const&);
    Block& operator << (Filter const&);
    
protected:
    
    typedef core::list<Filter> filters_type;
    filters_type _filters;
    
};

class RBlock
: public Block
{
public:
    
    RBlock();
    ~RBlock();
    
    virtual void clear();
    virtual uint count() const = 0;
    virtual bool one() = 0;
    virtual bool save() = 0;
    virtual bool next() = 0;
    
    //! unique id of block.
    variant_t id;
    
    //! get variant.
    Variant& at(Field const&);
    Variant& at(core::string const&);
    Variant& operator [] (core::string const&);
    
protected:
    
    typedef core::map<Field const*, Variant> variants_store_type;
    variants_store_type _vars;
    
};

NNT_END_HEADER_ORM

# endif
