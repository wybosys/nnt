
# include "Core.h"
# include "CHMParser.h"
# include "../../3rd/lzx/lzx.h"

WSI_BEGIN_C

qword _chm_fetch_bytes(chm_t* chm, byte *buf, uqword os, qword len);
int _unmarshal_itsf_header(unsigned char **pData, unsigned int *pDataLen, chm_header_itsf* dest);
int _unmarshal_itsp_header(unsigned char **pData, unsigned int *pDataLen, chm_header_itsp* dest);
int chm_resolve_object(chm_t *chm, const char *objPath, chm_unitinfo *ui);
int _unmarshal_lzxc_reset_table(unsigned char **pData, unsigned int *pDataLen, chm_lzxc_resettable *dest);
int _unmarshal_lzxc_control_data(unsigned char **pData, unsigned int *pDataLen, chm_lzxc_ctldata *dest);
void chm_set_param(chm_t* chm, int paramType, int paramVal);

int _unmarshal_char_array(unsigned char **pData, unsigned int *pLenRemain, char *dest, int count);
int _unmarshal_uchar_array(unsigned char **pData, unsigned int *pLenRemain, unsigned char *dest, int count);
int _unmarshal_int32(unsigned char **pData, unsigned int *pLenRemain, dword *dest);
int _unmarshal_uint32(unsigned char **pData, unsigned int *pLenRemain, udword *dest);
int _unmarshal_uuid(unsigned char **pData, unsigned int *pDataLen, unsigned char *dest);
int _unmarshal_uint64(unsigned char **pData, unsigned int *pLenRemain, uqword *dest);
int _unmarshal_int64(unsigned char **pData, unsigned int *pLenRemain, qword*dest);

void _chm_skip_cword(uchar **pEntry);
uqword _chm_parse_cword(uchar **pEntry);

uchar *_chm_find_in_PMGL(uchar *page_buf, udword block_len, const char *objPath);
int _chm_parse_PMGL_entry(uchar **pEntry, chm_unitinfo *ui);
dword _chm_find_in_PMGI(uchar *page_buf, dword block_len, const char *objPath);

qword _chm_decompress_region(chm_t *chm, uchar *buf, uqword start, qword len);
qword _chm_decompress_block(chm_t *h, uqword block, uchar **ubuffer);

int _unmarshal_pmgl_header(unsigned char **pData, unsigned int *pDataLen, chm_header_pmgl *dest);
int _chm_parse_UTF8(uchar **pEntry, uqword count, char *path);
void _chm_skip_PMGL_entry_data(uchar **pEntry);
int _unmarshal_pmgi_header(unsigned char **pData, unsigned int *pDataLen, chm_header_pmgi *dest);
int _chm_get_cmpblock_bounds(chm_t *h, qword block, uqword *start, qword *len);

static const char _CHMU_RESET_TABLE[] =
"::DataSpace/Storage/MSCompressed/Transform/"
"{7FC28940-9D31-11D0-9B27-00A0C91E9C7C}/"
"InstanceData/ResetTable";
static const char _CHMU_LZXC_CONTROLDATA[] =
"::DataSpace/Storage/MSCompressed/ControlData";
static const char _CHMU_CONTENT[] =
"::DataSpace/Storage/MSCompressed/Content";
static const char _CHMU_SPANINFO[] =
"::DataSpace/Storage/MSCompressed/SpanInfo";
static const char _chm_pmgl_marker[4] = "PMGL";
static const char _chm_pmgi_marker[4] = "PMGI";

void chm_init(chm_t* chm) {
    memset(chm, 0, sizeof(chm_t));
}

void chm_free(chm_t* chm) {
}

