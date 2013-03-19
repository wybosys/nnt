
# ifndef __NNT_PARSER_CHMPARSER_393D2ECF534C43828C3A9C11C3E6FE69_H_INCLUDED
# define __NNT_PARSER_CHMPARSER_393D2ECF534C43828C3A9C11C3E6FE69_H_INCLUDED

NNT_BEGIN_HEADER_C

# define CHM_ITSF_V2_LEN  (0x58)
# define CHM_ITSF_V3_LEN  (0x60)
# define CHM_MAX_PATHLEN  (512)
# define CHM_ITSP_V1_LEN  (0x54)
# define CHM_RESOLVE_SUCCESS (0)
# define CHM_RESOLVE_FAILURE (1)
# define CHM_UNCOMPRESSED (0)
# define CHM_COMPRESSED   (1)
# define CHM_LZXC_RESETTABLE_V1_LEN (0x28)
# define CHM_PARAM_MAX_BLOCKS_CACHED 0
# define CHM_MAX_BLOCKS_CACHED 5
# define CHM_LZXC_MIN_LEN (0x18)
# define CHM_LZXC_V2_LEN (0x1c)
# define CHM_PMGL_LEN (0x14)
# define CHM_PMGI_LEN (0x08)
# define CHM_ENUMERATE_NORMAL    (1)
# define CHM_ENUMERATE_META      (2)
# define CHM_ENUMERATE_SPECIAL   (4)
# define CHM_ENUMERATE_FILES     (8)
# define CHM_ENUMERATE_DIRS      (16)
# define CHM_ENUMERATE_ALL       (31)
# define CHM_ENUMERATOR_FAILURE  (0)
# define CHM_ENUMERATOR_CONTINUE (1)
# define CHM_ENUMERATOR_SUCCESS  (2)

typedef struct _chm_itsf
{
    byte        signature[4];           /*  0 (ITSF) */
    dword       version;                /*  4 */
    dword       header_len;             /*  8 */
    dword       unknown_000c;           /*  c */
    udword      last_modified;          /* 10 */
    udword      lang_id;                /* 14 */
    byte        dir_uuid[16];           /* 18 */
    byte        stream_uuid[16];        /* 28 */
    uqword       unknown_offset;         /* 38 */
    uqword       unknown_len;            /* 40 */
    uqword       dir_offset;             /* 48 */
    uqword       dir_len;                /* 50 */
    uqword       data_offset;            /* 58 (Not present before V3) */
} chm_header_itsf;

typedef struct _chm_itsp
{
    byte        signature[4];           /*  0 (ITSP) */
    dword       version;                /*  4 */
    dword       header_len;             /*  8 */
    dword       unknown_000c;           /*  c */
    udword      block_len;              /* 10 */
    dword       blockidx_intvl;         /* 14 */
    dword       index_depth;            /* 18 */
    dword       index_root;             /* 1c */
    dword       index_head;             /* 20 */
    dword       unknown_0024;           /* 24 */
    udword      num_blocks;             /* 28 */
    dword       unknown_002c;           /* 2c */
    udword       lang_id;                /* 30 */
    byte        system_uuid[16];        /* 34 */
    byte        unknown_0044[16];       /* 44 */
} chm_header_itsp;

typedef struct _chm_unitinfo {
    uqword             start;
    uqword             length;
    int                space;
    int                flags;
    char               path[CHM_MAX_PATHLEN+1];
} chm_unitinfo;

typedef struct _chm_lzxc_ctldata {
    udword      size;                   /*  0        */
    byte        signature[4];           /*  4 (LZXC) */
    udword      version;                /*  8        */
    udword      resetInterval;          /*  c        */
    udword      windowSize;             /* 10        */
    udword      windowsPerReset;        /* 14        */
    udword      unknown_18;             /* 18        */
} chm_lzxc_ctldata;

typedef struct _chm_lzxc_resettable {
    udword      version;
    udword      block_count;
    udword      unknown;
    udword      table_offset;
    uqword      uncompressed_len;
    uqword      compressed_len;
    uqword      block_len;
} chm_lzxc_resettable;

typedef struct _chm_header_pmgl {
    char        signature[4];           /*  0 (PMGL) */
    udword      free_space;             /*  4 */
    udword      unknown_0008;           /*  8 */
    dword       block_prev;             /*  c */
    dword       block_next;             /* 10 */
} chm_header_pmgl;

typedef struct _chm_header_pmgi {
    char        signature[4];           /*  0 (PMGI) */
    udword      free_space;             /*  4 */
} chm_header_pmgi;

typedef struct _chm_t {
    
    chm_header_itsf itsf;
    chm_header_itsp itsp;
    
    uqword              dir_offset;
    uqword              dir_len;
    uqword              data_offset;
    dword               index_root;
    dword               index_head;
    dword               block_len;
    
    uqword              span;
    chm_unitinfo        rt_unit;
    chm_unitinfo        cn_unit;
    chm_lzxc_resettable reset_table;
    
    /* LZX control data */
    int                 compression_enabled;
    udword              window_size;
    udword              reset_interval;
    udword              reset_blkcount;
    
    /* decompressor state */
    struct LZXstate     *lzx_state;
    int                 lzx_last_block;
    
    /* cache for decompressed blocks */
    byte                **cache_blocks;
    uqword              *cache_block_indices;
    dword               cache_num_blocks;
    
    // file desc.
    FILE *fd;
    
} chm_t;

typedef int (*CHM_ENUMERATOR)(chm_t *chm,
                              chm_unitinfo *ui,
                              void *context);

extern bool chm_read(chm_t*, FILE*);
extern void chm_init(chm_t*);
extern void chm_free(chm_t*);
extern bool chm_enumerate(chm_t*, int what, CHM_ENUMERATOR e, void *context);
extern bool chm_enumerate_dir(chm_t*, const char *prefix, int what, CHM_ENUMERATOR e, void *context);
extern qword chm_retrieve_object(chm_t *chm, chm_unitinfo *ui, unsigned char *buf, uqword addr, qword len);

NNT_END_HEADER_C

# endif