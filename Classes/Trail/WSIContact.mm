
# import "Core.h"
# import "WSIContact.h"
# import <AddressBook/AddressBook.h>

WSI_BEGIN_OBJC

# define REC ((ABRecordRef)record)

@implementation WSIContact

- (id)initWithRecord:(void const*)_record {
    self = [super init];
    record = CFRetain((ABRecordRef)_record);
    return self;
}

- (void)dealloc {
    if (record) {
        CFRelease(record);
        record = 0;
    }
    [super dealloc];
}

+ (id)contactWithRecord:(const void *)record {
    return [[[WSIContact alloc] initWithRecord:record] autorelease];
}

- (NSArray *)findProperty:(ABPropertyID)property {
    CFTypeRef thProperty = ABRecordCopyValue(REC, property);
    if (thProperty == nil)
        return nil;

    NSArray *items = (NSArray *)ABMultiValueCopyArrayOfAllValues(thProperty);
    CFRelease(thProperty);
    return [items autorelease];    
}

- (NSArray *)labelsForProperty:(ABPropertyID)property {
    CFTypeRef theProperty = ABRecordCopyValue(REC, property);
    NSMutableArray *labels = [NSMutableArray array];
    for (int i = 0; i < ABMultiValueGetCount(theProperty); i++) {
        NSString *label = (NSString *)ABMultiValueCopyLabelAtIndex(theProperty, i);
        [labels addObject:label];
        [label release];
    }
    CFRelease(theProperty);
    return labels;
}

- (NSString*)valueForKey:(ABPropertyID)property {
    return [(NSString *)ABRecordCopyValue(REC, property) autorelease];
}

@end

@implementation WSIPerson

+ (id)person {
    ABRecordRef person = ABPersonCreate();
    id ret = [WSIPerson personWithRecord:person];
    CFRelease(person);
    return ret;
}

+ (id)personWithRecord:(const void *)record {
    return [[[WSIPerson alloc] initWithRecord:record] autorelease];
}

- (NSString*)fullName {
    NSMutableString *string = [NSMutableString string];
	if (self.firstName || self.lastName){        
		if (self.prefix) [string appendFormat:@"%@ ", self.prefix];
		if (self.firstName) [string appendFormat:@"%@ ", self.firstName];
		if (self.nickName) [string appendFormat:@"\"%@\" ", self.nickName];
		if (self.lastName) [string appendFormat:@"%@", self.lastName];
		
		if (self.suffix && string.length)
			[string appendFormat:@", %@ ", self.suffix];
		else
			[string appendFormat:@" "];
	}
	if (self.organization) [string appendString:self.organization];
	return [string stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
}

- (NSString*)firstName {
    return [self valueForKey:kABPersonFirstNameProperty];
}

- (NSString*)lastName {
    return [self valueForKey:kABPersonLastNameProperty];
}

- (NSString*)nickName {
    return [self valueForKey:kABPersonNicknameProperty];
}

- (NSString*)prefix {
    return [self valueForKey:kABPersonPrefixProperty];
}

- (NSString*)suffix {
    return [self valueForKey:kABPersonSuffixProperty];
}

- (NSString*)organization {
    return [self valueForKey:kABPersonOrganizationProperty];
}

- (NSArray*)emails {
    return [self findProperty:kABPersonEmailProperty];
}

- (NSArray*)emailLabels {
    return [self labelsForProperty:kABPersonEmailProperty];
}

- (NSArray*)phones {
    return [self findProperty:kABPersonPhoneProperty];
}

- (NSArray*)phonesSimple {
    NSArray* arr = self.phones;
    NSMutableArray* ret = [[NSMutableArray alloc] initWithCapacity:arr.count];
    
    for (NSString* each in arr) {
        NSString* str = [each stringByReplacingOccurrencesOfString:@"-" withString:@""];
        [ret addObject:str];
    }
    
    return [ret autorelease];
}

- (NSArray*)phoneLabels {
    return [self labelsForProperty:kABPersonPhoneProperty];
}

@end

@implementation WSIAddressBook

@synthesize contacts;

WSIIMPL_SINGLETON(WSIAddressBook);

- (id)init {
    self = [super init];
    
    _addressBook = ABAddressBookCreate();
    
    return self;
}

- (void)instanceInit {
    [self refresh];
}

- (void)dealloc {
    CFRelease(_addressBook), _addressBook = nil;
    zero_release(contacts);
    [super dealloc];
}

- (void)refresh {
    NSArray *thePeople = (NSArray *)ABAddressBookCopyArrayOfAllPeople(_addressBook);
    NSMutableArray *array = [[NSMutableArray alloc] initWithCapacity:thePeople.count];
    for (id person in thePeople) {
        [array addObject:[WSIPerson personWithRecord:person]];
    }
    [thePeople release];
    self.contacts = array;
    [array release];    
}

@end

WSI_END_OBJC