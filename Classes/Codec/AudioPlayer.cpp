
# include "Core.h"
# include "AudioPlayer.h"
# include "OpenAL+NNT.h"
# include "../Drivers/AudioBuffer.h"
# include "AudioFile.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(audio)

NNTDECL_PRIVATE_BEGIN_CXX(Player)

void init()
{
    
}

void dealloc()
{
    
}

codec::Oal oal;
audio::PlayBuffer buf;

NNTDECL_PRIVATE_END_CXX

Player::Player()
{
    NNTDECL_PRIVATE_CONSTRUCT(Player);
}

Player::~Player()
{
    NNTDECL_PRIVATE_DESTROY();
}

void Player::seek(real v)
{
    d_ptr->oal.seek(v);
}

real Player::length() const
{
    return d_ptr->oal.length;
}

real Player::position() const
{
    real v = 0;
    d_ptr->oal.position(v);
    return v;
}

void Player::pause()
{
    d_ptr->oal.pause();
}

void Player::resume()
{
    d_ptr->oal.resume();
}

void Player::stop()
{
    d_ptr->oal.stop();
}

bool Player::play(core::IoStream& stm, NntAudioFormat fmt)
{
    d_ptr->buf.type = FileType(fmt);
    d_ptr->buf.stream = &stm;
    if (d_ptr->buf.open() == false)
        return false;
    
    d_ptr->oal.format = d_ptr->buf.format;
    d_ptr->oal.open();
    
    core::data tmp(d_ptr->buf.length());
    if (d_ptr->buf.read(tmp, 0) == false)
        return false;
    
    int format = 0;
    switch (d_ptr->buf.format.bits())
    {
        default:
        case 16: format |= codec::Oal::FORMAT_16BITS; break;
        case 8: format |= codec::Oal::FORMAT_8BITS; break;
    }
    
    if (d_ptr->buf.format.channel() > 1)
        format |= codec::Oal::FORMAT_STEREO;
    else
        format |= codec::Oal::FORMAT_MONO;
    
    if (d_ptr->oal.read(tmp,
                        format,
                        d_ptr->buf.format.sampler()) == false)
        return false;
    
    return d_ptr->oal.play();
}

NNT_END_NS
NNT_END_CXX
