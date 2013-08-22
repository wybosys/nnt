
# ifndef __NNTSQLITE3_D6478779002640D4B7E2DAF025A15447_H_INCLUDED
# define __NNTSQLITE3_D6478779002640D4B7E2DAF025A15447_H_INCLUDED

# ifdef __cplusplus
extern "C" {
# endif
 
// for MacOS native crypto.
extern int sqlite3_ns_key(sqlite3* db, void const* skey, int lkey);
extern int sqlite3_ns_rekey(sqlite3* db, void const* skey, int lkey);
    
# ifdef __cplusplus
}
# endif

# endif
