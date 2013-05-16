
# include "Core.h"
# include "Task+NNT.h"

NNT_BEGIN_CXX 
NNT_BEGIN_NS(core)
  
# ifdef NNT_USER_SPACE

Mutex::Mutex()
{
# ifdef NNT_MSVC
    
    _hdl = ::CreateMutex(NULL, FALSE, NULL);
    
# else

    pthread_mutex_init(&_hdl, NULL);
    
# endif
}

Mutex::~Mutex()
{
# ifdef NNT_MSVC
    
    ::CloseHandle(_hdl);
    
# else
    
    pthread_mutex_destroy(&_hdl);
    
# endif
}

void Mutex::lock()
{
# ifdef NNT_MSVC
    
    ::WaitForSingleObject(_hdl, INFINITE);
    
# else
    
# ifdef NNT_DEBUG

    int sta = pthread_mutex_lock(&_hdl);
    if (sta != 0)
      trace_msg("failed to lock mutex.");

# else

    pthread_mutex_lock(&_hdl);

# endif
    
# endif
}

void Mutex::unlock()
{
# ifdef NNT_MSVC
    
    ::ReleaseMutex(_hdl);
    
# else
    
# ifdef NNT_DEBUG

	int sta = pthread_mutex_unlock(&_hdl);
	if (sta != 0)
		trace_msg("failed to unlock mutex.");

# else

    pthread_mutex_unlock(&_hdl);

# endif
    
# endif    
}

bool Mutex::try_lock()
{
# ifdef NNT_MSVC
    
    DWORD ret = ::WaitForSingleObject(_hdl, 0);
    return WAIT_OBJECT_0 == ret;
    
# else
    
    int ret = pthread_mutex_trylock(&_hdl);
    return ret == 0;
    
# endif
}

Condition::Condition()
{
# ifdef NNT_MSVC

	_hdl = ::CreateEvent(NULL, FALSE, FALSE, NULL);

# else
    
    pthread_cond_init(&_hdl, NULL);    
    pthread_mutex_init(&_mtx, NULL);
    
# endif
}

Condition::~Condition()
{
# ifdef NNT_MSVC

	::CloseHandle(_hdl);

# else
    
    pthread_cond_destroy(&_hdl);
    pthread_mutex_destroy(&_mtx);
    
# endif
}

void Condition::wait()
{
# ifdef NNT_MSVC

	::WaitForSingleObject(_hdl, INFINITE);

# else
    
    pthread_mutex_lock(&_mtx);
    pthread_cond_wait(&_hdl, &_mtx);
    pthread_mutex_unlock(&_mtx);
    
# endif
}

void Condition::signal()
{
# ifdef NNT_MSVC

	::SetEvent(_hdl);

# else
    
    pthread_cond_signal(&_hdl);
    
# endif
}

Semaphore::Semaphore(uint cnt)
{
# if defined(NNT_MSVC)
    
# elif defined(NNT_MACH)
    
    static int _gs_sem_id = 0;
    char buf[64];
    snprintf(buf, sizeof(buf), "__nnt_core_semaphore_default_%d", ++_gs_sem_id);
    _hdl = sem_open(buf, O_CREAT|O_EXCL, cnt);
    if (_hdl == SEM_FAILED)
    {        
        trace_msg("failed to create seamphore.");
    }

# endif
}

Semaphore::~Semaphore()
{
# if defined(NNT_MSVC)
# elif defined(NNT_MACH)
    
    sem_close(_hdl);
    sem_destroy(_hdl);
    
# endif
}

void Semaphore::lock()
{
# if defined(NNT_MSVC)
# elif defined(NNT_MACH)
    
    int sta = sem_wait(_hdl);
    if (sta != 0)
    {
        trace_msg("failed to lock semaphore.");
    }
    
# endif
}

void Semaphore::unlock()
{
# if defined(NNT_MSVC)
# elif defined(NNT_MACH)
    
    int sta = sem_post(_hdl);
    if (sta != 0)
    {
        trace_msg("failed to unlock semaphore.");
    }
    
# endif
}

NNTDECL_PRIVATE_BEGIN_CXX(Task)