bool chm_read(chm_t* chm, FILE* fd) {
    if (fseek(fd, 0, SEEK_SET) != 0)
        return false;
    
    unsigned char      sbuffer[256];
    unsigned int       sremain;
    unsigned char      *sbufpos;
    chm_unitinfo       uiLzxc;
    chm_lzxc_ctldata   ctlData;
    
    memset(&uiLzxc, 0, sizeof(uiLzxc));
    memset(&ctlData, 0, sizeof(ctlData));

    chm->fd = fd;
    chm->lzx_state = NULL;
    chm->cache_blocks = NULL;
    chm->cache_block_indices = NULL;
    chm->cache_num_blocks = 0;
    
    /* read and verify header */
    sremain = CHM_ITSF_V3_LEN;
    sbufpos = sbuffer;
    if (_chm_fetch_bytes(chm, sbuffer, (uqword)0, sremain) != sremain    ||
        !_unmarshal_itsf_header(&sbufpos, &sremain, &chm->itsf)) {
        return false;
    }
    
    /* stash important values from header */
    chm->dir_offset  = chm->itsf.dir_offset;
    chm->dir_len     = chm->itsf.dir_len;
    chm->data_offset = chm->itsf.data_offset;
    
    /* now, read and verify the directory header chunk */
    sremain = CHM_ITSP_V1_LEN;
    sbufpos = sbuffer;
    if (_chm_fetch_bytes(chm, sbuffer,
                         (uqword)chm->itsf.dir_offset, sremain) != sremain       ||
        !_unmarshal_itsp_header(&sbufpos, &sremain, &chm->itsp)) {
        return false;
    }
    
    /* grab essential information from ITSP header */
    chm->dir_offset += chm->itsp.header_len;
    chm->dir_len    -= chm->itsp.header_len;
    chm->index_root  = chm->itsp.index_root;
    chm->index_head  = chm->itsp.index_head;
    chm->block_len   = chm->itsp.block_len;
    
    /* if the index root is -1, this means we don't have any PMGI blocks.
     * as a result, we must use the sole PMGL block as the index root
     */
    if (chm->index_root <= -1)
        chm->index_root = chm->index_head;
    
    /* By default, compression is enabled. */
    chm->compression_enabled = 1;
    
    /* prefetch most commonly needed unit infos */
    if (CHM_RESOLVE_SUCCESS != chm_resolve_object(chm,
                                                  _CHMU_RESET_TABLE,
                                                  &chm->rt_unit)    ||
        chm->rt_unit.space == CHM_COMPRESSED                        ||
        CHM_RESOLVE_SUCCESS != chm_resolve_object(chm,
                                                  _CHMU_CONTENT,
                                                  &chm->cn_unit)    ||
        chm->cn_unit.space == CHM_COMPRESSED                        ||
        CHM_RESOLVE_SUCCESS != chm_resolve_object(chm,
                                                  _CHMU_LZXC_CONTROLDATA,
                                                  &uiLzxc)                ||
        uiLzxc.space == CHM_COMPRESSED)
    {
        chm->compression_enabled = 0;
    }
    
    /* read reset table info */
    if (chm->compression_enabled)
    {
        sremain = CHM_LZXC_RESETTABLE_V1_LEN;
        sbufpos = sbuffer;
        if (chm_retrieve_object(chm, &chm->rt_unit, sbuffer,
                                0, sremain) != sremain                        ||
            !_unmarshal_lzxc_reset_table(&sbufpos, &sremain,
                                         &chm->reset_table))
        {
            chm->compression_enabled = 0;
        }
    }
    
    /* read control data */
    if (chm->compression_enabled)
    {
        sremain = (unsigned int)uiLzxc.length;
        if (uiLzxc.length > sizeof(sbuffer))
        {
            return false;
        }
        
        sbufpos = sbuffer;
        if (chm_retrieve_object(chm, &uiLzxc, sbuffer,
                                0, sremain) != sremain                       ||
            !_unmarshal_lzxc_control_data(&sbufpos, &sremain,
                                          &ctlData))
        {
            chm->compression_enabled = 0;
        }
        
        chm->window_size = ctlData.windowSize;
        chm->reset_interval = ctlData.resetInterval;
        
        chm->reset_blkcount = chm->reset_interval    /
        (chm->window_size / 2) *
        ctlData.windowsPerReset;
    }
    
    /* initialize cache */
    chm_set_param(chm, CHM_PARAM_MAX_BLOCKS_CACHED,
                  CHM_MAX_BLOCKS_CACHED);
    
    return true;
}

qword _chm_fetch_bytes(chm_t* chm, byte *buf, uqword os, qword len) {
    qword readLen=0, oldOs=0;
    oldOs = fseek(chm->fd, 0, SEEK_CUR);
    fseek(chm->fd, (long)os, SEEK_SET);
    readLen = fread(buf, 1, len, chm->fd);
    fseek(chm->fd, (long)oldOs, SEEK_SET);
    return readLen;
}

int _unmarshal_itsf_header(unsigned char **pData,
                                  unsigned int *pDataLen,
                                  chm_header_itsf* dest) {
    /* we only know how to deal with the 0x58 and 0x60 byte structures */
    if (*pDataLen != CHM_ITSF_V2_LEN  &&  *pDataLen != CHM_ITSF_V3_LEN)
        return 0;
    
    /* unmarshal common fields */
    _unmarshal_char_array(pData, pDataLen, (char *)dest->signature, 4);
    _unmarshal_int32     (pData, pDataLen, &dest->version);
    _unmarshal_int32     (pData, pDataLen, &dest->header_len);
    _unmarshal_int32     (pData, pDataLen, &dest->unknown_000c);
    _unmarshal_uint32    (pData, pDataLen, &dest->last_modified);
    _unmarshal_uint32    (pData, pDataLen, &dest->lang_id);
    _unmarshal_uuid      (pData, pDataLen,  dest->dir_uuid);
    _unmarshal_uuid      (pData, pDataLen,  dest->stream_uuid);
    _unmarshal_uint64    (pData, pDataLen, &dest->unknown_offset);
    _unmarshal_uint64    (pData, pDataLen, &dest->unknown_len);
    _unmarshal_uint64    (pData, pDataLen, &dest->dir_offset);
    _unmarshal_uint64    (pData, pDataLen, &dest->dir_len);
    
    /* error check the data */
    /* XXX: should also check UUIDs, probably, though with a version 3 file,
     * current MS tools do not seem to use them.
     */
    if (memcmp(dest->signature, "ITSF", 4) != 0)
        return 0;
    if (dest->version == 2)
    {
        if (dest->header_len < CHM_ITSF_V2_LEN)
            return 0;
    }
    else if (dest->version == 3)
    {
        if (dest->header_len < CHM_ITSF_V3_LEN)
            return 0;
    }
    else
        return 0;
    
    /* now, if we have a V3 structure, unmarshal the rest.
     * otherwise, compute it
     */
    if (dest->version == 3)
    {
        if (*pDataLen != 0)
            _unmarshal_uint64(pData, pDataLen, &dest->data_offset);
        else
            return 0;
    }
    else
        dest->data_offset = dest->dir_offset + dest->dir_len;
    
    return 1;
}

