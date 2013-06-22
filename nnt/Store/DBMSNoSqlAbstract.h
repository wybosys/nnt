
# ifndef __DBMS_NOSQLABSTRACT_D5C2453B06C94621B1B5D7828F7F0165_H_INCLUDED
# define __DBMS_NOSQLABSTRACT_D5C2453B06C94621B1B5D7828F7F0165_H_INCLUDED

# ifdef NNT_OBJC

# import "./DBMS.h"

NNT_BEGIN_HEADER_OBJC

@protocol DBMSNoSqlAbstract <IDBMS>

//! put data and key.
- (BOOL)put:(NSData*)data key:(NSData*)key;

//! put data and key use raw memory.
- (BOOL)put_raw:(void*)data dlen:(uint)dlen key:(void*)key klen:(uint)klen;

//! over data at key.
- (BOOL)over:(NSData*)data key:(NSData*)key;

//! over data and key use raw memory.
- (BOOL)over_raw:(void*)data dlen:(uint)dlen key:(void*)key klen:(uint)klen;

//! get data of key.
- (NSArray*)get:(NSData*)key;

//! get data of key use raw memory.
- (NSArray*)get_raw:(void*)key len:(uint)len;

//! get first data of key. return len of loaded data.
- (uint)get:(void*)key klen:(uint)klen data:(void*)data dlen:(uint)dlen;
- (bool)get:(void*)key klen:(uint)klen pdata:(void**)data pdlen:(uint*)pdlen;

//! remove data.
- (BOOL)remove:(void*)key klen:(uint)klen;
- (BOOL)remove:(NSData*)da;

//! walk all key value. if the function return false, the walk will break.
typedef bool (*DBMSNoSqlWalkFunc)(void* key, uint klen, void* data, uint dlen);
- (void)walk:(DBMSNoSqlWalkFunc)func;

//! sync to pers.
- (void)sync;

//! iterator.
- (void*)iterator_begin;
- (void*)iterator_next:(void*)iter;
- (void)iterator_end:(void*)iter;
- (void)iterator_retrive:(void*)iter key:(void**)key klen:(uint*)klen data:(void**)data dlen:(uint*)dlen; 

@end

@interface DBMSNoSqlAbstract : NSObject <DBMSNoSqlAbstract> {
    
}

@end

@interface DBMSNoSqlUrlAbstract : DBMSNoSqlAbstract <IDBMSUrl> {
    
}

- (id)initWith:(NSString*)path type:(NNTDirectoryType)type;

@end

NNT_END_HEADER_OBJC

# endif

# ifdef NNT_CXX

# include "./DBMS.h"

NNT_BEGIN_HEADER_CXX 
NNT_BEGIN_NS(store)

class DBMSNoSqlAbstract
: public IDBMS
{
public:
    
    //! put data and key.
    virtual bool put(core::data const& data, core::data const& key) = 0;
    
    //! put data and key use raw memory.
    virtual bool put(void* data, uint dlen, void* key, uint klen) = 0;
    
    //! over data at key.
    virtual bool over(core::data const& data, core::data const& key) = 0;
    
    //! over data and key use raw memory.
    virtual bool over(void* data, uint dlen, void* key, uint klen) = 0;
    
    //! remove key.
    virtual bool del(core::data const& key) = 0;
    virtual bool del(void* key, uint klen) = 0;
    
    //! get first data of key. return len of loaded data.
    virtual bool get(void* key, uint klen, void** data, uint* pdlen) = 0;
    virtual bool get(core::data const& key, core::data& data) = 0;
    
    //! walk all key value. if the function return false, the walk will break.
    typedef bool (*DBMSNoSqlWalkFunc)(void* key, uint klen, void* data, uint dlen);
    virtual void walk(DBMSNoSqlWalkFunc func) = 0;
    
    //! sync to pers.
    virtual void sync() = 0;
    
    //! iterator.
    virtual void* iterator_begin() = 0;
    virtual void* iterator_next(void* iter) = 0;
    virtual void iterator_end(void* iter) = 0;
    virtual void iterator_retrive(void* iter, void** key, uint* klen, void** data, uint* dlen) = 0; 
        
    // impl
    virtual core::string urlize(connection_info const&) const;
};

typedef DBMSNoSqlAbstract::DBMSNoSqlWalkFunc DBMSNoSqlWalkFunc;

inline_impl core::string DBMSNoSqlAbstract::urlize(connection_info const& info) const
{
    return info.url;
}

NNT_END_NS 
NNT_END_HEADER_CXX

# endif

# endif
