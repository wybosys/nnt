
# include "Core.h"
# include "WavParser.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(parser)

class WavChunk
: public Riff::Chunk
{
public:
    
    virtual Chunk* create() const
    {
        return new WavChunk;
    }
    
};

Wav::Wav()
{
    
}

Wav::~Wav()
{
    
}

Riff::Chunk* Wav::create_chunk() const
{
    return new WavChunk;
}

bool Wav::parse(core::data const& da)
{
    if (!Riff::parse(da))
        return false;
    
    static Riff::Identity IDR_WAV("WAVE");
    static Riff::Identity IDR_FMT("fmt ");
    
    if (root.type != IDR_WAV)
        return false;
    
    if (!root.child || root.child->idr != IDR_FMT)
        return false;
    
    byte* d = root.child->data.bytes();
    tag = core::offsets::pop<word>(d);
    channel = core::offsets::pop<word>(d);
    sample_rate = core::offsets::pop<dword>(d);
    abps = core::offsets::pop<dword>(d);
    align = core::offsets::pop<word>(d);
    bps = core::offsets::pop<word>(d);
    additions = (root.child->data.length() == 18) ? core::offsets::pop<word>(d) : 0;
    
    return true;
}

NNT_END_NS
NNT_END_CXX