int _unmarshal_itsp_header(unsigned char **pData,
                                  unsigned int *pDataLen,
                                  chm_header_itsp *dest) {
    /* we only know how to deal with a 0x54 byte structures */
    if (*pDataLen != CHM_ITSP_V1_LEN)
        return 0;
    
    /* unmarshal fields */
    _unmarshal_char_array(pData, pDataLen, (char*)dest->signature, 4);
    _unmarshal_int32     (pData, pDataLen, &dest->version);
    _unmarshal_int32     (pData, pDataLen, &dest->header_len);
    _unmarshal_int32     (pData, pDataLen, &dest->unknown_000c);
    _unmarshal_uint32    (pData, pDataLen, &dest->block_len);
    _unmarshal_int32     (pData, pDataLen, &dest->blockidx_intvl);
    _unmarshal_int32     (pData, pDataLen, &dest->index_depth);
    _unmarshal_int32     (pData, pDataLen, &dest->index_root);
    _unmarshal_int32     (pData, pDataLen, &dest->index_head);
    _unmarshal_int32     (pData, pDataLen, &dest->unknown_0024);
    _unmarshal_uint32    (pData, pDataLen, &dest->num_blocks);
    _unmarshal_int32     (pData, pDataLen, &dest->unknown_002c);
    _unmarshal_uint32    (pData, pDataLen, &dest->lang_id);
    _unmarshal_uuid      (pData, pDataLen,  dest->system_uuid);
    _unmarshal_uchar_array(pData, pDataLen, dest->unknown_0044, 16);
    
    /* error check the data */
    if (memcmp(dest->signature, "ITSP", 4) != 0)
        return 0;
    if (dest->version != 1)
        return 0;
    if (dest->header_len != CHM_ITSP_V1_LEN)
        return 0;
    
    return 1;
}

int chm_resolve_object(chm_t *chm, const char *objPath, chm_unitinfo *ui) {
    /*
     * XXX: implement caching scheme for dir pages
     */
    
    dword curPage;
    
    /* buffer to hold whatever page we're looking at */
    /* RWE 6/12/2003 */
    uchar *page_buf = malloc(chm->block_len);
    if (page_buf == NULL)
        return CHM_RESOLVE_FAILURE;
    
    /* starting page */
    curPage = chm->index_root;
    
    /* until we have either returned or given up */
    while (curPage != -1)
    {
        
        /* try to fetch the index page */
        if (_chm_fetch_bytes(chm, page_buf,
                             (uqword)chm->dir_offset + (uqword)curPage*chm->block_len,
                             chm->block_len) != chm->block_len)
        {
            free(page_buf);
            return CHM_RESOLVE_FAILURE;
        }
        
        /* now, if it is a leaf node: */
        if (memcmp(page_buf, _chm_pmgl_marker, 4) == 0)
        {
            /* scan block */
            uchar *pEntry = _chm_find_in_PMGL(page_buf,
                                              chm->block_len,
                                              objPath);
            if (pEntry == NULL)
            {
                free(page_buf);
                return CHM_RESOLVE_FAILURE;
            }
            
            /* parse entry and return */
            _chm_parse_PMGL_entry(&pEntry, ui);
            free(page_buf);
            return CHM_RESOLVE_SUCCESS;
        }
        
        /* else, if it is a branch node: */
        else if (memcmp(page_buf, _chm_pmgi_marker, 4) == 0)
            curPage = _chm_find_in_PMGI(page_buf, chm->block_len, objPath);
        
        /* else, we are confused.  give up. */
        else
        {
            free(page_buf);
            return CHM_RESOLVE_FAILURE;
        }
    }
    
    /* didn't find anything.  fail. */
    free(page_buf);
    return CHM_RESOLVE_FAILURE;
}

qword chm_retrieve_object(chm_t *chm, chm_unitinfo *ui, unsigned char *buf, uqword addr, qword len) {
    if (addr >= ui->length)
        return (qword)0;
    
    /* clip length */
    if (addr + len > ui->length)
        len = ui->length - addr;
    
    /* if the file is uncompressed, it's simple */
    if (ui->space == CHM_UNCOMPRESSED)
    {
        /* read data */
        return _chm_fetch_bytes(chm,
                                buf,
                                (uqword)chm->data_offset + (uqword)ui->start + (uqword)addr,
                                len);
    }
    
    /* else if the file is compressed, it's a little trickier */
    else /* ui->space == CHM_COMPRESSED */
    {
        qword swath=0, total=0;
        
        /* if compression is not enabled for this file... */
        if (! chm->compression_enabled)
            return total;
        
        do {
            
            /* swill another mouthful */
            swath = _chm_decompress_region(chm, buf, ui->start + addr, len);
            
            /* if we didn't get any... */
            if (swath == 0)
                return total;
            
            /* update stats */
            total += swath;
            len -= swath;
            addr += swath;
            buf += swath;
            
        } while (len != 0);
        
        return total;
    }
}

int _unmarshal_lzxc_reset_table(unsigned char **pData, unsigned int *pDataLen, chm_lzxc_resettable *dest) {
    /* we only know how to deal with a 0x28 byte structures */
    if (*pDataLen != CHM_LZXC_RESETTABLE_V1_LEN)
        return 0;
    
    /* unmarshal fields */
    _unmarshal_uint32    (pData, pDataLen, &dest->version);
    _unmarshal_uint32    (pData, pDataLen, &dest->block_count);
    _unmarshal_uint32    (pData, pDataLen, &dest->unknown);
    _unmarshal_uint32    (pData, pDataLen, &dest->table_offset);
    _unmarshal_uint64    (pData, pDataLen, &dest->uncompressed_len);
    _unmarshal_uint64    (pData, pDataLen, &dest->compressed_len);
    _unmarshal_uint64    (pData, pDataLen, &dest->block_len);
    
    /* check structure */
    if (dest->version != 2)
        return 0;
    
    return 1;   
}

