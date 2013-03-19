
# ifndef __WSI_VIEW_TABLE_927663663C3F4D79897750344FDE1CB4_H_INCLUDED
# define __WSI_VIEW_TABLE_927663663C3F4D79897750344FDE1CB4_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@protocol IVTable

- (uint)row_length;
- (uint)col_length;
- (NSArray*)row_at:(uint)index;
- (NSString*)col_at:(uint)index;

@end

WSI_END_HEADER_OBJC

# endif