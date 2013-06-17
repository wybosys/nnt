
# ifndef __NNT_PARSER_RIFF_CE3399CA382848CEBD5073135A8B174B_H_INCLUDED
# define __NNT_PARSER_RIFF_CE3399CA382848CEBD5073135A8B174B_H_INCLUDED

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(parser)

class Riff
{
public:
    
    class Chunk
    {
    public:
        
        Chunk();
        ~Chunk();
        
        void clear();
        void remove();
        Chunk* add();
        
        Chunk* prev;
        Chunk* next;
        
        dword idr;
        core::data data;
    };
    
    Riff();
    ~Riff();
    
    bool parse(core::data const&);
    
    Chunk root;
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