int _unmarshal_lzxc_control_data(unsigned char **pData,
                                        unsigned int *pDataLen,
                                        chm_lzxc_ctldata *dest)
{
    /* we want at least 0x18 bytes */
    if (*pDataLen < CHM_LZXC_MIN_LEN)
        return 0;
    
    /* unmarshal fields */
    _unmarshal_uint32    (pData, pDataLen, &dest->size);
    _unmarshal_char_array(pData, pDataLen, (char*)dest->signature, 4);
    _unmarshal_uint32    (pData, pDataLen, &dest->version);
    _unmarshal_uint32    (pData, pDataLen, &dest->resetInterval);
    _unmarshal_uint32    (pData, pDataLen, &dest->windowSize);
    _unmarshal_uint32    (pData, pDataLen, &dest->windowsPerReset);
    
    if (*pDataLen >= CHM_LZXC_V2_LEN)
        _unmarshal_uint32    (pData, pDataLen, &dest->unknown_18);
    else
        dest->unknown_18 = 0;
    
    if (dest->version == 2)
    {
        dest->resetInterval *= 0x8000;
        dest->windowSize *= 0x8000;
    }
    if (dest->windowSize == 0  ||  dest->resetInterval == 0)
        return 0;
    
    /* for now, only support resetInterval a multiple of windowSize/2 */
    if (dest->windowSize == 1)
        return 0;
    if ((dest->resetInterval % (dest->windowSize/2)) != 0)
        return 0;
    
    /* check structure */
    if (memcmp(dest->signature, "LZXC", 4) != 0)
        return 0;
    
    return 1;
}

void chm_set_param(chm_t* chm, int paramType, int paramVal) {
    switch (paramType)
    {
        case CHM_PARAM_MAX_BLOCKS_CACHED:
            if (paramVal != chm->cache_num_blocks)
            {
                uchar **newBlocks;
                uqword *newIndices;
                int     i;
                
                /* allocate new cached blocks */
                newBlocks = (uchar **)malloc(paramVal * sizeof (uchar *));
                if (newBlocks == NULL) return;
                newIndices = (uqword *)malloc(paramVal * sizeof (uqword));
                if (newIndices == NULL) { free(newBlocks); return; }
                for (i=0; i<paramVal; i++)
                {
                    newBlocks[i] = NULL;
                    newIndices[i] = 0;
                }
                
                /* re-distribute old cached blocks */
                if (chm->cache_blocks)
                {
                    for (i=0; i<chm->cache_num_blocks; i++)
                    {
                        int newSlot = (int)(chm->cache_block_indices[i] % paramVal);
                        
                        if (chm->cache_blocks[i])
                        {
                            /* in case of collision, destroy newcomer */
                            if (newBlocks[newSlot])
                            {
                                free(chm->cache_blocks[i]);
                                chm->cache_blocks[i] = NULL;
                            }
                            else
                            {
                                newBlocks[newSlot] = chm->cache_blocks[i];
                                newIndices[newSlot] =
                                chm->cache_block_indices[i];
                            }
                        }
                    }
                    
                    free(chm->cache_blocks);
                    free(chm->cache_block_indices);
                }
                
                /* now, set new values */
                chm->cache_blocks = newBlocks;
                chm->cache_block_indices = newIndices;
                chm->cache_num_blocks = paramVal;
            }
            break;
            
        default:
            break;
    }
}

int _unmarshal_char_array(unsigned char **pData,
                          unsigned int *pLenRemain,
                          char *dest,
                          int count)
{
    if (count <= 0  ||  (unsigned int)count > *pLenRemain)
        return 0;
    memcpy(dest, (*pData), count);
    *pData += count;
    *pLenRemain -= count;
    return 1;
}

int _unmarshal_uchar_array(unsigned char **pData,
                           unsigned int *pLenRemain,
                           unsigned char *dest,
                           int count)
{
    if (count <= 0  ||  (unsigned int)count > *pLenRemain)
        return 0;
    memcpy(dest, (*pData), count);
    *pData += count;
    *pLenRemain -= count;
    return 1;
}

int _unmarshal_int32(unsigned char **pData,
                     unsigned int *pLenRemain,
                     dword *dest)
{
    if (4 > *pLenRemain)
        return 0;
    *dest = (*pData)[0] | (*pData)[1]<<8 | (*pData)[2]<<16 | (*pData)[3]<<24;
    *pData += 4;
    *pLenRemain -= 4;
    return 1;
}

int _unmarshal_uint32(unsigned char **pData,
                      unsigned int *pLenRemain,
                      udword *dest)
{
    if (4 > *pLenRemain)
        return 0;
    *dest = (*pData)[0] | (*pData)[1]<<8 | (*pData)[2]<<16 | (*pData)[3]<<24;
    *pData += 4;
    *pLenRemain -= 4;
    return 1;
}

int _unmarshal_uuid(unsigned char **pData,
                    unsigned int *pDataLen,
                    unsigned char *dest)
{
    return _unmarshal_uchar_array(pData, pDataLen, dest, 16);
}

int _unmarshal_uint64(unsigned char **pData,
                      unsigned int *pLenRemain,
                      uqword *dest)
{
    qword temp;
    int i;
    if (8 > *pLenRemain)
        return 0;
    temp=0;
    for(i=8; i>0; i--)
    {
        temp <<= 8;
        temp |= (*pData)[i-1];
    }
    *dest = temp;
    *pData += 8;
    *pLenRemain -= 8;
    return 1;
}

