# ifndef __WSI_DRIVER_SENSELOCKUSBKEY_7A1631EDE8E84F9388C09F4772DEEA02_H_INCLUDED
# define __WSI_DRIVER_SENSELOCKUSBKEY_7A1631EDE8E84F9388C09F4772DEEA02_H_INCLUDED

WSI_BEGIN_HEADER_C

# include <sense4.h>

WSI_END_HEADER_C

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX WSI_BEGIN_NS(senselock)

enum {
	MODE_EXCLUSIZE,
	MODE_SHARE,
	PIN_USER,
	PIN_DEV,
	PIN_AUTHEN,
	EXE_VM,
	EXE_XA,
};

class KeyItem
{
public:
	KeyItem(SENSE4_CONTEXT* ctx);
	~KeyItem();

public:
	//! open device.
	bool open(uint mode);

	//! cd.
	bool cd(core::string const&);

	//! verify pin.
	bool verify_pin(core::string const&, uint mode);

	//! execute.
	bool execute(core::string const& fid, core::data const& cmd, core::data& out, uint mode);

	//! close.
	void close();

protected:
	SENSE4_CONTEXT* _ctx;
};

class Standalone
{
public:
	Standalone();
	~Standalone();

public:

	//! size.
	usize size() const;

	//! refresh.
	void refresh();

	//! clear.
	void clear();

	//! at.
	KeyItem& at(uindex);
	KeyItem const& at(uindex) const;

protected:
	core::vector<KeyItem*> _items;
    SENSE4_CONTEXT* _ctxs;
};

WSI_END_NS WSI_END_HEADER_CXX

# endif

# endif
