
# ifndef __NNT_OA_MANAGER_57126B4D029E4032995DE800D6874454_H_INCLUDED
# define __NNT_OA_MANAGER_57126B4D029E4032995DE800D6874454_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(OAManager);

typedef struct {
    Class clsPost;
} oaclass_seg;

@interface OAManager : NNTObject {
    NNTDECL_PRIVATE(OAManager);
}

NNTDECL_SINGLETON(OAManager);

//! register a api class.
+ (BOOL)registerApi:(Class)cls;
- (BOOL)registerApi:(Class)cls;

//! count.
+ (uint)count;
- (uint)count;

//! class at index.
+ (Class)classAtIndex:(uint)idx;
- (Class)classAtIndex:(uint)idx;

//! iterator
# ifdef NNT_CXX

typedef ::wsi::core::map<Class, oaclass_seg>::iterator oamanager_iterator;

- (oamanager_iterator)iterator_begin;
- (oamanager_iterator)iterator_end;

- (void)showAllWeibo;
- (void)showSina;
- (void)showTencent;
- (void)showTencentOS;
- (void)showNetease;
- (void)showKaixin;
- (void)showRenren;
- (void)showSohu;
- (void)showDouban;

# endif

@end

NNT_END_HEADER_OBJC

# endif