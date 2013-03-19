
# include "Core.h"
# include "OrmSqlite.hpp"
# include "NNTSqlite.h"
# include <sqlite/sqlite3.h>

NNT_BEGIN_ORM

class Sqlite
{
public:
    
    static bool is_primarykey(Field const& fd, Fields const& fds)
    {
        return fd.key && (fds.count_keys() == 1);
    }
    
    static bool is_integer(Field const& tp)
    {
        bool ret = false;
        switch (tp.type)
        {
            case Field::FT_Integer: ret = true; break;
            default: ret = false; break;
        }
        return ret;
    }
    
    static bool is_text(Field const& tp)
    {
        bool ret = false;
        switch (tp.type)
        {
            case Field::FT_String: ret = true; break;
            default: ret = false; break;
        }
        return ret;
    }
    
    static bool is_real(Field const& tp)
    {
        bool ret = false;
        switch (tp.type)
        {
            case Field::FT_Real: ret = true; break;
            default: ret = false; break;
        }
        return ret;
    }
    
    static bool is_blob(Field const& tp)
    {
        bool ret = false;
        switch (tp.type)
        {
            case Field::FT_Blob: ret = true; break;
            default: ret = false; break;
        }
        return ret;
    }

    
};

NNTDECL_PRIVATE_BEGIN_CXX(SqliteCube)

friend class SqliteBlock;
friend class SqliteTranscation;

void init()
{
    cnt.creatable = true;
    cnt.readonly = false;
}

void dealloc()
{
    PASS;
}

sqlite3* db() const
{
    return (sqlite3*)cnt.origin();
}

store::Sqlite cnt;

NNTDECL_PRIVATE_END_CXX

SqliteCube::SqliteCube()
{
    NNTDECL_PRIVATE_CONSTRUCT(SqliteCube);
}

SqliteCube::~SqliteCube()
{
    NNTDECL_PRIVATE_DESTROY();
}

bool SqliteCube::use(core::string const& file)
{    
    store::connection_info cnt;
    cnt.url = file;
    return d_ptr->cnt.connect(cnt);
}

SqliteBlock SqliteCube::get(RSlice& sl)
{
    sqlite3* db = d_ptr->db();
    
    bool table_exist = false;
    // check table is exist.
    sqlite3_stmt* stmt = NULL;
    sqlite3_prepare(db, "select count(*) from sqlite_master where type = \"table\" and name = ?", -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, sl.name.c_str(), -1, NULL);
    sqlite3_step(stmt);
    table_exist = sqlite3_column_int(stmt, 0) > 0;
    sqlite3_finalize(stmt);

    // create table.
    if (!table_exist)
    {
        core::string sql = "create table \"" + sl.name + "\" (";
        core::vector<core::string> fields;
        for (uint i = 0; i < sl.fields.count(); ++i)
        {
            Field& fd = sl.fields[i];
            core::string str = "\"" + fd.name + "\" ";
            if (Sqlite::is_integer(fd))
                str += "integer";
            else if (Sqlite::is_real(fd))
                str += "real";
            else if (Sqlite::is_text(fd))
                str += "text";
            else if (Sqlite::is_blob(fd))
                str += "blob";
            if (fd.length != 0)
                str += "(" + core::tostr(fd.length) + "," + core::tostr(fd.decimals) + ") ";
            else
                str += " ";
            if (!fd.nullable)
                str += "not null ";
            if (Sqlite::is_primarykey(fd, sl.fields))
            {
                str += "primary key ";
                if (fd.feature.mark(Field::FF_AutoIncrement) && Sqlite::is_integer(fd))
                    str += "autoincrement ";
            }
            fields.push_back(str);
        }
        sql += core::combine<core::string>(fields, ",");
        sql += ")";
        sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
    }
    
    SqliteBlock ret;
    ret.slice = &sl;
    ret.cube = this;
    return ret;
}

SqliteBlock::SqliteBlock()
: _stmt(NULL)
{

}

SqliteBlock::~SqliteBlock()
{
    _reset();
}

void SqliteBlock::begin()
{
    use<SqliteCube> cube = this->cube;
    sqlite3* db = cube->d_ptr->db();
    sqlite3_exec(db, "begin transaction", NULL, NULL, NULL);
}

