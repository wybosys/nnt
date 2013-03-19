
# include "Core.h"
# include "DBMSqlAbstract.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(store)

DBMSqlDatatable::DBMSqlDatatable()
: next(NULL), prev(NULL)
{
    
}

DBMSqlDatatable::~DBMSqlDatatable()
{
    this->clear();
}

core::string DBMSqlDatatable::to_string() const
{
    ::std::stringstream ss;
    
    // print cols.
    for (cols_type::const_iterator each = _cols.begin(); each != _cols.end(); ++each)
        ss << **each << " ";
    ss << std::endl;
    
    // print rows.
    for (rows_type::const_iterator row = _rows.begin(); row != _rows.end(); ++row)
    {
        for (row_type::const_iterator cell = (*row)->begin(); cell != (*row)->end(); ++cell)
            ss << **cell << " ";
        ss << std::endl;
    }
    ss << std::endl;
    
    return ss.str();
}

void DBMSqlDatatable::clear_rows()
{
    for (rows_type::iterator each = this->_rows.begin();
         each != this->_rows.end(); ++each)
    {
        row_type& row = *core::down_const(*each);
        core::clear_destroy(row);
    }
    
    core::clear_destroy(this->_rows);
}

void DBMSqlDatatable::clear()
{
    // clear cols.
    core::clear_destroy(this->_cols);
    
    // clear rows.
    this->clear_rows();
    
    // clear next.
    DBMSqlDatatable* next = this->next;
    while (next)
    {
        DBMSqlDatatable* store = next->next;
        next->drop();
        next = store;
    }
}

NNT_END_NS
NNT_END_CXX
