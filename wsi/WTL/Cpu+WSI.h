
# ifndef __WSIWTL_CPU_3ffe14fd59e2497bb1f47f4aaf283182_H_INCLUDED
# define __WSIWTL_CPU_3ffe14fd59e2497bb1f47f4aaf283182_H_INCLUDED

# include "Hardware+WSI.h"
# include "Assembly+WSI.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(wtl)
WSI_BEGIN_NS(cpu)

template <typename _cpuT>
struct _info_traits
{
	typedef hw::_cpu_intel type;
};

template <>
struct _info_traits<arch_arm>
{
	typedef hw::_cpu_arm type;
};

template <>
struct _info_traits<arch_unknown>
{
	typedef hw::_cpu_unknown type;
};

template <typename infotraits = _info_traits<arch_type>::type >
class Info
{
public:
};

template <>
class Info <hw::_cpu_intel>
	: public Info <hw::_cpu_unknown>
{
public:

	typedef wasm::Opcode<hw::_cpu_intel> Opcode;

	Info()
	{
		PASS;
	}

	bool has_brandstring()
	{
		bool b;
		WSIASM_BEGIN;
		mov eax, 80000000h;
		cpuid;
		cmp eax, 80000004h;
		jb UNSUPPORT;
		mov byte ptr [b], 1h;
		jmp END;
UNSUPPORT:
		mov byte ptr [b], 0h;
END:
		nop;
		WSIASM_END;
		return b;
	}

	core::string vid()
	{
		dword b, c, d;

		WSIASM_BEGIN;
		mov eax, 0h;
		cpuid;
		mov b, ebx;
		mov c, ecx;
		mov d, edx;
		WSIASM_END;

		core::data buf;
		buf.append(&b, 4);
		buf.append(&d, 4);
		buf.append(&c, 4);

		return core::type_cast<core::string>(buf);
	}

	core::data serialno()
	{
		dword a, c, d;
		core::data buf;

		WSIASM_BEGIN;
		mov eax, 1h;
		cpuid;
		mov d, edx;
		mov a, eax;
		WSIASM_END;

		// unsupport.
		if (bit_at(d, 18) == 0)
			return buf;

		// support.
		WSIASM_BEGIN;
		mov eax, 03h;
		cpuid;
		mov c, ecx;
		mov d, edx;
		WSIASM_END;
		
		buf.append(&a, 8);
		buf.append(&c, 8);
		buf.append(&d, 8);

		return buf;
	}
	

};

WSI_END_NS
WSI_END_NS
WSI_END_HEADER_CXX

# endif