uchar *_chm_find_in_PMGL(uchar *page_buf,
                         udword block_len,
                         const char *objPath)
{
    /* XXX: modify this to do a binary search using the nice index structure
     *      that is provided for us.
     */
    chm_header_pmgl header;
    unsigned int hremain;
    uchar *end;
    uchar *cur;
    uchar *temp;
    uqword strLen;
    char buffer[CHM_MAX_PATHLEN+1];
    
    /* figure out where to start and end */
    cur = page_buf;
    hremain = CHM_PMGL_LEN;
    if (! _unmarshal_pmgl_header(&cur, &hremain, &header))
        return NULL;
    end = page_buf + block_len - (header.free_space);
    
    /* now, scan progressively */
    while (cur < end)
    {
        /* grab the name */
        temp = cur;
        strLen = _chm_parse_cword(&cur);
        if (strLen > CHM_MAX_PATHLEN)
            return NULL;
        if (! _chm_parse_UTF8(&cur, strLen, buffer))
            return NULL;
        
        /* check if it is the right name */
        if (! strcasecmp(buffer, objPath))
            return temp;
        
        _chm_skip_PMGL_entry_data(&cur);
    }
    
    return NULL;
}

int _chm_parse_PMGL_entry(uchar **pEntry, chm_unitinfo *ui)
{
    uqword strLen;
    
    /* parse str len */
    strLen = _chm_parse_cword(pEntry);
    if (strLen > CHM_MAX_PATHLEN)
        return 0;
    
    /* parse path */
    if (! _chm_parse_UTF8(pEntry, strLen, ui->path))
        return 0;
    
    /* parse info */
    ui->space  = (int)_chm_parse_cword(pEntry);
    ui->start  = _chm_parse_cword(pEntry);
    ui->length = _chm_parse_cword(pEntry);
    return 1;
}

dword _chm_find_in_PMGI(uchar *page_buf,
                        dword block_len,
                        const char *objPath)
{
    /* XXX: modify this to do a binary search using the nice index structure
     *      that is provided for us
     */
    chm_header_pmgi header;
    unsigned int hremain;
    int page=-1;
    uchar *end;
    uchar *cur;
    uqword strLen;
    char buffer[CHM_MAX_PATHLEN+1];
    
    /* figure out where to start and end */
    cur = page_buf;
    hremain = CHM_PMGI_LEN;
    if (! _unmarshal_pmgi_header(&cur, &hremain, &header))
        return -1;
    end = page_buf + block_len - (header.free_space);
    
    /* now, scan progressively */
    while (cur < end)
    {
        /* grab the name */
        strLen = _chm_parse_cword(&cur);
        if (strLen > CHM_MAX_PATHLEN)
            return -1;
        if (! _chm_parse_UTF8(&cur, strLen, buffer))
            return -1;
        
        /* check if it is the right name */
        if (strcasecmp(buffer, objPath) > 0)
            return page;
        
        /* load next value for path */
        page = (int)_chm_parse_cword(&cur);
    }
    
    return page;
}

qword _chm_decompress_region(chm_t *chm, 
                             uchar *buf,
                             uqword start,
                             qword len)
{
    uqword nBlock, nOffset;
    uqword nLen;
    uqword gotLen;
    uchar *ubuffer;
    
    if (len <= 0)
        return (qword)0;
    
    /* figure out what we need to read */
    nBlock = start / chm->reset_table.block_len;
    nOffset = start % chm->reset_table.block_len;
    nLen = len;
    if (nLen > (chm->reset_table.block_len - nOffset))
        nLen = chm->reset_table.block_len - nOffset;
    
    if (chm->cache_block_indices[nBlock % chm->cache_num_blocks] == nBlock    &&
        chm->cache_blocks[nBlock % chm->cache_num_blocks] != NULL)
    {
        memcpy(buf,
               chm->cache_blocks[nBlock % chm->cache_num_blocks] + nOffset,
               (unsigned int)nLen);
        return nLen;
    }
    
    /* data request not satisfied, so... start up the decompressor machine */
    if (! chm->lzx_state)
    {
        int window_size = ffs(chm->window_size) - 1;
        chm->lzx_last_block = -1;
        chm->lzx_state = LZXinit(window_size);
    }
    
    /* decompress some data */
    gotLen = _chm_decompress_block(chm, nBlock, &ubuffer);
    if (gotLen < nLen)
        nLen = gotLen;
    memcpy(buf, ubuffer+nOffset, (unsigned int)nLen);
    return nLen;
}

int _unmarshal_pmgl_header(unsigned char **pData,
                           unsigned int *pDataLen,
                           chm_header_pmgl *dest)
{
    /* we only know how to deal with a 0x14 byte structures */
    if (*pDataLen != CHM_PMGL_LEN)
        return 0;
    
    /* unmarshal fields */
    _unmarshal_char_array(pData, pDataLen,  dest->signature, 4);
    _unmarshal_uint32    (pData, pDataLen, &dest->free_space);
    _unmarshal_uint32    (pData, pDataLen, &dest->unknown_0008);
    _unmarshal_int32     (pData, pDataLen, &dest->block_prev);
    _unmarshal_int32     (pData, pDataLen, &dest->block_next);
    
    /* check structure */
    if (memcmp(dest->signature, _chm_pmgl_marker, 4) != 0)
        return 0;
    
    return 1;
}

