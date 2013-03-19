
# import "Core.h"
# import "NSRegexLibrary.h"

WSI_BEGIN_OBJC

NSString* kMatch_Email = @"^[a-zA-Z0-9_]+@[a-zA-Z0-9_]+(?:\\.[a-zA-Z0-9]+)+$";
NSString* kMatch_Password = @"\\S{6,15}";
NSString* kMatch_Cellphone = @"([0-9]{3})+([0-9]{4})+([0-9]{4})+";
NSString* kMatch_Zipcode = @"([0-9]{3})+.([0-9]{4})+";
NSString* kMatch_Telephone = @"([0-9]{4})+([0-9]{7})+";

WSI_END_OBJC