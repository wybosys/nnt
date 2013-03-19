
# ifndef __NNT_VIEW_TABLE_927663663C3F4D79897750344FDE1CB4_H_INCLUDED
# define __NNT_VIEW_TABLE_927663663C3F4D79897750344FDE1CB4_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@protocol IVTable

- (uint)row_length;
- (uint)col_length;
- (NSArray*)row_at:(uint)index;
- (NSString*)col_at:(uint)index;

@end

NNT_END_HEADER_OBJC

# endif