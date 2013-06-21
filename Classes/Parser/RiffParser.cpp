
# include "Core.h"
# include "RiffParser.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(parser)

Riff::Identity::Identity(dword v)
: _idr(v)
{
    
}

Riff::Identity::Identity(char const* s)
: _idr(0)
{
    usize len = strlen(s);
    len = (len < 5) ? len : 4;
    memcpy(&_idr, s, len);
}

Riff::Identity::operator core::string () const
{
    return core::string((char*)&_idr, 4);
}

Riff::Riff()
{
    
}

Riff::~Riff()
{
    root.clear();
}

Riff::Chunk::Chunk()
: next(NULL), prev(NULL), child(NULL)
{
    
}

Riff::Chunk::~Chunk()
{
    safe_delete(child);
}

void Riff::Chunk::clear()
{
    safe_delete(next);
}

void Riff::Chunk::remove()
{
    if (next)
        next->prev = prev;
    if (prev)
        prev->next = next;
}

Riff::Chunk* Riff::Chunk::create() const
{
    return new Chunk;
}

bool Riff::Chunk::save()
{
    return true;
}

bool Riff::Chunk::read(void **d)
{
    idr = core::offsets::pop<dword>(*d);
    usize sz = core::offsets::pop<dword>(*d);
    
    static Riff::Identity RIFF("RIFF");
    static Riff::Identity LIST("LIST");
    
# ifdef NNT_DEBUG
    core::string idrname = Riff::Identity(idr);
# endif
    
    if (idr == RIFF)
    {
        type = core::offsets::pop<dword>(*d);
        sz -= 4;
        
        child = create();
        child->read(d);
    }
    else if (idr == LIST)
    {
        type = core::offsets::pop<dword>(*d);
        sz -= 4;
    }
    else
    {        
        type = 0;
        
        fill(*d, sz);
        core::offsets::offset(*d, sz);
    }
    
    return true;
}

void Riff::Chunk::fill(void *d, usize sz)
{
    data.resize(sz);
    data.copy(d, sz);
}

bool Riff::parse(core::data const& da)
{    
    byte* d = da.bytes();
    byte* de = d + da.length();
    Chunk* ck = &root;
    while (d < de)
    {
        if (!ck->read((void**)&d))
            return false;
        
        load(*ck);
        
        if (d < de)
        {
            ck->next = create_chunk();
            ck->next->prev = ck;
            ck = ck->next;
        }
    }
    return true;
}

void Riff::load(Chunk const&)
{
    PASS;
}

bool Riff::save(core::data& da) const
{
    Chunk const* ck = &root;
    while (ck)
    {
        static Riff::Identity RIFF("RIFF");
        static Riff::Identity LIST("LIST");
        
        if (!core::down_const(ck)->save())
            return false;
        
        da.append(ck->idr);
        
        core::data tmp;
        
        if (ck->idr == RIFF)
        {
            if (!core::down_const(ck->child)->save())
                return false;
            
            tmp.append(ck->type);
            tmp.append(ck->child->idr);
            tmp.append<dword>(ck->child->data.length());
            tmp.append(ck->child->data);
        }
        else if (ck->idr == LIST)
        {
            tmp.append(ck->child->idr);
            tmp.append<dword>(ck->child->data.length() + 4);
        }
        else
        {
            tmp.append<dword>(ck->data.length());
            tmp.append(ck->data);
        }
        
        da.append<dword>(tmp.length());
        da.append(tmp);
        
        ck = ck->next;
    }
    return true;
}

Riff::Chunk* Riff::create_chunk() const
{
    return new Riff::Chunk;
}

NNT_END_NS
NNT_END_CXX
