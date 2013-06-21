
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

void Wav::load(Chunk const& ck)
{
    static Riff::Identity IDR_WAV("WAVE");
    static Riff::Identity IDR_FMT("fmt ");
    
    if (root.type == IDR_WAV)
    {
        if (root.child || root.child->idr != IDR_FMT)
        {
            byte* d = root.child->data.bytes();
            _tag = core::offsets::pop<word>(d);
            _channel = core::offsets::pop<word>(d);
            _sample_rate = core::offsets::pop<dword>(d);
            _abps = core::offsets::pop<dword>(d);
            _align = core::offsets::pop<word>(d);
            _bps = core::offsets::pop<word>(d);
            _additions = (root.child->data.length() == 18) ? core::offsets::pop<word>(d) : 0;
        }
    }
}

bool Wav::save(core::data &da) const
{
    da.clear();
    
    core::data& d = root.child->data;
    d.clear();
    d.append<word>(_tag);
    d.append<word>(_channel);
    d.append<dword>(_sample_rate);
    d.append<dword>(_abps);
    d.append<word>(_align);
    d.append<word>(_bps);
    if (_additions != 0)
        d.append<word>(_additions);
    
    return Riff::save(da);
}

bool Wav::is_data(Chunk const* ck)
{
    static Riff::Identity IDR_DATA("data");
    return ck->idr == IDR_DATA;
}

void Wav::collect(core::data &da) const
{
    Chunk const* ck = &root;
    while (ck)
    {
        if (is_data(ck))
            da.append(ck->data);
        if (ck->child && is_data(ck->child))
            da.append(ck->child->data);
        ck = ck->next;
    }
}

struct bytes_1_8
{
    byte d;
};

struct bytes_2_8
{
    bytes_1_8 _0;
    bytes_1_8 _1;
};

union bytes_1_16
{
    word d;
    struct
    {
        byte low;
        byte high;
    } v;
};

struct bytes_2_16
{
    bytes_1_16 _0;
    bytes_1_16 _1;
};

template <typename L, typename R>
static void convert(L const& f, R const& t);

static void convert(bytes_1_8 const& f, bytes_2_8& t)
{
    t._0.d = t._1.d = f.d;
}

static void convert(bytes_2_8 const& f, bytes_1_8& t)
{
    t.d = MAX(f._0.d, f._1.d);
}

static void convert(bytes_1_8 const& f, bytes_1_16& t)
{
    t.d = (f.d - 0x80) << 8;
}

static void convert(bytes_1_16 const&f , bytes_2_16& t)
{
    t._0.d = t._1.d = f.d;
}

static void convert(bytes_2_16 const& f, bytes_1_16& t)
{
    t.d = MAX(f._0.d, f._1.d);
}

static void convert(bytes_2_16 const& f, bytes_2_8& t)
{
    t._0.d = (f._0.d >> 8) + 0x80;
    t._1.d = (f._1.d >> 8) + 0x80;
}

static void convert(bytes_1_16 const& f, bytes_1_8& t)
{
    t.d = (f.d >> 8) + 0x80;
}

static void convert(bytes_2_8 const& f, bytes_2_16& t)
{
    t._0.d = (f._0.d - 0x80) << 8;
    t._1.d = (f._1.d - 0x80) << 8;
}

# define update_info \
_abps = _channel * _bps * _sample_rate / 8; \
_align = _bps / 8 * _channel;

void Wav::set_channel(uint ch)
{
    if (_channel == ch)
        return;
    
    Chunk* ck = root.next;
    while (ck)
    {
        if (is_data(ck))
        {
            usize cnt = ck->data.length() / _channel / (_bps / 8); 
            core::data da(cnt * ch * (_bps / 8));
            
            if (_bps == 8)
            {
                if (_channel == 1 && ch == 2)
                {
                    use<bytes_1_8> from = ck->data.bytes();
                    use<bytes_2_8> to = da.bytes();
                    while (cnt--)
                    {
                        convert(*from++, *to++);
                    }
                }
                else if (_channel == 2 && ch == 1)
                {
                    use<bytes_2_8> from = ck->data.bytes();
                    use<bytes_1_8> to = da.bytes();
                    while (cnt--)
                    {
                        convert(*from++, *to++);
                    }
                }
            }
            else if (_bps == 16)
            {
                if (_channel == 1 && ch == 2)
                {
                    use<bytes_1_16> from = ck->data.bytes();
                    use<bytes_2_16> to = da.bytes();
                    while (cnt--)
                    {
                        convert(*from++, *to++);
                    }
                }
                else if (_channel == 2 && ch == 1)
                {
                    use<bytes_2_16> from = ck->data.bytes();
                    use<bytes_1_16> to = da.bytes();
                    while (cnt--)
                    {
                        convert(*from++, *to++);
                    }
                }
            }
            
            ck->data = da;
        }
        
        ck = ck->next;
    }
    
    _channel = ch;
    update_info;
}

void Wav::set_bps(uint bps)
{
    if (_bps == bps)
        return;
    
    Chunk* ck = root.next;
    while (ck)
    {
        if (is_data(ck))
        {
            usize cnt = ck->data.length() / _channel / (_bps / 8);
            core::data da(cnt * _channel * (bps / 8));

            if (_channel == 1)
            {
                if (_bps == 8 && bps == 16)
                {
                    use<bytes_1_8> from = ck->data.bytes();
                    use<bytes_1_16> to = da.bytes();
                    while (cnt--)
                    {
                        convert(*from++, *to++);
                    }
                }
                else if (_bps == 16 && bps == 8)
                {
                    use<bytes_1_16> from = ck->data.bytes();
                    use<bytes_1_8> to = da.bytes();
                    while (cnt--)
                    {
                        convert(*from++, *to++);
                    }
                }
            }
            else if (_channel == 2)
            {
                if (_bps == 8 && bps == 16)
                {
                    use<bytes_2_8> from = ck->data.bytes();
                    use<bytes_2_16> to = da.bytes();
                    while (cnt--)
                    {
                        convert(*from++, *to++);
                    }
                }
                else if (_bps == 16 && bps == 8)
                {
                    use<bytes_2_16> from = ck->data.bytes();
                    use<bytes_2_8> to = da.bytes();
                    while (cnt--)
                    {
                        convert(*from++, *to++);
                    }
                }
            }
            
            ck->data = da;
        }
        
        ck = ck->next;
    }
    
    _bps = bps;
    update_info;
}

NNT_END_NS
NNT_END_CXX