uqword _chm_parse_cword(uchar **pEntry)
{
    qword accum = 0;
    uchar temp;
    while ((temp=*(*pEntry)++) >= 0x80)
    {
        accum <<= 7;
        accum += temp & 0x7f;
    }
    
    return (accum << 7) + temp;
}

int _chm_parse_UTF8(uchar **pEntry, uqword count, char *path)
{
    /* XXX: implement UTF-8 support, including a real mapping onto
     *      ISO-8859-1?  probably there is a library to do this?  As is
     *      immediately apparent from the below code, I'm presently not doing
     *      any special handling for files in which none of the strings contain
     *      UTF-8 multi-byte characters.
     */
    while (count != 0)
    {
        *path++ = (char)(*(*pEntry)++);
        --count;
    }
    
    *path = '\0';
    return 1;
}

void _chm_skip_PMGL_entry_data(uchar **pEntry)
{
    _chm_skip_cword(pEntry);
    _chm_skip_cword(pEntry);
    _chm_skip_cword(pEntry);
}

int _unmarshal_pmgi_header(unsigned char **pData,
                           unsigned int *pDataLen,
                           chm_header_pmgi *dest)
{
    /* we only know how to deal with a 0x8 byte structures */
    if (*pDataLen != CHM_PMGI_LEN)
        return 0;
    
    /* unmarshal fields */
    _unmarshal_char_array(pData, pDataLen,  dest->signature, 4);
    _unmarshal_uint32    (pData, pDataLen, &dest->free_space);
    
    /* check structure */
    if (memcmp(dest->signature, _chm_pmgi_marker, 4) != 0)
        return 0;
    
    return 1;
}

void _chm_skip_cword(uchar **pEntry)
{
    while (*(*pEntry)++ >= 0x80)
        ;
}

qword _chm_decompress_block(chm_t *h,
                            uqword block,
                            uchar **ubuffer)
{
    uchar *cbuffer = malloc(((unsigned int)h->reset_table.block_len + 6144));
    uqword cmpStart;                                    /* compressed start  */
    qword cmpLen;                                       /* compressed len    */
    int indexSlot;                                      /* cache index slot  */
    uchar *lbuffer;                                     /* local buffer ptr  */
    udword blockAlign = (udword)(block % h->reset_blkcount); /* reset intvl. aln. */
    udword i;                                           /* local loop index  */
    
    if (cbuffer == NULL)
        return -1;
    
    /* let the caching system pull its weight! */
    if (block - blockAlign <= h->lzx_last_block  &&
        block              >= h->lzx_last_block)
        blockAlign = (udword)(block - h->lzx_last_block);
    
    /* check if we need previous blocks */
    if (blockAlign != 0)
    {
        /* fetch all required previous blocks since last reset */
        for (i = blockAlign; i > 0; i--)
        {
            udword curBlockIdx = (udword)block - i;
            
            /* check if we most recently decompressed the previous block */
            if (h->lzx_last_block != curBlockIdx)
            {
                if ((curBlockIdx % h->reset_blkcount) == 0)
                {
#ifdef CHM_DEBUG
                    fprintf(stderr, "***RESET (1)***\n");
#endif
                    LZXreset(h->lzx_state);
                }
                
                indexSlot = (int)((curBlockIdx) % h->cache_num_blocks);
                if (! h->cache_blocks[indexSlot])
                    h->cache_blocks[indexSlot] = (uchar *)malloc((unsigned int)(h->reset_table.block_len));
                if (! h->cache_blocks[indexSlot])
                {
                    free(cbuffer);
                    return -1;
                }
                h->cache_block_indices[indexSlot] = curBlockIdx;
                lbuffer = h->cache_blocks[indexSlot];
                
                /* decompress the previous block */
#ifdef CHM_DEBUG
                fprintf(stderr, "Decompressing block #%4d (EXTRA)\n", curBlockIdx);
#endif
                if (!_chm_get_cmpblock_bounds(h, curBlockIdx, &cmpStart, &cmpLen) ||
                    cmpLen < 0                                                    ||
                    cmpLen > h->reset_table.block_len + 6144                      ||
                    _chm_fetch_bytes(h, cbuffer, cmpStart, cmpLen) != cmpLen      ||
                    LZXdecompress(h->lzx_state, cbuffer, lbuffer, (int)cmpLen,
                                  (int)h->reset_table.block_len) != DECR_OK)
                {
#ifdef CHM_DEBUG
                    fprintf(stderr, "   (DECOMPRESS FAILED!)\n");
#endif
                    free(cbuffer);
                    return (qword)0;
                }
                
                h->lzx_last_block = (int)curBlockIdx;
            }
        }
    }
    else
    {
        if ((block % h->reset_blkcount) == 0)
        {
#ifdef CHM_DEBUG
            fprintf(stderr, "***RESET (2)***\n");
#endif
            LZXreset(h->lzx_state);
        }
    }
    
    /* allocate slot in cache */
    indexSlot = (int)(block % h->cache_num_blocks);
    if (! h->cache_blocks[indexSlot])
        h->cache_blocks[indexSlot] = (uchar *)malloc(((unsigned int)h->reset_table.block_len));
    if (! h->cache_blocks[indexSlot])
    {
        free(cbuffer);
        return -1;
    }
    h->cache_block_indices[indexSlot] = block;
    lbuffer = h->cache_blocks[indexSlot];
    *ubuffer = lbuffer;
    
    /* decompress the block we actually want */
#ifdef CHM_DEBUG
    fprintf(stderr, "Decompressing block #%4d (REAL )\n", block);
#endif
    if (! _chm_get_cmpblock_bounds(h, block, &cmpStart, &cmpLen)          ||
        _chm_fetch_bytes(h, cbuffer, cmpStart, cmpLen) != cmpLen          ||
        LZXdecompress(h->lzx_state, cbuffer, lbuffer, (int)cmpLen,
                      (int)h->reset_table.block_len) != DECR_OK)
    {
#ifdef CHM_DEBUG
        fprintf(stderr, "   (DECOMPRESS FAILED!)\n");
#endif
        free(cbuffer);
        return (qword)0;
    }
    h->lzx_last_block = (int)block;
    
    /* XXX: modify LZX routines to return the length of the data they
     * decompressed and return that instead, for an extra sanity check.
     */
    free(cbuffer);
    return h->reset_table.block_len;
}

