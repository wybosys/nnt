
# ifndef __NNT_PARSER_RIFF_CE3399CA382848CEBD5073135A8B174B_H_INCLUDED
# define __NNT_PARSER_RIFF_CE3399CA382848CEBD5073135A8B174B_H_INCLUDED

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(parser)

class Riff
: public cxx::Object<>
{
public:
    
    class Identity
    {
    public:
        
        Identity(dword);
        Identity(char const*);
        
        operator dword () const
        {
            return _idr;
        }
        
        operator core::string () const;
        
    protected:
        
        dword _idr;
        
    };
    
    class Chunk
    : public VirObject
    {
    public:
        
        Chunk();
        ~Chunk();
        
        void clear();
        void remove();
        
        Chunk* prev;
        Chunk* next;
        
        virtual bool read(void**);
        virtual bool save();
        virtual void fill(void*, usize);
        virtual Chunk* create() const;
        
        dword idr, type;
        core::data data;
        Chunk* child;
        
    };
    
    Riff();
    ~Riff();
    
    virtual bool parse(core::data const&);
    virtual bool save(RESET core::data&) const;
    virtual Chunk* create_chunk() const;
    
    Chunk root;
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
