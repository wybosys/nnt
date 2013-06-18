
# ifndef __NNT_PARSER_WAV_0558BCAE3E0144FEB64B0E6A5DCD107A_H_INCLUDED
# define __NNT_PARSER_WAV_0558BCAE3E0144FEB64B0E6A5DCD107A_H_INCLUDED

# include "RiffParser.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(parser)

class Wav
: public Riff
{
public:
    
    Wav();
    ~Wav();
    
    virtual bool parse(core::data const&);
    virtual bool save(core::data&) const;
    virtual Chunk* create_chunk() const;
    
    void collect(NRESET core::data&) const;
    
    uint channel() const
    {
        return _channel;
    }
    
    uint sample_rate() const
    {
        return _sample_rate;
    }
    
    uint avg_bps() const
    {
        return _abps;
    }
    
    uint bps() const
    {
        return _bps;
    }
    
    static bool is_data(Chunk const*);
    
    void set_channel(uint);
    void set_bps(uint);
    
protected:
    
    uint _tag;
    uint _channel;
    uint _sample_rate;
    uint _abps; // avg bytes per second.
    uint _align;
    uint _bps; // bits per sample.
    uint _additions;
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