int _chm_get_cmpblock_bounds(chm_t *h,
                             qword block,
                             uqword *start,
                             qword *len)
{
    uchar buffer[8], *dummy;
    unsigned int remain;
    
    /* for all but the last block, use the reset table */
    if (block < h->reset_table.block_count-1)
    {
        /* unpack the start address */
        dummy = buffer;
        remain = 8;
        if (_chm_fetch_bytes(h, buffer,
                             (uqword)h->data_offset
                             + (uqword)h->rt_unit.start
                             + (uqword)h->reset_table.table_offset
                             + (uqword)block*8,
                             remain) != remain                            ||
            !_unmarshal_uint64(&dummy, &remain, start))
            return 0;
        
        /* unpack the end address */
        dummy = buffer;
        remain = 8;
        if (_chm_fetch_bytes(h, buffer,
                             (uqword)h->data_offset
                             + (uqword)h->rt_unit.start
                             + (uqword)h->reset_table.table_offset
                             + (uqword)block*8 + 8,
                             remain) != remain                                ||
            !_unmarshal_int64(&dummy, &remain, len))
            return 0;
    }
    
    /* for the last block, use the span in addition to the reset table */
    else
    {
        /* unpack the start address */
        dummy = buffer;
        remain = 8;
        if (_chm_fetch_bytes(h, buffer,
                             (uqword)h->data_offset
                             + (uqword)h->rt_unit.start
                             + (uqword)h->reset_table.table_offset
                             + (uqword)block*8,
                             remain) != remain                            ||
            !_unmarshal_uint64(&dummy, &remain, start))
            return 0;
        
        *len = h->reset_table.compressed_len;
    }
    
    /* compute the length and absolute start address */
    *len -= *start;
    *start += h->data_offset + h->cn_unit.start;
    
    return 1;
}

int _unmarshal_int64(unsigned char **pData,
                     unsigned int *pLenRemain,
                     qword*dest)
{
    qword temp;
    int i;
    if (8 > *pLenRemain)
        return 0;
    temp=0;
    for(i=8; i>0; i--)
    {
        temp <<= 8;
        temp |= (*pData)[i-1];
    }
    *dest = temp;
    *pData += 8;
    *pLenRemain -= 8;
    return 1;
}

bool chm_enumerate(chm_t* h, int what, CHM_ENUMERATOR e, void *context) {
    dword curPage;
    
    /* buffer to hold whatever page we're looking at */
    /* RWE 6/12/2003 */
    uchar *page_buf = malloc((unsigned int)h->block_len);
    chm_header_pmgl header;
    uchar *end;
    uchar *cur;
    unsigned int lenRemain;
    uqword ui_path_len;
    
    /* the current ui */
    chm_unitinfo ui;
    int type_bits = (what & 0x7);
    int filter_bits = (what & 0xF8);
    
    if (page_buf == NULL)
        return 0;
    
    /* starting page */
    curPage = h->index_head;
    
    /* until we have either returned or given up */
    while (curPage != -1)
    {
        
        /* try to fetch the index page */
        if (_chm_fetch_bytes(h,
                             page_buf,
                             (uqword)h->dir_offset + (uqword)curPage*h->block_len,
                             h->block_len) != h->block_len)
        {
            free(page_buf);
            return 0;
        }
        
        /* figure out start and end for this page */
        cur = page_buf;
        lenRemain = CHM_PMGL_LEN;
        if (! _unmarshal_pmgl_header(&cur, &lenRemain, &header))
        {
            free(page_buf);
            return 0;
        }
        end = page_buf + h->block_len - (header.free_space);
        
        /* loop over this page */
        while (cur < end)
        {
            ui.flags = 0;
            
            if (! _chm_parse_PMGL_entry(&cur, &ui))
            {
                free(page_buf);
                return 0;
            }
            
            /* get the length of the path */
            ui_path_len = strlen(ui.path)-1;
            
            /* check for DIRS */
            if (ui.path[ui_path_len] == '/')
                ui.flags |= CHM_ENUMERATE_DIRS;
            
            /* check for FILES */
            if (ui.path[ui_path_len] != '/')
                ui.flags |= CHM_ENUMERATE_FILES;
            
            /* check for NORMAL vs. META */
            if (ui.path[0] == '/')
            {
                
                /* check for NORMAL vs. SPECIAL */
                if (ui.path[1] == '#'  ||  ui.path[1] == '$')
                    ui.flags |= CHM_ENUMERATE_SPECIAL;
                else
                    ui.flags |= CHM_ENUMERATE_NORMAL;
            }
            else
                ui.flags |= CHM_ENUMERATE_META;
            
            if (! (type_bits & ui.flags))
                continue;
            
            if (filter_bits && ! (filter_bits & ui.flags))
                continue;
            
            /* call the enumerator */
            {
                int status = (*e)(h, &ui, context);
                switch (status)
                {
                    case CHM_ENUMERATOR_FAILURE:
                        free(page_buf);
                        return 0;
                    case CHM_ENUMERATOR_CONTINUE:
                        break;
                    case CHM_ENUMERATOR_SUCCESS:
                        free(page_buf);
                        return 1;
                    default:
                        break;
                }
            }
        }
        
        /* advance to next page */
        curPage = header.block_next;
    }
    
    free(page_buf);
    return 1;
}

