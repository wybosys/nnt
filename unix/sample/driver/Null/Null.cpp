
# include <nnt/Foundation+NNT.h>

NNT_BEGIN_C

int null_entry(module_t mod, int event, void* arg)
{
    struct A { void proc() {} };
    A* xx = (A*)0;
    xx->proc();
    return 0;
}

DEV_MODULE(Null, null_entry, NULL);

NNT_END_C
