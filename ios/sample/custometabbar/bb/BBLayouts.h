
# ifndef __BBLAYOUTS_EAA6A9E777DB4C728875A2FD9D79A02C_H_INCLUDED
# define __BBLAYOUTS_EAA6A9E777DB4C728875A2FD9D79A02C_H_INCLUDED

# import "BBLayout.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(BBLayout);

@interface BBGridLayout : BBLayout {

    NSInteger   _columnCount;
    CGFloat     _padding;
    CGFloat     _spacing;
}

@property (nonatomic) NSInteger columnCount;
@property (nonatomic) CGFloat   padding;
@property (nonatomic) CGFloat   spacing;

@end

@interface BBFlowLayout : BBLayout {

    CGFloat   _padding;
    CGFloat   _spacing;
}

@property (nonatomic) CGFloat padding;
@property (nonatomic) CGFloat spacing;

@end

WSI_END_HEADER_OBJC

# endif