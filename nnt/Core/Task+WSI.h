
# ifndef __WSI_TASK_45878518D409441CAFE47BAC3E7DAC82_H_INCLUDED
# define __WSI_TASK_45878518D409441CAFE47BAC3E7DAC82_H_INCLUDED

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

@interface WSICondition : NSObject {
    void* _obj;
}

- (void)wait;
- (void)signal;

@end

WSI_END_HEADER_OBJC

# endif

# ifdef WSI_CXX

# ifdef WSI_UNIX
#   include <semaphore.h>
# endif

WSI_BEGIN_HEADER_CXX 
WSI_BEGIN_NS(core)

WSICLASS(Mutex);
WSICLASS(Task);
WSICLASS(Condition);
WSICLASS(Semaphore);

WSIDECL_PRIVATE_HEAD_CXX(Task);

class Mutex
{
public:

    Mutex();
    ~Mutex();
    
    void lock();
    void unlock();
    bool try_lock();
    
protected:

# ifdef WSI_MSVC
    HANDLE
# else
    pthread_mutex_t
# endif
    _hdl;

};

class Wait
{
public:
    
    Wait()
    {
        PASS;
    }
    
    void wait()
    {
        _mtx.lock();
        _mtx.lock();
        _mtx.unlock();
    }
    
    void go()
    {
        _mtx.unlock();
    }
    
protected:
    
    Mutex _mtx;
    
};

typedef cxx::Lockable<Mutex> LockableObject;

class Condition
{
public:

    Condition();
    ~Condition();
        
    void wait();
    void signal();
    
protected:

# ifdef WSI_MSVC
    HANDLE
# else
    pthread_mutex_t _mtx;
    pthread_cond_t
# endif
    _hdl;

};

class Semaphore
{
    
public:

    Semaphore(uint);
    ~Semaphore();
    
    void lock();
    void unlock();
    
protected:

# if defined(WSI_MSVC)    
    HANDLE
# elif defined(WSI_MACH)   
    sem_t*
# else    
    sem_t*
# endif    
    _hdl;

};

WSI_BEGIN_NS(tpl)

template <uint N>
class Semaphore
: public ::wsi::core::Semaphore
{
public:
    
    Semaphore()
    : ::wsi::core::Semaphore(N)
    {
        PASS;
    }
    
};

WSI_END_NS

class Task
: public cxx::Object<>
{
    WSIDECL_PRIVATE_CXX(Task);
    WSIDECL_NOCOPY(Task);
    
public:       
    
    typedef int (*func_run)(Task*);
    
    //! wait task stop.
    void wait();
        
    //! run.
    bool start(func_run);
    
    //! start.
    bool start();
    
    //! infinite.
    void infinite();
    
    //! control.
    void resume();
    void suspend();
    void stop();
    
    //! complete.
    bool complete() const;
    
public:

# ifdef main
#   undef main
# endif

    virtual int main() 
    { 
        return 0; 
    }

    uint count;
    
protected:

    Task();
    virtual ~Task();

};

WSI_END_NS
WSI_END_HEADER_CXX

# endif // cxx

# endif
