
# ifndef __WSI_MODEL_TABLE_2E1DBE3F0E024917BEBE87D75D450B32_H_INCLUDED
# define __WSI_MODEL_TABLE_2E1DBE3F0E024917BEBE87D75D450B32_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

# import "Model.h"
# import "IVTable.h"

WSIDECL_PRIVATE_HEAD(MTable);

@interface MTable : Model <IVTable> {
    
    uint all_records; //! all records
    uint from; //! record from
    uint many; //! how many records should be get
	
	WSIDECL_PRIVATE(MTable);
}

@property (nonatomic) uint all_records;
@property (nonatomic) uint from;
@property (nonatomic) uint many;

- (void)add_col:(NSArray*)col ids:(NSArray*)colid;
- (void)add_col:(NSString*)col id:(NSString*)colid;
- (void)add_row:(NSArray*)row;

@end

WSI_END_HEADER_OBJC

# endif