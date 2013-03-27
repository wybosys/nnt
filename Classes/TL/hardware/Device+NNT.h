
# ifndef __NNTWTL_DEVICE_cc8a97edbee54b2ab1253be376a75a72_H_INCLUDED
# define __NNTWTL_DEVICE_cc8a97edbee54b2ab1253be376a75a72_H_INCLUDED

# include "Cpu+NNT.h"

# ifdef NNT_WINDOWS

#   include "../MSCOM+NNT.h"

# endif

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ntl)
NNT_BEGIN_NS(dev)

template <typename ostraits = os_type>
class Bios
{

};

# ifdef NNT_MSVC

template <>
class Bios<os_windows>
	: public Bios<os_unknown>
{
public:

	Bios()
	{
		_obj = _wbem.query();
	}

	~Bios()
	{
		PASS;
	}

	core::string name()
	{
		return _obj.name<core::string>();
	}

	core::string serialno()
	{
		return _obj.id_code<core::string>();
	}

	core::string manufacturer()
	{
		return _obj.manufacturer<core::string>();
	}

	bool is_null() const
	{
		return _obj.is_null();
	}

protected:

	windows::wbem::Bios _wbem;
	windows::wbem::Bios::iterator _obj;	

};

template <typename ostraits = os_type>
class Mainboard
{

};

template <>
class Mainboard<os_windows>
	: public Mainboard<os_unknown>
{
public:

	Mainboard()
	{		
		_obj = _wbem.query();
	}

	bool is_null() const
	{
		return _obj.is_null();
	}

	core::string serialno()
	{		
		return _obj.serialnumber<core::string>();
	}

protected:

	windows::wbem::BaseBoard _wbem;
	windows::wbem::BaseBoard::iterator _obj;

};

template <typename ostraits = os_type>
class Disk
{

};

template <>
class Disk<os_windows>
	: public Disk<os_unknown>
{
public:

	Disk()
	{
		_obj = _wbem.query();
	}

	bool is_null() const
	{
		return _obj.is_null();
	}

	core::string serialno() const
	{
		return _obj.serialnumber<core::string>();
	}

	core::string deviceid() const
	{
		return _obj.id<core::string>();
	}

	uint signature() const
	{
		return _obj.signature();
	}

protected:

	windows::wbem::PhysicalDisk _wbem;
	windows::wbem::PhysicalDisk::iterator _obj;

};

template <typename ostraits = os_type>
class Memory
{

};

template <>
class Memory<os_windows>
	: public Memory<os_unknown>
{
public:

	Memory()
	{
		_obj = _wbem.query();
	}

	bool is_null() const
	{
		return _obj.is_null();
	}

	core::string banklabel()
	{
		return _obj.bandlabel<core::string>();
	}

protected:

	windows::wbem::PhysicalMemory _wbem;
	windows::wbem::PhysicalMemory::iterator _obj;

};

# endif

NNT_END_NS
NNT_END_NS
NNT_END_HEADER_CXX

# endif
