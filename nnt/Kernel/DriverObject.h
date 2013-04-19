
# ifndef __NNT_KERNEL_DRIVEROBJECT_bed49de42d8e481ea9bca62581254b12_H_INCLUDED
# define __NNT_KERNEL_DRIVEROBJECT_bed49de42d8e481ea9bca62581254b12_H_INCLUDED
 
NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(driver)

class Status
{
public:

    static bool Success(int);
    static bool Failed(int);

};

class Object
    : public ::nnt::Object
{

};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
