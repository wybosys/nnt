
# ifndef __NNT_TASK_45878518D409441CAFE47BAC3E7DAC82_H_INCLUDED
# define __NNT_TASK_45878518D409441CAFE47BAC3E7DAC82_H_INCLUDED

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

@interface NNTCondition : NSObject {
    void* _obj;
}

- (void)wait;
- (void)signal;

@end

NNT_END_HEADER_OBJC

# endif

# ifdef NNT_CXX

# ifdef NNT_USER_SPACE

# ifdef NNT_UNIX

#   include <semaphore.h>

# endif

NNT_BEGIN_HEADER_CXX 
NNT_BEGIN_NS(core)

NNTCLASS(Mutex);
NNTCLASS(Task);
NNTCLASS(Condition);
NNTCLASS(Semaphore);

NNTDECL_PRIVATE_HEAD_CXX(Task);

class Mutex
{
public:

    Mutex();
    ~Mutex();
    
    void lock();
    void unlock();
    bool try_lock();
    
protected:

# ifdef NNT_MSVC
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

# ifdef NNT_MSVC
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

# if defined(NNT_MSVC)    
    HANDLE
# elif defined(NNT_MACH)   
    sem_t*
# else    
    sem_t*
# endif    
    _hdl;

};

NNT_BEGIN_NS(tpl)

template <uint N>
class Semaphore
: public ::nnt::core::Semaphore
{
public:
    
    Semaphore()
    : ::nnt::core::Semaphore(N)
    {
        PASS;
    }
    
};

NNT_END_NS

class Task
: public cxx::Object<>
{
    NNTDECL_PRIVATE_CXX(Task);
    NNTDECL_NOCOPY(Task);
    
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
    
    //! run a sample thread.
    typedef void (*thread_func)(void*);
    static bool Run(thread_func, void*);
    
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

NNT_END_NS
NNT_END_HEADER_CXX

# else

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(core)

class Spinlock
{
public:

    class Object
    {
    public:

        Object(Spinlock*);

        void lock();
        void unlock();

    protected:

# ifdef NNT_MSVC
        KIRQL _level;
# endif

        Spinlock* _lock;

        friend class Spinlock;
    };

    Spinlock();
    ~Spinlock();

    Object use();

protected:

# ifdef NNT_MSVC
    KSPIN_LOCK _obj;
# endif

    friend class Object;
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif // user space.
# endif // cxx

# endif
