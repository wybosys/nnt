
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
    virtual Chunk* create_chunk() const;
    
    uint tag;
    uint channel;
    uint sample_rate;
    uint abps; // avg bytes per second.
    uint align;
    uint bps; // bits per sample.
    uint additions;
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
