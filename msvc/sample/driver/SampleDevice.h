
# ifndef SAMPLE_DEVICE
# define SAMPLE_DEVICE

# include <nnt/Kernel/DriverApp.h>

# ifdef NNT_KERNEL_SPACE

NNTAPP_BEGIN

class Sample
    : public driver::App
{
public:

    Sample();
    ~Sample();

    int main();

};

NNTAPP_END

# endif

# endif
