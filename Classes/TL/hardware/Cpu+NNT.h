
# ifndef __NNTWTL_CPU_3ffe14fd59e2497bb1f47f4aaf283182_H_INCLUDED
# define __NNTWTL_CPU_3ffe14fd59e2497bb1f47f4aaf283182_H_INCLUDED

# include "Hardware+NNT.h"
# include "Assembly+NNT.h"
# include "../../Mach/cpu.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ntl)
NNT_BEGIN_NS(cpu)

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

	typedef nasm::Opcode<hw::_cpu_intel> Opcode;

	Info()
	{
		PASS;
	}
    
	core::string vid()
	{
        mregister mr;
        cpuid(0, &mr);

		core::data buf;
		buf.append(mr.bx);
		buf.append(mr.dx);
		buf.append(mr.cx);

		return core::type_cast<core::string>(buf);
	}

	core::data serialno()
	{        
		core::data buf;
        mregister mr;
        cpuid(1, &mr);
        // support no. feature.
        if (bit_at(mr.dx, 18) == 0)
            return buf;

        cpuid(3, &mr);
		
		buf.append(mr.ax);
		buf.append(mr.cx);
		buf.append(mr.dx);

		return buf;
	}	

};

NNT_END_NS
NNT_END_NS
NNT_END_HEADER_CXX

# endif
