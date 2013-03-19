
# ifndef __WSIWTL_MSCOM_5997ac7319de49b6b38720fbbab2c3e1_H_INCLUDED
# define __WSIWTL_MSCOM_5997ac7319de49b6b38720fbbab2c3e1_H_INCLUDED

#   define _WIN32_DCOM

#   include <comdef.h>
#   include <atlbase.h>
#   include <atlcom.h>
#   include <atlstr.h>

#   include <Wbemidl.h>
#   pragma comment(lib, "wbemuuid.lib")

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(wtl)

# ifdef WSI_WINDOWS

template <>
inline_impl int type_cast<int, VARIANT>(VARIANT const& var)
{
	return var.intVal;
}

template <>
inline_impl uint type_cast<uint, VARIANT>(VARIANT const& var)
{
	return var.uintVal;
}

template <>
inline_impl core::string type_cast<core::string, VARIANT>(VARIANT const& var)
{
	return (core::string)(_bstr_t)var;
}

# endif

WSI_BEGIN_NS(windows)

template <LONG ComInitializeFlag>
class ComObject
{
public:

	ComObject()
	{
		_Init();
	}

	~ComObject()
	{
		_Fin();
	}

	static core::string ToStr(VARIANT const& var)
	{
		return "";
	}

protected:

	void _Init()
	{
		::CoInitializeEx(NULL, ComInitializeFlag);
	}

	void _Fin()
	{
		::CoUninitialize();
	}

};

template <typename implT>
class WbemIterator 
{
public:

	WbemIterator()
	{
		PASS;
	}

	WbemIterator(WbemIterator& r)
		: _enum(r._enum), _object(r._object)
	{
		PASS;
	}

	~WbemIterator()
	{
		clear();
	}

	static WbemIterator const& Null()
	{
		static const WbemIterator ze;
		return ze;
	}

	WbemIterator& operator = (WbemIterator& r)
	{
		_enum = r._enum;
		_object = r._object;
		return *this;
	}

	bool is_null() const
	{
		return _enum == NULL;
	}

	void clear()
	{
		_enum = NULL;
		_object = NULL;
	}

	implT& operator ++ ()
	{
		ULONG ret;
		_object = NULL;
		_enum->Next(WBEM_INFINITE, 1, &_object, &ret);
		if (ret == 0)
			_enum = NULL;
		return *(implT*)this;
	}

	template <typename retT>
	retT value(WCHAR const* nm, retT const& null, uint vt) const
	{
		VARIANT var;
		_object->Get(nm, NULL, &var, NULL, NULL);
		if (var.vt != vt)
			return null;
		return wtl::type_cast<retT>(var);
	}

	template <typename retT>
	retT string(WCHAR const* nm) const
	{
		VARIANT var;
		_object->Get(nm, NULL, &var, NULL, NULL);
		if (var.vt != VT_BSTR)
			return retT();
		return (retT)(bstr_t)var;
	}

	void date(WCHAR const* nm) const
	{
		VARIANT var;
		_object->Get(nm, NULL, &var, NULL, NULL);
		if (var.vt != VT_DATE)
			return;
	}

protected:

	CComPtr<IEnumWbemClassObject> _enum;
	CComPtr<IWbemClassObject> _object;

	friend class WbemObject;
};

