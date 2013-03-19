
# ifndef __NNT_MODEL_TABLE_2E1DBE3F0E024917BEBE87D75D450B32_H_INCLUDED
# define __NNT_MODEL_TABLE_2E1DBE3F0E024917BEBE87D75D450B32_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

# import "Model.h"
# import "IVTable.h"

NNTDECL_PRIVATE_HEAD(MTable);

@interface MTable : Model <IVTable> {
    
    uint all_records; //! all records
    uint from; //! record from
    uint many; //! how many records should be get
	
	NNTDECL_PRIVATE(MTable);
}

@property (nonatomic) uint all_records;
@property (nonatomic) uint from;
@property (nonatomic) uint many;

- (void)add_col:(NSArray*)col ids:(NSArray*)colid;
- (void)add_col:(NSString*)col id:(NSString*)colid;
- (void)add_row:(NSArray*)row;

@end

NNT_END_HEADER_OBJC

# endif