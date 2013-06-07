
# include "Core.h"
# include "mongoose+python.h"

# include "../../Classes/Script/_python.site/nnt.modules.h"
# include "../../Classes/Script/_python.site/pynnt.h"

NNT_BEGIN_CXX


NNT_END_CXX

NNT_BEGIN_C

// copy from mongoose.c, duplicate.
struct file {
    int is_directory;
    time_t modification_time;
    int64_t size;
    FILE *fp;
    const char *membuf;   // Non-NULL if file data is in memory
};

void handle_py_request(struct mg_connection *conn, const char *path, struct file *filep)
{
    
}

NNT_END_C
