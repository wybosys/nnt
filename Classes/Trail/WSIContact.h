
# ifndef __NNT_TRAIL_CONTACT_B217F065C5EF4455BA1D558A6C12CF59_H_INCLUDED
# define __NNT_TRAIL_CONTACT_B217F065C5EF4455BA1D558A6C12CF59_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface NNTContact : NNTObject {
    void const* record;
}

//! init.
- (id)initWithRecord:(void const*)record;

//! instance.
+ (id)contactWithRecord:(void const*)record;

//! find property.
- (NSArray*)findProperty:(int)uid;

//! find label.
- (NSArray*)labelsForProperty:(int)uid;

//! find value.
- (NSString*)valueForKey:(int)uid;

@end

@interface NNTPerson : NNTContact

+ (id)person;
+ (id)personWithRecord:(void const*)record;

// info.
- (NSString*)firstName;
- (NSString*)lastName;
- (NSString*)nickName;
- (NSString*)fullName;
- (NSString*)prefix;
- (NSString*)suffix;
- (NSString*)organization;
- (NSArray*)emails;
- (NSArray*)emailLabels;
- (NSArray*)phones;
- (NSArray*)phonesSimple;
- (NSArray*)phoneLabels;

@end

@interface NNTAddressBook : NNTObject {
    
    //! all contacts.
    NSArray* contacts;
    
    @protected
    
    //! address book handle.
    CFTypeRef _addressBook;
}

@property (nonatomic, retain) NSArray* contacts;

NNTDECL_SINGLETON(NNTAddressBook);

//! refresh all contacts.
- (void)refresh;

@end

NNT_END_HEADER_OBJC

# endif