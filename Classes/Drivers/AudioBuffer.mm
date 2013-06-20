
# include "Core.h"
# include "AudioBuffer.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(audio)

void Buffer::receive(AudioQueueRef inAQ, AudioQueueBufferRef inBuffer, const AudioTimeStamp *inStartTime, UInt32 inNumPackets, const AudioStreamPacketDescription *inPacketDesc)
{
    data = core::data((byte*)inBuffer->mAudioData, (usize)inBuffer->mAudioDataByteSize, core::assign);
    emit(kSignalBytesAvailable, cxx::eventobj_t::Data(&data));
}

NNT_END_NS
NNT_END_CXX