class WbemObject
	: public ComObject<COINIT_MULTITHREADED>
{
public:

	WbemObject()
	{
		HRESULT res;

		// set security.
		res = ::CoInitializeSecurity(
			NULL,
			-1,
			NULL,
			NULL,
			RPC_C_AUTHN_LEVEL_DEFAULT,
			RPC_C_IMP_LEVEL_IMPERSONATE,
			NULL,
			EOAC_NONE,
			NULL
			);
		_throw(res, "failed to initialize COM's security.");

		// create WMI locator.
		res = ::CoCreateInstance(
			CLSID_WbemLocator,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWbemLocator,
			(LPVOID*)&_loc
			);
		_throw(res, "failed to instance wbem locator.");

		// connect to WMI server.
		res = _loc->ConnectServer(
			bstr_t(L"ROOT\\CIMV2"),
			NULL,
			NULL,
			0,
			NULL,
			0,
			0,
			&_svc
			);
		_throw(res, "failed to connect to WMI service.");

		// set service's security.
		res = ::CoSetProxyBlanket(
			_svc,
			RPC_C_AUTHN_WINNT,
			RPC_C_AUTHN_NONE,
			NULL,
			RPC_C_AUTHN_LEVEL_CALL,
			RPC_C_IMP_LEVEL_IMPERSONATE,
			NULL,
			EOAC_NONE
			);
		_throw(res, "failed to set security for WMI service.");
	}

	~WbemObject()
	{
		PASS;
	}

	typedef bstr_t query_string;

	template <typename IteratorT>
	IteratorT query(query_string const& cmd)
	{
		IteratorT ret;
		HRESULT res = _svc->ExecQuery(
			bstr_t("WQL"),
			cmd,
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			NULL,
			&ret._enum
			);
		if (FAILED(res))
			return ret;

		// seek to begin.
		return ++ret;
	}

protected:

	void _throw(HRESULT res, core::string const& msg)
	{
		if (FAILED(res))
		{
			_clear();
			_Fin();
			throw exception::message(msg);
		}
	}

	void _clear()
	{
		_loc = NULL;
		_svc = NULL;
	}

	CComPtr<IWbemLocator> _loc;
	CComPtr<IWbemServices> _svc;

};

WSI_BEGIN_NS(wbem)

template <typename baseT>
class SoftwareIterator
	: public baseT
{
public:

	template <typename valT>
	valT manufacturer() const
	{
		return string<valT>(L"Manufacturer");
	}

	template <typename valT>
	valT buildnumber() const
	{
		return string<valT>(L"BuildNumber");
	}

};

template <typename baseT>
class PhysicalIterator
	: public baseT
{
public:

	template <typename valT>
	valT serialnumber() const
	{
		return string<valT>(L"SerialNumber");
	}

	template <typename valT>
	valT sku() const
	{
		return string<valT>(L"SKU");
	}

	template <typename valT>
	valT manufacturer() const
	{
		return string<valT>(L"Manufacturer");
	}

};

template <
typename implT,
typename baseT = WbemIterator<implT>
>
class Iterator
	: public baseT
{

public:

	template <typename valT>
	valT name() const
	{
		return string<valT>(L"Name");
	}

	template <typename valT>
	valT description() const
	{
		return string<valT>(L"Description");
	}

	template <typename valT>
	valT caption() const
	{
		return string<valT>(L"Caption");
	}

};

class OperatorSystem
	: public WbemObject
{
public:

	class iterator
		: public SoftwareIterator<Iterator<iterator> >
	{
	};

	iterator query()
	{
		return WbemObject::query<iterator>(query_string("SELECT * FROM Win32_OperatingSystem"));
	}

};

class Bios
	: public WbemObject
{
public:

	class iterator
		: public SoftwareIterator<Iterator<iterator> >
	{
	public:

		template <typename valT>
		valT id_code() const
		{
			return string<valT>(L"IdentificationCode");
		}

		template <typename valT>
		valT version() const
		{
			return string<valT>(L"SMBIOSBIOSVersion");
		}

	};

	iterator query()
	{
		return WbemObject::query<iterator>(query_string("SELECT * from Win32_BIOS"));
	}

};

class BaseBoard
	: public WbemObject
{
public:

	class iterator
		: public PhysicalIterator<Iterator<iterator> >
	{
	public:

	};

	iterator query()
	{
		return WbemObject::query<iterator>(query_string("SELECT * from Win32_BaseBoard"));
	}

};

class PhysicalDisk
	: public WbemObject
{
public:

	class iterator 
		: public PhysicalIterator<Iterator<iterator> >
	{
	public:

		template <typename valT>
		valT id() const
		{
			return string<valT>(L"DeviceID");
		}

		uint signature() const
		{
			return value<uint>(L"Signature", -1, VT_I4);
		}

	};

	iterator query()
	{
		return WbemObject::query<iterator>(query_string("SELECT * from Win32_DiskDrive"));
	}

};

class PhysicalMemory
	: public WbemObject
{
public:

	class iterator
		: public PhysicalIterator<Iterator<iterator> >
	{
	public:

		template <typename valT>
		valT bandlabel() const
		{
			return string<valT>(L"BankLabel");
		}

	};

	iterator query()
	{
		return WbemObject::query<iterator>(query_string("SELECT * from Win32_PhysicalMemory"));
	}

};

WSI_END_NS // end wbem

WSI_END_NS
WSI_END_NS
WSI_END_HEADER_CXX

# endif
