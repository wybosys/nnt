
#ifndef INCLUDED_LZX_H
#define INCLUDED_LZX_H

#ifdef __cplusplus
extern "C" {
#endif

/* return codes */
#define DECR_OK           (0)
#define DECR_DATAFORMAT   (1)
#define DECR_ILLEGALDATA  (2)
#define DECR_NOMEMORY     (3)

/* opaque state structure */
struct LZXstate;

/* create an lzx state object */
struct LZXstate *LZXinit(int window);

/* destroy an lzx state object */
void LZXteardown(struct LZXstate *pState);

/* reset an lzx stream */
int LZXreset(struct LZXstate *pState);

/* decompress an LZX compressed block */
int LZXdecompress(struct LZXstate *pState,
                  unsigned char *inpos,
                  unsigned char *outpos,
                  int inlen,
                  int outlen);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDED_LZX_H */
