
# include "Core.h"
# include "Object.h"
# include "Task+NNT.h"

NNT_BEGIN_CXX

# ifdef NNT_DEBUG

// global object counter.
long ::nnt::Object::__global_object_counter = 0;

# endif

::nnt::Object::Object()
{
# ifdef NNT_DEBUG

	NNT_ATOMIC_INC(__global_object_counter);

# endif
}

::nnt::Object::~Object()
{
# ifdef NNT_DEBUG

	NNT_ATOMIC_DEC(__global_object_counter);

# endif
}

# ifdef NNT_USER_SPACE

NNT_BEGIN_NS(cxx)

eventobj_t null_eventobj;

NNT_BEGIN_NS(impl)

class BackgroundTask
	: public core::Task
{
public:

	BackgroundTask(TaskBackground* _task)
		: task(_task)
	{
		safe_grab(task);
	}

	virtual ~BackgroundTask()
	{
		safe_drop(task);
	}

	virtual int main() 
	{
		task->run();
		return 0;
	}

	TaskBackground* task;

};

TaskBackground::TaskBackground()
{
	PASS;
}

TaskBackground::~TaskBackground()
{
	PASS;
}

void TaskBackground::start()
{
	BackgroundTask* task = new BackgroundTask(this);
	task->start();
	task->drop();
}

NNT_END_NS // impl

NNT_END_NS // cxx

# endif // user space.

NNT_END_CXX // nnt

# ifdef NNT_USER_SPACE

NNT_BEGIN_C

bool Drop(::nnt::RefObject* obj)
{
    if (obj)
        return obj->drop();
    return true;
}

void Grab(::nnt::RefObject* obj)
{
    if (obj)
        obj->grab();
}

NNT_END_C

# endif
