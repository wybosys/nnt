
# include "wsi/WSIFoundation.h"
# include "TestTask.h"
# include "wsi/Core/Task+WSI.h"

WSIAPP_BEGIN

class ATask
: public ::wsi::core::Task
{
    virtual int main()
    {
        std::cout << val++ << std::endl;
        sleep(1);
        return 0;
    }
    
    int val;
};

void TestTask::main()
{
    ATask* task = new ATask;
    task->infinite();
    task->start();
    task->drop();
    
    sleep(5);
}

WSIAPP_END