void SqliteBlock::commit()
{
    use<SqliteCube> cube = this->cube;
    sqlite3* db = cube->d_ptr->db();
    sqlite3_exec(db, "commit", NULL, NULL, NULL);
}

void SqliteBlock::rollback()
{
    use<SqliteCube> cube = this->cube;
    sqlite3* db = cube->d_ptr->db();
    sqlite3_exec(db, "rollback", NULL, NULL, NULL);
}

core::string SqliteBlock::_condition() const
{
    core::string sql;
    if (_filters.size())
    {
        sql += " where ";
        core::vector<core::string> values;
        for (core::counter<filters_type::const_iterator> iter = _filters.begin();
             iter != _filters.end();
             ++iter)
        {
            core::string sql = iter->field;
            switch (iter->oper)
            {
                case Filter::LESS: sql += "<"; break;
                case Filter::GREATER: sql += ">"; break;
                case Filter::EQUAL: sql += "="; break;
                case Filter::NOTEQUAL: sql += "<>"; break;
                case Filter::LESSEQUAL: sql += "<="; break;
                case Filter::GREATEREQUAL: sql += ">="; break;
            }
            sql += "$cond" + core::tostr(iter.count);
            values.push_back(sql);
        }
        sql += core::combine<core::string>(values, " and ");
    }
    return sql;
}

void SqliteBlock::_condition(void* _stmt) const
{        
    use<sqlite3_stmt> stmt = _stmt;
    use<RSlice> slice = this->slice;
    for (core::counter<filters_type::const_iterator> iter = _filters.begin();
         iter != _filters.end();
         ++iter)
    {
        core::string cond = "$cond" + core::tostr(iter.count);
        int const pos = sqlite3_bind_parameter_index(stmt, cond.c_str());
        Field const& fd = slice->fields.at(iter->field);
        if (Sqlite::is_integer(fd))
            sqlite3_bind_int(stmt, pos, iter->value);
        else if (Sqlite::is_real(fd))
            sqlite3_bind_double(stmt, pos, iter->value);
        else if (Sqlite::is_text(fd))
            sqlite3_bind_text(stmt, pos, iter->value, iter->value.size(), NULL);
        else if (Sqlite::is_blob(fd))
            sqlite3_bind_blob(stmt, pos, iter->value, iter->value.size(), NULL);
    }
}

uint SqliteBlock::count() const
{
    use<SqliteCube> cube = this->cube;
    use<RSlice> slice = this->slice;
    sqlite3* db = cube->d_ptr->db();
    sqlite3_stmt* stmt = NULL;
    core::string sql = "select count(*) from " + slice->name + _condition();
    sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL);
    _condition(stmt);
    sqlite3_step(stmt);
    uint cnt = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return cnt;
}

void SqliteBlock::_reset()
{
    if (_stmt)
    {
        sqlite3_finalize((sqlite3_stmt*)_stmt);
        _stmt = NULL;
    }
}

bool SqliteBlock::one()
{
    _reset();
    
    use<SqliteCube> cube = this->cube;
    use<RSlice> slice = this->slice;
    sqlite3* db = cube->d_ptr->db();
    core::string sql = "select * from " + slice->name + _condition();
    sqlite3_stmt* stmt = NULL;
    sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL);
    _condition(stmt);
    if (sqlite3_step(stmt) != SQLITE_ROW)
    {
        sqlite3_finalize(stmt);
        return false;
    }
    
    id = sqlite3_column_int(stmt, 0);
    for (uint i = 1; i < slice->fields.count(); ++i)
    {
        Field const& fd = slice->fields[i];
        if (Sqlite::is_integer(fd))
            at(fd) = sqlite3_column_int(stmt, i);
        else if (Sqlite::is_real(fd))
            at(fd) = sqlite3_column_double(stmt, i);
        else if (Sqlite::is_text(fd))
            at(fd) = sqlite3_column_text(stmt, i);
        else if (Sqlite::is_blob(fd))
        {
            void const* da = sqlite3_column_blob(stmt, i);
            uint const len = sqlite3_column_bytes(stmt, i);
            at(fd) = core::data((byte*)da, len, core::assign);
        }
    }
    
    _stmt = stmt;
    return true;
}

