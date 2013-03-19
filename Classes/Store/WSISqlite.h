
# ifndef __DBMS_SQLITE_07002ABECBAE405DA641E9E3074CF666_H_INCLUDED
# define __DBMS_SQLITE_07002ABECBAE405DA641E9E3074CF666_H_INCLUDED

# ifdef NNT_OBJC

# import "./DBMSqlAbstract.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(NNTSqlite);

@interface NNTSqlite : DBMSqlUrlAbstract {    
    NNTDECL_PRIVATE(NNTSqlite);
}

//! run sql query.
- (DBMSqlDatatable*)exec_ansi:(char const *)sql params:(NSArray *)param;
- (DBMSqlDatatable*)exec_ansi:(char const *)sql;
- (DBMSqlDatatable*)exec_ansi:(char const *)sql len:(usize)len params:(NSArray *)param;
- (DBMSqlDatatable*)exec_ansi:(char const *)sql len:(usize)len;

//! exist table.
- (bool)exist_table:(char const*)table;

//! drop table.
- (void)drop_table:(char const*)table;

//! create table.
- (void)create_table:(char const*)table cols:(char const*)cols;

@end

NNT_END_HEADER_OBJC

# endif

# ifdef NNT_CXX

# include "DBMSqlAbstract.h"

NNT_BEGIN_HEADER_CXX 
NNT_BEGIN_NS(store)

NNTDECL_PRIVATE_HEAD_CXX(Sqlite);

class Sqlite
: public DBMSqlAbstract
{
    NNTDECL_NOCOPY(Sqlite);
    NNTDECL_PRIVATE_CXX(Sqlite);
    
public:
    
    NNTDECL_DBMS_DRIVER;
    
    Sqlite();
    ~Sqlite();
    
public:
    
    virtual bool connect(connection_info const&);
    virtual void close();
    
    virtual DBMSqlDatatable* exec(core::string const& sql);    
    virtual DBMSqlDatatable* exec(core::string const& sql, params_type const& params);
    
public:
    
    //! readonly, default is true.
    bool readonly;
    
    //! able to create the database, default is false.
    bool creatable;
    
    //! get origin db.
    void* origin() const;
    
};

class SLDatabase
: public DBMSqlDatatable
{
public:
    
    SLDatabase();
    ~SLDatabase();
    
public:

    void update_cols(uint ncols, char** cols);
    void add_row(uint ncells, char** cells);
    
};

class SLDatabaseSTMT
: public DBMSqlDatatable
{
public:

    SLDatabaseSTMT(void*);
    ~SLDatabaseSTMT();
    
public:
    
    virtual void update();
    
protected:
    
    void* _stmt;
    
};

NNT_BEGIN_NS(sqlite)

template <typename strT, typename tabT>
struct sqlexpress_table
{
    typedef tabT table_type;
    
    strT operator () (table_type const& tbl) const
    {
        strT str;
        typename table_type::fields_type::const_iterator each = tbl.fields.begin();
        while (each != tbl.fields.end())
        {
            str += tbl.name + "." + *each;
            if (++each != tbl.fields.end())
                str += ",";
        }
        return str;
    }
    
};

# ifdef NNT_OBJC

NNT_BEGIN_NS(objc)

using namespace store::objc;

struct sqlexpress_table
{
    typedef objc::table_t table_type;
    
    ns::String operator () (table_type const& tbl) const
    {
        ns::String ret;
        uint const sz = tbl.fields.size();
        uint idx = 0;
        while (idx < sz)
        {
            ret += tbl.name + @"." + (NSString*)tbl.fields[idx];
            if (++idx < sz)
                ret += @",";
        }
        return ret;
    }
    
};

typedef wtl::sqlexpress < ns::String, sqlexpress_table> sqlexpress;

NNT_END_NS

# endif

NNT_END_NS

NNT_END_NS 
NNT_END_HEADER_CXX

# endif

# endif
