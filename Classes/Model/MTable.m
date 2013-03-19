
# import "Core.h"
# import "MTable.h"

NNT_BEGIN

NNTDECL_PRIVATE_BEGIN(MTable, NNTObject)
{
	NSMutableArray *_col;
	NSMutableArray *_colid;
	NSMutableArray *_rows;
}

@property (nonatomic, retain) NSMutableArray *colid;
@property (nonatomic, retain) NSMutableArray *col;
@property (nonatomic, retain) NSMutableArray *rows;

NNTDECL_PRIVATE_IMPL(MTable)

@synthesize col = _col, colid = _colid, rows = _rows;

- (id)init {
	self = [super init];
	
	_col = [NSMutableArray new];
	_colid = [NSMutableArray new];
	_rows = [NSMutableArray new];
	
	return self;
}

- (void)fini {
	zero_release(_col);
	zero_release(_colid);
	zero_release(_rows);

    [super fini];
}

NNTDECL_PRIVATE_END

@implementation MTable

@synthesize all_records, from, many;

- (id)init {
	self = [super init];
    NNTDECL_PRIVATE_INIT(MTable);
    
    from = 0;
    many = -1;
	
	return self;
}

- (void)fini {
    NNTDECL_PRIVATE_DEALLOC();
    [super fini];
}

- (BOOL)is_valid:(NSObject *)result {
	if (NO == [result isKindOfClass:[NSDictionary class]]) 
        return NO;
	if ([(NSDictionary*)result objectForKey:@"col"] == nil) 
        return NO;
	if ([(NSDictionary*)result objectForKey:@"rows"] == nil) 
        return NO;
	return YES;
}

- (BOOL)process:(NSObject *)result {
	if (NO == [self is_valid:result]) 
        return NO;
    
    NSString *allrecords = [(NSDictionary*)result valueForKey:@"all_records"];
    all_records = allrecords ? [allrecords intValue] : 0;
	
	NSArray *col = [(NSDictionary*)result valueForKey:@"col"];
	NSArray *rows = [(NSDictionary*)result valueForKey:@"rows"];
	
	// filter data
    if ([d_ptr.colid count]) {
        int *indices = (int*)malloc(sizeof(int) * [d_ptr.colid count]);
        memset(indices, 0, sizeof(int) * [d_ptr.colid count]);
        int idcol = 0;
        for (NSString *coleach in col) {
            NSUInteger index = [d_ptr.colid indexOfObject:coleach];
            if (NSNotFound != index) {
                indices[index] = idcol + 1;
            }
            ++idcol;
        }
        
        for (NSArray *eachrow in rows) {
            // file value
            NSMutableArray *row = [[NSMutableArray new] autorelease];
            for (int idc = 0; idc < [d_ptr.colid count]; ++idc) {
                if (indices[idc] != 0) {
                    [row addObject:[eachrow objectAtIndex:indices[idc] - 1]];
                } else {
                    [row addObject:@""];
                }
            }
            [d_ptr.rows addObject:row];
        }
        
        free(indices);
	} else {
        
        [d_ptr.col removeAllObjects];        
        
        NSMutableArray *arr = [[NSMutableArray alloc] initWithArray:col];
        d_ptr.col = arr;
        [arr release];
        
        [d_ptr.rows removeAllObjects];
        
        arr = [[NSMutableArray alloc] initWithArray:rows];
        d_ptr.rows = arr;
        [arr release];
    }

	return YES;
}

- (uint)row_length {
	return (uint)[d_ptr.rows count];
}

- (uint)col_length {
	return (uint)[d_ptr.col count];
}

- (NSArray*)row_at:(uint)index {
	return [d_ptr.rows objectAtIndex:index];
}

- (NSString*)col_at:(uint)index {
	return [d_ptr.col objectAtIndex:index];
}

- (void)add_col:(NSArray*)col ids:(NSArray*)colid {
	[d_ptr.col addObjectsFromArray:col];
	[d_ptr.colid addObjectsFromArray:colid];
}

- (void)add_col:(NSString*)col id:(NSString *)colid {
    [d_ptr.col addObject:col];
    [d_ptr.colid addObject:colid];
}

- (void)add_row:(NSArray *)row {
    [d_ptr.rows addObject:row];
}

- (NSMutableArray*)get_params {
    NSMutableArray *ret = [NSMutableArray arrayWithArray:[super get_params]];
    [ret addObject:[NSDictionary dictionaryWithObjectsAndKeys:
                    [NSNumber numberWithInt:self.from], @"from",
                    [NSNumber numberWithInt:self.many], @"many",
                    nil]];
    return ret;
}


@end

NNT_END
