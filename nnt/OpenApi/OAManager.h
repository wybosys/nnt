
# ifndef __WSI_OA_MANAGER_57126B4D029E4032995DE800D6874454_H_INCLUDED
# define __WSI_OA_MANAGER_57126B4D029E4032995DE800D6874454_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(OAManager);

typedef struct {
    Class clsPost;
} oaclass_seg;

@interface OAManager : WSIObject {
    WSIDECL_PRIVATE(OAManager);
}

WSIDECL_SINGLETON(OAManager);

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
# ifdef WSI_CXX

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

WSI_END_HEADER_OBJC

# endif