bool SqliteBlock::next()
{
    use<sqlite3_stmt> stmt = _stmt;
    if (stmt == NULL)
        return one();

    if (sqlite3_step(stmt) != SQLITE_ROW)
    {
        _reset();
        return false;
    }
    
    use<RSlice> slice = this->slice;
    
    id = sqlite3_column_int(stmt, 0);
    for (uint i = 1; i < slice->fields.count(); ++i)
    {
        Field const& fd = slice->fields[i];
        if (Sqlite::is_integer(fd))
            at(fd) = sqlite3_column_int(stmt, i);
        else if (Sqlite::is_real(fd))
            at(fd) = sqlite3_column_double(stmt, i);
        else if (Sqlite::is_text(fd))
            at(fd) = sqlite3_column_text(stmt, i);
        else if (Sqlite::is_blob(fd))
        {
            void const* da = sqlite3_column_blob(stmt, i);
            uint const len = sqlite3_column_bytes(stmt, i);
            at(fd) = core::data((byte*)da, len, core::assign);
        }
    }
    
    return true;
}

bool SqliteBlock::save()
{
    if ((uint)id == 0)
        return _create();
    return _update();
}

bool SqliteBlock::_create()
{
    use<SqliteCube> cube = this->cube;
    use<RSlice> slice = this->slice;
    sqlite3* db = cube->d_ptr->db();
    core::string sql = "insert into " + slice->name + " (";
    core::vector<core::string> labels, values;
    for (variants_store_type::const_iterator iter = _vars.begin();
         iter != _vars.end();
         ++iter)
    {
        labels.push_back(iter->first->name);
        values.push_back("?");
    }
    sql += core::combine<core::string>(labels, ",") + ") values (";
    sql += core::combine<core::string>(values, ",") + ")";
    sqlite3_stmt* stmt = NULL;
    sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL);
    for (core::counter<variants_store_type::const_iterator> iter = _vars.begin();
         iter != _vars.end();
         ++iter)
    {
        int const pos = iter.count + 1;        
        Field const& fd = *iter->first;
        if (Sqlite::is_integer(fd))
            sqlite3_bind_int(stmt, pos, iter->second);
        else if (Sqlite::is_real(fd))
            sqlite3_bind_double(stmt, pos, iter->second);
        else if (Sqlite::is_text(fd))
            sqlite3_bind_text(stmt, pos, iter->second, iter->second.var->size(), NULL);
        else if (Sqlite::is_blob(fd))
            sqlite3_bind_blob(stmt, pos, iter->second, iter->second.var->size(), NULL);
    }
    int sta = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return sta == SQLITE_DONE;
}

bool SqliteBlock::_update()
{
    use<SqliteCube> cube = this->cube;
    use<RSlice> slice = this->slice;
    sqlite3* db = cube->d_ptr->db();
    core::string sql = "update " + slice->name + " set ";
    core::vector<core::string> sets;
    for (variants_store_type::const_iterator iter = _vars.begin();
         iter != _vars.end();
         ++iter)
    {
        core::string sql = iter->first->name + "=?";
        sets.push_back(sql);
    }
    sql += core::combine<core::string>(sets, ",");
    sql += " where _id=" + core::tostr(id);
    sqlite3_stmt* stmt = NULL;
    sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL);
    for (core::counter<variants_store_type::const_iterator> iter = _vars.begin();
         iter != _vars.end();
         ++iter)
    {
        int const pos = iter.count + 1;        
        Field const& fd = *iter->first;
        if (Sqlite::is_integer(fd))
            sqlite3_bind_int(stmt, pos, iter->second);
        else if (Sqlite::is_real(fd))
            sqlite3_bind_double(stmt, pos, iter->second);
        else if (Sqlite::is_text(fd))
            sqlite3_bind_text(stmt, pos, iter->second, iter->second.var->size(), NULL);
        else if (Sqlite::is_blob(fd))
            sqlite3_bind_blob(stmt, pos, iter->second, iter->second.var->size(), NULL);
    }
    int sta = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return sta == SQLITE_DONE;
}

NNT_END_ORM
