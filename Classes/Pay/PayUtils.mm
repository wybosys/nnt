
# import "Core.h"
# import "PayUtils.h"


NNT_BEGIN_CXX
NNT_BEGIN_NS(pay)

ns::String utils::orderid()
{
 	const int N = 15;
	
	NSString *sourceString = @"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	NSMutableString *result = [[[NSMutableString alloc] init] autorelease];
	srand(time(0));
	for (int i = 0; i < N; i++)
	{
		unsigned index = rand() % [sourceString length];
		NSString *s = [sourceString substringWithRange:NSMakeRange(index, 1)];
		[result appendString:s];
	}
    
	return result;
}

ulong utils::ordertime()
{
    return timestamp();
}

NNT_END_NS
NNT_END_CXX
