
# ifndef __NNT_ORM_CUBE_SQLITE_64BCBC26C5E14F61B44522B25F91F548_H_INCLUDED
# define __NNT_ORM_CUBE_SQLITE_64BCBC26C5E14F61B44522B25F91F548_H_INCLUDED

# include "OrmCube.hpp"
# include "OrmSlice.hpp"
# include "OrmBlock.hpp"

NNT_BEGIN_HEADER_ORM

class SqliteBlock
: public RBlock
{
public:
    
    SqliteBlock();
    ~SqliteBlock();
    
    virtual void begin();
    virtual void commit();
    virtual void rollback();
    
    virtual uint count() const;
    virtual bool one();
    virtual bool save();
    virtual bool next();
    
protected:
    
    void _reset();
    bool _create();
    bool _update();
    
    core::string _condition() const;
    void _condition(void*) const;
    
    void* _stmt;
    
};

NNTDECL_PRIVATE_HEAD_CXX(SqliteCube);

class SqliteCube
: public SqlCube
{
    NNTDECL_PRIVATE_CXX(SqliteCube);
    
public:
    
    SqliteCube();
    ~SqliteCube();
    
    // use a db.
    OBJCEXPRESS(bool use(ns::String const&));
    bool use(core::string const&);
    
    // get slice.
    SqliteBlock get(RSlice&);
    
    friend class SqliteBlock;
    friend class SqliteTranscation;
};

NNT_END_HEADER_ORM

# endif
