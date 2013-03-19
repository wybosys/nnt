
# ifndef __WSI_CORE_NSLOCKER_626EACFBDA054D4394461A6335235C9F_H_INCLUDED
# define __WSI_CORE_NSLOCKER_626EACFBDA054D4394461A6335235C9F_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface WSINSLock : NSLock

//- (void)lock;
//- (BOOL)tryLock;

@end

@interface WSINSConditionLock : NSConditionLock

//- (void)lock;
//- (BOOL)tryLock;

@end

@interface WSINSRecursiveLock : NSRecursiveLock

//- (void)lock;
//- (BOOL)tryLock;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX

template <typename TObjc>
class AutoReleaseObj
{
public:
    
    AutoReleaseObj()
    : ptr (0)
    {
        lock = [[WSINSLock alloc] init];
    }
    
    ~AutoReleaseObj()
    {
        safe_release(ptr);
        safe_release(lock);
    }
    
    TObjc* getInstance()
    {
        [lock lock];
        if (ptr == nil)
        {
            ptr = [[TObjc alloc] init];
            if ([ptr respondsToSelector:@selector(instanceInit)]) {
                [ptr performSelector:@selector(instanceInit) withObject:nil];
            }
        }
        [lock unlock];
        return ptr;
    }
    
    WSINSLock *lock;
    TObjc* ptr;
    
};

WSI_END_HEADER_CXX

# endif

# endif
