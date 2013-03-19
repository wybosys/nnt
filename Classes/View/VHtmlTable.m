
# import "Core.h"
# import "VHtmlTable.h"
# import "IVTable.h"
# import "VHtml.h"
# import "NNTResource.h"

NNT_BEGIN

@implementation VHtmlTable

- (NSString*)make:(NSObject*)__model {
	if (NO == [__model conformsToProtocol:@protocol(IVTable)]) 
        return @"";
    
	NSMutableString *html = [[NSMutableString new] autorelease];
		
	id<IVTable> model = (id<IVTable>)__model;

	NSMutableString *table = [[NSMutableString new] autorelease];
    
    [html appendString:[VHtml make_css:[NNTResource ContentOf:@"VHtmlTable_CSS.css"]]];
    
	[table appendString:@"<table class=\"ipad_tb_02\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\">"];
	
	// append colgroup
    
	[table appendString:@"<colgroup>"];
	for (uint idx = 0; idx < [model col_length]; ++idx) {
		[table appendString:@"<col></col>"];
	}
	[table appendString:@"</colgroup>"];
    
	// append header
	[table appendString:@"<tr>"];
	for (uint idx = 0; idx < [model col_length]; ++idx) {
		NSString *col = [model col_at:idx];
		[table appendString:@"<th class=\"ipad_tb_04\">"];
		[table appendString:col];
    //    [table appendFormat:@"<td class=\"ipad_tb_04\">%@</td>",_W(col)];
	}
	[table appendString:@"</tr>"];
	// append row
	for (uint idr = 0; idr < [model row_length]; ++idr) {
		NSArray const* row = [model row_at:idr];
		if (idr % 2 == 0) {
			[table appendString:@"<tr>"];
		} else {
			[table appendString:@"<tr"];
		}
		for (uint idc = 0; idc < [row count]; ++idc) {
			NSString *cell = [row objectAtIndex:idc];
			[table appendString:@"<td class=\"ipad_tb_01\">"];
			[table appendString:cell];
            [table appendString:@"</td>"];
		}
		[table appendString:@"</tr>"];
	}
	
	[table appendString:@"</table>"];
    
	[html appendString:table];

	return html;
}

@end

NNT_END
