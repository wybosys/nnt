
# include <wsi/WSIFoundation.h>
# include "DrvSenselockUsbKey.h"

WSI_BEGIN_CXX WSI_BEGIN_NS(senselock)

KeyItem::KeyItem(SENSE4_CONTEXT* ctx)
: _ctx(ctx)
{
    PASS;
}

KeyItem::~KeyItem()
{
    PASS;
}

bool KeyItem::open(uint mode)
{
	uint s4mode = S4_SHARE_MODE;
	switch (mode)
	{
	case MODE_SHARE: s4mode = S4_SHARE_MODE; break;
	case MODE_EXCLUSIZE: s4mode = S4_EXCLUSIZE_MODE; break;
	};

	S4OPENINFO opinfo;
	memset(&opinfo, 0, sizeof(opinfo));
	opinfo.dwS4OpenInfoSize = sizeof(S4OPENINFO);
	opinfo.dwShareMode = s4mode;
	// open
	if (S4_SUCCESS != S4OpenEx(_ctx, &opinfo))
		return false;

	return true;
}

void KeyItem::close()
{
	S4Close(_ctx);
}

bool KeyItem::cd(core::string const& dir)
{
	return S4_SUCCESS == S4ChangeDir(_ctx, dir.c_str());
}

bool KeyItem::verify_pin(core::string const& data, uint mode)
{
	uint s4mode = S4_USER_PIN;
	switch (mode)
	{
	case PIN_USER: s4mode = S4_USER_PIN; break;
	case PIN_DEV: s4mode = S4_DEV_PIN; break;
	case PIN_AUTHEN: s4mode = S4_AUTHEN_PIN; break;
	}

	return S4_SUCCESS == S4VerifyPin(_ctx, (BYTE*)data.c_str(), data.length(), s4mode);
}

bool KeyItem::execute(core::string const& fid, core::data const& cmd, core::data& out, uint mode)
{
	uint s4mode = S4_VM_EXE;
	switch (mode)
	{
	case EXE_VM: s4mode = S4_VM_EXE; break;
	case EXE_XA: s4mode = S4_XA_EXE; break;
	}

	ulong gots = 0;
	ulong sta = S4ExecuteEx(_ctx, fid.c_str(), s4mode, (void*)cmd.bytes(), cmd.size(), (void*)out.bytes(), out.size(), &gots);
	out.set_length(gots);
	return S4_SUCCESS == sta;
}

Standalone::Standalone()
: _ctxs(NULL)
{
	refresh();
}

Standalone::~Standalone()
{
	clear();
}

void Standalone::refresh()
{
	clear();

	ulong _count;
	S4Enum(NULL, &_count);

	if (_count && !(_count % sizeof(SENSE4_CONTEXT)))
	{
		_ctxs = (SENSE4_CONTEXT*)malloc(_count);
		if (S4_SUCCESS != S4Enum(_ctxs, &_count))
		{
			free(_ctxs);
			_ctxs = NULL;
		}

		if (_ctxs)
		{
			_count = _count / sizeof(SENSE4_CONTEXT);
			_items.reserve(_count);
			for (uindex idx = 0; idx < _count; ++idx)
			{
				KeyItem* item = new KeyItem(&_ctxs[idx]);
				_items.push_back(item);
			}
		}
	}
}

usize Standalone::size() const
{
	return _items.size();
}

void Standalone::clear()
{
    if (_ctxs)
    {
        free(_ctxs);
        _ctxs = NULL;
    }
	core::clear_destroy(_items);
}

KeyItem& Standalone::at(uindex idx)
{
	return *_items.at(idx);
}

KeyItem const& Standalone::at(uindex idx) const
{
	return *_items.at(idx);
}

WSI_END_NS WSI_END_CXX
