
# include <nnt/Foundation+NNT.h>

NNT_BEGIN_CXX

NNTDECL_PRIVATE_HEAD(CA);

NNTDECL_PRIVATE_BEGIN(CA)

void init()
{
}

void dealloc()
{
}

NNTDECL_PRIVATE_END

class CA
{
public:

    NNTDECL_PRIVATE(CA);

    CA()
        {
            NNTDECL_PRIVATE_CONSTRUCT(CA);
        }

    ~CA()
        {
            NNTDECL_PRIVATE_DESTROY();
        }

    void proc()
        {
            int a = 10;
            a += 12;
        }
    
};


NNT_END_CXX

NNT_BEGIN_C

int null_entry(module_t mod, int event, void* arg)
{
    ::nnt::CA a;
    a.proc();
    ::nnt::CA* ptr = new ::nnt::CA;
    ptr->proc();
    return 0;
}

DEV_MODULE(Null, null_entry, NULL);

NNT_END_C
