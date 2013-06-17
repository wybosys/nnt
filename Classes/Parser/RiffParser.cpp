
# include "Core.h"
# include "RiffParser.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(parser)

Riff::Riff()
{
    
}

Riff::~Riff()
{
    root.clear();
}

Riff::Chunk::Chunk()
: next(NULL), prev(NULL)
{
    
}

Riff::Chunk::~Chunk()
{

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

Riff::Chunk* Riff::Chunk::add()
{
    next = new Chunk;
    return next;
}

bool Riff::parse(core::data const& da)
{
    byte* d = da.bytes();
    byte* de = d + da.length();
    Chunk* ck = &root;
    while (d < de)
    {
        ck->idr = core::offsets::pop<dword>(d);
        usize sz = core::offsets::pop<dword>(d);
        ck->data.resize(sz);
        ck->data.copy(core::offsets::preoff(d, sz), sz);
        if (d < de)
            ck = ck->add();
    }
    return true;
}

NNT_END_NS
NNT_END_CXX
