
# ifndef __WSIWTL_ASSEMBLY_0e053744c9524861bbbb19c009347c78_H_INCLUDED
# define __WSIWTL_ASSEMBLY_0e053744c9524861bbbb19c009347c78_H_INCLUDED

# include "Hardware+WSI.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(wtl)
WSI_BEGIN_NS(wasm)

template <typename cputraits, typename archtraits>
class Registers
{
};

template <>
class Registers <hw::_cpu_intel, arch_x32>
{
public:

	enum 
	{
		EAX = 0,
		EBX = 1,
		ECX = 2,
		EDX = 3,
		EX_COUNT = 4,
	};

	typedef dword EX[EX_COUNT];

};

template <>
class Registers <hw::_cpu_intel, arch_x64>
{
public:
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

	typedef Registers<hw::_cpu_intel, arch_type> Registers;

};

WSI_END_NS
WSI_END_NS
WSI_END_HEADER_CXX

# endif
