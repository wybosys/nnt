
# include "Core.h"
# include "AudioPlayer.h"
# include "OpenAL+NNT.h"

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

NNTDECL_PRIVATE_END_CXX

Player::Player()
{
    NNTDECL_PRIVATE_CONSTRUCT(Player);
}

Player::~Player()
{
    NNTDECL_PRIVATE_DESTROY();
}

bool Player::play(core::IoStream const& stm)
{
    d_ptr->oal.open();
    return true;
}

NNT_END_NS
NNT_END_CXX
