
# include "Core.h"
# include "Object.h"
# include "Task+WSI.h"

WSI_BEGIN_CXX

// global object counter.
long ::wsi::Object::__global_object_counter = 0;

::wsi::Object::Object()
{
# ifdef WSI_DEBUG

	WSI_ATOMIC_INC(__global_object_counter);

# endif
}

::wsi::Object::~Object()
{
# ifdef WSI_DEBUG

	WSI_ATOMIC_DEC(__global_object_counter);

# endif
}

WSI_BEGIN_NS(cxx)

// empty event object.
eventobj_t null_eventobj;

WSI_BEGIN_NS(impl)

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

WSI_END_NS // impl

WSI_END_NS // cxx

WSI_END_CXX // wsi

WSI_BEGIN_C

bool Drop(::wsi::RefObject* obj)
{
    if (obj)
        return obj->drop();
    return true;
}

void Grab(::wsi::RefObject* obj)
{
    if (obj)
        obj->grab();
}

WSI_END_C
