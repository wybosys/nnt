
# ifndef __DBMS_SQLABSTRACT_E940EFDEB1154BB595084C5FF8C3BC2C_H_INCLUDED
# define __DBMS_SQLABSTRACT_E940EFDEB1154BB595084C5FF8C3BC2C_H_INCLUDED

# ifdef NNT_OBJC

# import "./DBMS.h"

NNT_BEGIN_HEADER_OBJC

@interface DBMSqlParam : NSObject {
    
    //! position, from 0. default is -1.
    NSUInteger pos;
    
    //! value.
    id value;
    
    //! value type.
    NNTValueType type;
    
    //! index name.
    NSString* name;
    
}

@property (nonatomic, assign) NSUInteger pos;
@property (nonatomic, assign) NNTValueType type;
@property (nonatomic, retain) id value;
@property (nonatomic, copy) NSString* name;

+ (id)paramWith:(id)value type:(NNTValueType)type pos:(uint)pos;

@end

@interface DBMSqlDatatable : NSObject {
    NSArray *cols;
    NSArray *rows;
}

@property (nonatomic, retain) NSArray *cols, *rows;

//! find value for key.
- (NSArray*)valueForKey:(NSString *)key;

//! find value for key.
- (id)valueForKey:(NSString *)key row:(uint)row;

//! count.
- (NSUInteger)count;

//! index of key.
- (uindex)indexOfKey:(NSString*)key;

@end

@protocol DBMSqlAbstract <IDBMS>

//! run sql with params.
- (DBMSqlDatatable*)exec:(NSString*)sql params:(NSArray*)param;

@optional

//! run sql.
- (DBMSqlDatatable*)exec:(NSString*)sql;

@end

@interface DBMSqlAbstract : NSObject <DBMSqlAbstract>

@end

@interface DBMSqlUrlAbstract : DBMSqlAbstract <IDBMSUrl>

- (id)initWith:(NSString*)path type:(NNTDirectoryType)type;

@end

NNT_END_HEADER_OBJC

# endif

# ifdef NNT_CXX

# include "./DBMS.h"

NNT_BEGIN_HEADER_CXX 
NNT_BEGIN_NS(store)

NNTDECL_EXTERN_CLASS_CXX(DBMSqlDatatable);

NNTCLASS(DBMSqlAbstract);

class DBMSqlAbstract
: public IDBMS
{
public:
    
    //! simple run sql.
    virtual DBMSqlDatatable* exec(core::string const& sql) = 0;
 
    //! params type,
    typedef core::vector<core::pair<core::string, variant_t> > params_type;
    
    //! run sql with params.
    virtual DBMSqlDatatable* exec(core::string const& sql, params_type const& params) = 0;
        
    // impl.
    virtual core::string urlize(connection_info const&) const;
};

inline_impl core::string DBMSqlAbstract::urlize(connection_info const& info) const
{
    return info.url;
}

NNTCLASS(DBMSqlDatatable);

class DBMSqlDatatable
: public cxx::Object<>
{
public:
    
    DBMSqlDatatable();
    virtual ~DBMSqlDatatable();
    
    typedef core::vector<variant_t const*> cols_type;
    typedef core::vector<variant_t const*> row_type;
    typedef core::vector<row_type const*> rows_type;
    
public:
    
    virtual core::string to_string() const;
    
    //! clear rows.
    void clear_rows();
    
    //! clear all.
    void clear();
    
    //! update.
    virtual void update() { PASS; }
    
    //! rows.
    rows_type const& rows() const
    {
        return this->_rows;
    }
    
    cols_type const& cols() const
    {
        return this->_cols;
    }
    
    DBMSqlDatatable *next, *prev;
    
protected:
    
    cols_type _cols;
    rows_type _rows;
    
    friend class DBMSqlDatatableAttach;
    
};

# ifdef LIBNNT

class DBMSqlDatatableAttach
{
public:
    static DBMSqlDatatable::rows_type& rows(DBMSqlDatatable* dt) { return dt->_rows; }
    static DBMSqlDatatable::cols_type& cols(DBMSqlDatatable* dt) { return dt->_cols; }
};

# endif

typedef DBMSqlDatatable datatable_t;

NNT_BEGIN_NS(ntl)

template <typename nameT>
struct field
{
    typedef nameT type;
};

template <typename fieldT, 
int seqT = ::nnt::ntl::SEQUENCE_VECTOR>
struct table
{
    typedef typename fieldT::type field_value;
    typedef typename ::nnt::ntl::sequence<field_value, seqT>::type fields_type;
    typedef typename ::nnt::ntl::value_type<field_value>::type name_type;
    typedef table<fieldT, seqT> self_type;
    
    self_type& operator [] (field_value& val)
    {
        fields.push_back(val);
        return *this;
    }
    
    self_type& operator [] (field_value const& val)
    {
        fields.push_back(val);
        return *this;
    }
     
    self_type operator [] (field_value& val) const
    {
        self_type tab;
        tab.fields.push_back(val);
        return tab;
    }
    
    self_type operator [] (field_value const& val) const
    {
        self_type tab;
        tab.fields.push_back(val);
        return tab;
    }
    
    self_type& operator () (name_type& nm)
    {
        name = nm;
        return *this;
    }
    
    self_type operator () (name_type& nm) const
    {
        self_type tab;
        tab.name = nm;
        return tab;
    }
    
    self_type operator () (name_type const& nm) const
    {
        self_type tab;
        tab.name = nm;
        return tab;
    }
    
    name_type name;
    fields_type fields;    
};

template <typename sqlT, typename tableExp>
struct sqlexpress
{
    typedef sqlexpress<sqlT, tableExp> self_type;
    
    self_type& operator << (typename tableExp::table_type const& tbl)
    {
        result << tableExp()(tbl);
        return *this;
    }
    
    template <typename T>
    self_type& operator << (T const& r)
    {
        result << r;
        return *this;
    }
    
    sqlT result;
};

NNT_END_NS

typedef store::ntl::field<core::string> field_t;
typedef store::ntl::table<field_t, ::nnt::ntl::SEQUENCE_VECTOR> table_t;

NNT_END_NS 
NNT_END_HEADER_CXX

# endif

# if defined(NNT_CXX) && defined(NNT_OBJC)

NNT_BEGIN_HEADER_CXX 
NNT_BEGIN_NS(store) 
NNT_BEGIN_NS(objc)

typedef store::ntl::field< ::NSString* > field_t;
typedef store::ntl::table<field_t, ::nnt::ntl::SEQUENCE_OBJC_MUTARRAY> table_t;

struct objc_table
{    
    table_t operator [] (table_t::field_value val) const
    {
        table_t tab; tab[val];
        return tab;
    }
    
    table_t operator () (table_t::name_type nm) const
    {
        table_t tab; tab(nm);
        return tab;
    }
};

static const objc_table table_p = objc_table();

NNT_END_NS 
NNT_END_NS 
NNT_END_HEADER_OBJC

# endif

# endif