bool chm_enumerate_dir(chm_t* h, const char *prefix, int what, CHM_ENUMERATOR e, void *context) {
    /*
     * XXX: do this efficiently (i.e. using the tree index)
     */
    
    dword curPage;
    
    /* buffer to hold whatever page we're looking at */
    /* RWE 6/12/2003 */
    uchar *page_buf = malloc((unsigned int)h->block_len);
    chm_header_pmgl header;
    uchar *end;
    uchar *cur;
    unsigned int lenRemain;
    
    /* set to 1 once we've started */
    int it_has_begun=0;
    
    /* the current ui */
    chm_unitinfo ui;
    int type_bits = (what & 0x7);
    int filter_bits = (what & 0xF8);
    uqword ui_path_len;
    
    /* the length of the prefix */
    char prefixRectified[CHM_MAX_PATHLEN+1];
    int prefixLen;
    char lastPath[CHM_MAX_PATHLEN+1];
    int lastPathLen;
    
    if (page_buf == NULL)
        return 0;
    
    /* starting page */
    curPage = h->index_head;
    
    /* initialize pathname state */
    strncpy(prefixRectified, prefix, CHM_MAX_PATHLEN);
    prefixRectified[CHM_MAX_PATHLEN] = '\0';
    prefixLen = (int)strlen(prefixRectified);
    if (prefixLen != 0)
    {
        if (prefixRectified[prefixLen-1] != '/')
        {
            prefixRectified[prefixLen] = '/';
            prefixRectified[prefixLen+1] = '\0';
            ++prefixLen;
        }
    }
    lastPath[0] = '\0';
    lastPathLen = -1;
    
    /* until we have either returned or given up */
    while (curPage != -1)
    {
        
        /* try to fetch the index page */
        if (_chm_fetch_bytes(h,
                             page_buf,
                             (uqword)h->dir_offset + (uqword)curPage*h->block_len,
                             h->block_len) != h->block_len)
        {
            free(page_buf);
            return 0;
        }
        
        /* figure out start and end for this page */
        cur = page_buf;
        lenRemain = CHM_PMGL_LEN;
        if (! _unmarshal_pmgl_header(&cur, &lenRemain, &header))
        {
            free(page_buf);
            return 0;
        }
        end = page_buf + h->block_len - (header.free_space);
        
        /* loop over this page */
        while (cur < end)
        {
            ui.flags = 0;
            
            if (! _chm_parse_PMGL_entry(&cur, &ui))
            {
                free(page_buf);
                return 0;
            }
            
            /* check if we should start */
            if (! it_has_begun)
            {
                if (ui.length == 0  &&  strncasecmp(ui.path, prefixRectified, prefixLen) == 0)
                    it_has_begun = 1;
                else
                    continue;
                
                if (ui.path[prefixLen] == '\0')
                    continue;
            }
            
            /* check if we should stop */
            else
            {
                if (strncasecmp(ui.path, prefixRectified, prefixLen) != 0)
                {
                    free(page_buf);
                    return 1;
                }
            }
            
            /* check if we should include this path */
            if (lastPathLen != -1)
            {
                if (strncasecmp(ui.path, lastPath, lastPathLen) == 0)
                    continue;
            }
            strncpy(lastPath, ui.path, CHM_MAX_PATHLEN);
            lastPath[CHM_MAX_PATHLEN] = '\0';
            lastPathLen = (int)strlen(lastPath);
            
            /* get the length of the path */
            ui_path_len = strlen(ui.path)-1;
            
            /* check for DIRS */
            if (ui.path[ui_path_len] == '/')
                ui.flags |= CHM_ENUMERATE_DIRS;
            
            /* check for FILES */
            if (ui.path[ui_path_len] != '/')
                ui.flags |= CHM_ENUMERATE_FILES;
            
            /* check for NORMAL vs. META */
            if (ui.path[0] == '/')
            {
                
                /* check for NORMAL vs. SPECIAL */
                if (ui.path[1] == '#'  ||  ui.path[1] == '$')
                    ui.flags |= CHM_ENUMERATE_SPECIAL;
                else
                    ui.flags |= CHM_ENUMERATE_NORMAL;
            }
            else
                ui.flags |= CHM_ENUMERATE_META;
            
            if (! (type_bits & ui.flags))
                continue;
            
            if (filter_bits && ! (filter_bits & ui.flags))
                continue;
            
            /* call the enumerator */
            {
                int status = (*e)(h, &ui, context);
                switch (status)
                {
                    case CHM_ENUMERATOR_FAILURE:
                        free(page_buf);
                        return 0;
                    case CHM_ENUMERATOR_CONTINUE:
                        break;
                    case CHM_ENUMERATOR_SUCCESS:
                        free(page_buf);
                        return 1;
                    default:
                        break;
                }
            }
        }
        
        /* advance to next page */
        curPage = header.block_next;
    }
    
    free(page_buf);
    return 1;
}

WSI_END_C