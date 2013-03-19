
# ifndef __WSI_STORE_BDB_6931173E025148F28BC3D31442FCEC52_H_INCLUDED
# define __WSI_STORE_BDB_6931173E025148F28BC3D31442FCEC52_H_INCLUDED

# ifdef WSI_OBJC

# import "DBMSNoSqlAbstract.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(WSIBdb);

@interface WSIBdb : DBMSNoSqlUrlAbstract {    
    WSIDECL_PRIVATE(WSIBdb);
    
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

WSI_END_HEADER_OBJC

# endif

# ifdef WSI_CXX

# include "DBMSNoSqlAbstract.h"

WSI_BEGIN_HEADER_CXX 
WSI_BEGIN_NS(store)

WSIDECL_PRIVATE_HEAD_CXX(Bdb);

class Bdb
: public DBMSNoSqlAbstract
{
    WSIDECL_NOCOPY(Bdb);
    WSIDECL_PRIVATE_CXX(Bdb);
    
public:
    WSIDECL_DBMS_DRIVER;
    
    Bdb();
    virtual ~Bdb();
    
public:
    
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

WSI_BEGIN_NS(test)

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

WSI_END_NS

WSI_END_NS 
WSI_END_HEADER_CXX

WSI_BEGIN_HEADER_C

WSIAPI(::wsi::store::test::Bdb*) UTBdb();

WSI_END_HEADER_C

# endif

# endif