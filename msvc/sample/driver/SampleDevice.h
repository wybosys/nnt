
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

class SampleWrite
    : public driver::feature::Write
{
public:

    SampleWrite();

    void main();

    pmp_begin(SampleWrite);
    pmp_end;
};

class SampleRead
    : public driver::feature::Read
{
public:

    SampleRead();

    void main();

    pmp_begin(SampleRead);
    pmp_end;
};

NNTAPP_END

# endif

# endif
