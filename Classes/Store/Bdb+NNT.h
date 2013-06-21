
# ifndef __NNT_STORE_BDB_6931173E025148F28BC3D31442FCEC52_H_INCLUDED
# define __NNT_STORE_BDB_6931173E025148F28BC3D31442FCEC52_H_INCLUDED

# ifdef NNT_OBJC

# import "DBMSNoSqlAbstract.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(NNTBdb);

@interface NNTBdb : DBMSNoSqlUrlAbstract {    
    NNTDECL_PRIVATE(NNTBdb);
    
    //! if readonly. default is NO.
    BOOL _readonly;
    
    //! if support dup. default is NO.
    BOOL _dup;
    
    //! db's name.
    NSString* _name;
    
}

@property (nonatomic, assign) BOOL readonly;
@property (nonatomic, assign) BOOL dup;
@property (nonatomic, copy) NSString* name;

//! clear.
- (void)clear;

@end

NNT_END_HEADER_OBJC

# endif

# ifdef NNT_CXX

# include "DBMSNoSqlAbstract.h"

NNT_BEGIN_HEADER_CXX 
NNT_BEGIN_NS(store)

NNTDECL_PRIVATE_HEAD_CXX(Bdb);

class Bdb
: public DBMSNoSqlAbstract
{
    NNTDECL_NOCOPY(Bdb);
    NNTDECL_PRIVATE_CXX(Bdb);
    
public:
    
    NNTDECL_DBMS_DRIVER;
    
    Bdb();
    virtual ~Bdb();
    
    //! delete database.
    virtual bool delete_db();
    
    // override.
    virtual bool connect(connection_info const&);
    virtual void close();
    virtual bool put(core::data const& data, core::data const& key);    
    virtual bool put(void* data, uint dlen, void* key, uint klen);
    virtual bool over(core::data const& data, core::data const& key);
    virtual bool over(void* data, uint dlen, void* key, uint klen);
    virtual bool del(core::data const& key);
    virtual bool del(void* key, uint klen);
    virtual bool get(void* key, uint klen, void** data, uint* pdlen);
    virtual bool get(core::data const& key, core::data& data);
    virtual void walk(DBMSNoSqlWalkFunc func);
    virtual void sync();
    virtual void* iterator_begin();
    virtual void* iterator_next(void* iter);
    virtual void iterator_end(void* iter);
    virtual void iterator_retrive(void* iter, void** key, uint* klen, void** data, uint* dlen);

    //! clear.
    void clear();
    
    //! multi records.
    void* range_begin(void* key, uint klen);
    void* range_next(void* iter);
    
public:
    
    typedef bool (*BDBWalkFunc)(void* key, void* data, void* cursor);
    void _walk(BDBWalkFunc);
    
    //! readonly, default is false.
    bool readonly;
    
    //! dup mode, default is false.
    bool dup;
    
};

NNT_BEGIN_NS(test)

class Bdb
: public ut::Case
{
public:
    
    Bdb() : ut::Case("BDB") {}
    
    virtual bool prepare();
    virtual void collect();
    virtual bool run();
    
protected:
    
    store::Bdb* _db;
    
};

NNT_END_NS

NNT_END_NS 
NNT_END_HEADER_CXX

NNT_BEGIN_HEADER_C

NNTAPI(NNT_TYPE(store::test::Bdb*)) UTBdb();

NNT_END_HEADER_C

# endif

# endif