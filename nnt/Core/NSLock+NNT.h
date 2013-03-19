
# ifndef __NNT_CORE_NSLOCKER_626EACFBDA054D4394461A6335235C9F_H_INCLUDED
# define __NNT_CORE_NSLOCKER_626EACFBDA054D4394461A6335235C9F_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface NNTNSLock : NSLock

//- (void)lock;
//- (BOOL)tryLock;

@end

@interface NNTNSConditionLock : NSConditionLock

//- (void)lock;
//- (BOOL)tryLock;

@end

@interface NNTNSRecursiveLock : NSRecursiveLock

//- (void)lock;
//- (BOOL)tryLock;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX

template <typename TObjc>
class AutoReleaseObj
{
public:
    
    AutoReleaseObj()
    : ptr (0)
    {
        lock = [[NNTNSLock alloc] init];
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
    
    NNTNSLock *lock;
    TObjc* ptr;
    
};

NNT_END_HEADER_CXX

# endif

# endif