void init()
{
    hdl_thd = 0;
    frun = 0;
    complete = false;    
    d_owner->count = 1;
}

void dealloc()
{
    d_owner->complete();    
	this->wait();
}

owner_type::func_run frun;
uint count;
bool complete;

int run_once()
{
    mtx_run.lock();
    
    int ret = 0;
    if (frun)
        ret = (*frun)(d_owner);
    if (ret)
    {
        mtx_run.unlock();
        return ret;
    }
    
    ret = d_owner->main();
    if (ret)
    {
        mtx_run.unlock();
        return ret;
    }
    
    mtx_run.unlock();
    return ret;
}

# ifdef NNT_MSVC

HANDLE hdl_thd;

# else

pthread_t hdl_thd;

# endif

Mutex mtx_ctl, mtx_run;

# ifdef NNT_MSVC
friend DWORD WINAPI wrapper_thd(LPVOID);
static DWORD WINAPI wrapper_thd(LPVOID data)
# else
friend void* wrapper_thd(void*);
static void* wrapper_thd(void* data)
# endif
{
    owner_type* d_owner = (owner_type*)data;
    
    if (d_owner->count != -1)
    {
        d_owner->d_ptr->count = d_owner->count;
        
        while (!d_owner->d_ptr->complete &&
               d_owner->d_ptr->count--)
        {
            d_owner->d_ptr->mtx_ctl.lock();
            
            if (d_owner->d_ptr->run_once())
                d_owner->d_ptr->complete = true;
            
            d_owner->d_ptr->mtx_ctl.unlock();
        }
    }
    else
    {
        while (!d_owner->d_ptr->complete)
        {
            d_owner->d_ptr->mtx_ctl.lock();
            
            if (d_owner->d_ptr->run_once())
                d_owner->d_ptr->complete = true;
            
            d_owner->d_ptr->mtx_ctl.unlock();
        }
    }
    
    d_owner->drop();
    
    trace_msg("task's thread is exited.");
    
    return NULL;
}

bool start()
{
    d_owner->grab();
    complete = false;
    
# ifdef NNT_MSVC
    
    hdl_thd = ::CreateThread(NULL, 0, wrapper_thd, d_owner, 0, NULL);
    return hdl_thd != NULL;
    
# else
    
    int ret = pthread_create(&hdl_thd, NULL, wrapper_thd, d_owner);
    return ret == 0;
    
# endif
}

void wait()
{
# ifdef NNT_MSVC
# else
    pthread_join(hdl_thd, NULL);
# endif
}

NNTDECL_PRIVATE_END_CXX

Task::Task()
{
    NNTDECL_PRIVATE_CONSTRUCT(Task);
}

Task::~Task()
{
    NNTDECL_PRIVATE_DESTROY();
}

void Task::wait()
{
    d_ptr->wait();
}

bool Task::start(func_run func)
{
    if (d_ptr->hdl_thd)
        return false;
    d_ptr->frun = func;
    return d_ptr->start();
}

bool Task::start()
{
    if (d_ptr->hdl_thd)
        return false;
    return d_ptr->start();
}

void Task::infinite()
{
    count = -1;
}

void Task::stop()
{
    d_ptr->complete = true;
}

bool Task::complete() const
{
    return d_ptr->complete;
}

void Task::suspend()
{
    d_ptr->mtx_ctl.lock();
}

void Task::resume()
{
    d_ptr->mtx_ctl.unlock();
}

# else // kernel space.

Spinlock::Spinlock()
{

}

Spinlock::~Spinlock()
{

}

Spinlock::Object::Object(Spinlock* _spin)
: _lock(_spin)
{

}

void Spinlock::Object::lock()
{
# ifdef NNT_MSVC
    KeAcquireSpinLock(&_lock->_obj, &_level);
# endif
}

void Spinlock::Object::unlock()
{
# ifdef NNT_MSVC
    KeReleaseSpinLock(&_lock->_obj, _level);
# endif
}

Spinlock::Object Spinlock::use()
{
    return Spinlock::Object(this);
}

# endif // user space.

NNT_END_NS 
NNT_END_CXX
