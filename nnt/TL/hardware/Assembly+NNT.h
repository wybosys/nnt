
# ifndef __NNTWTL_ASSEMBLY_0e053744c9524861bbbb19c009347c78_H_INCLUDED
# define __NNTWTL_ASSEMBLY_0e053744c9524861bbbb19c009347c78_H_INCLUDED

# include "Hardware+NNT.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ntl)
NNT_BEGIN_NS(nasm)

template <typename cputraits, typename archtraits>
class Registers
{
};

template <typename cputraits>
class Registers <cputraits, arch_x32>
{
public:
    
    udword eax, ebx, ecx, edx, esp, ebp;

};

template <typename cputraits>
class Registers <cputraits, arch_x64>
{
public:
    
    uqword rax, rbx, rcx, rdx, rsp, rbp;
    
};

template <typename cputraits>
class Opcode
{
};

template <>
class Opcode <hw::_cpu_intel>
	: public Opcode <hw::_cpu_unknown>
{
public:

};

NNT_END_NS
NNT_END_NS
NNT_END_HEADER_CXX

# endif
