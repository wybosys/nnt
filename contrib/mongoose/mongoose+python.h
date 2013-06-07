
# ifndef __NNT_MONGOOSE_PYTHON_7F2348F1DCBA4F5AB748F380A8A1AD5C_H_INCLUDED
# define __NNT_MONGOOSE_PYTHON_7F2348F1DCBA4F5AB748F380A8A1AD5C_H_INCLUDED

NNT_BEGIN_HEADER_C

# include "mongoose.h"

# define NNT_MONGOOSE_PYTHON 1

struct file;

extern void handle_py_request(struct mg_connection *conn, const char *path, struct file *filep);

NNT_END_HEADER_C

# endif
