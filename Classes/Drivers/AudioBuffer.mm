
# include "Core.h"
# include "AudioBuffer.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(audio)

void Buffer::receive(AudioQueueRef inAQ, AudioQueueBufferRef inBuffer, const AudioTimeStamp *inStartTime, UInt32 inNumPackets, const AudioStreamPacketDescription *inPacketDesc)
{

    /*
    OSStatus sta = AudioFileWritePackets(stm,
                                         FALSE,
                                         inBuffer->mAudioDataByteSize,
                                         inPacketDesc,
                                         packets,
                                         &inNumPackets,
                                         inBuffer->mAudioData);
     */

    OSStatus sta = AudioFileStreamParseBytes(stm,
                                             inBuffer->mAudioDataByteSize,
                                             inBuffer->mAudioData,
                                             kAudioFileStreamPropertyFlag_CacheProperty);
    
    if (sta == noErr)
    {
        packets += inNumPackets;
    }
# ifdef NNT_DEBUG
    else
    {
        autocollect;
        trace_fmt(@"failed to parse data, %.4s", (char*)&sta);
    }
# endif
    
    //data = core::data((byte*)inBuffer->mAudioData, (usize)inBuffer->mAudioDataByteSize, core::assign);
    //emit(kSignalBytesAvailable, cxx::eventobj_t::Data(&data));
    
    if (used)
    {
        sta = AudioQueueEnqueueBuffer(inAQ, inBuffer, 0, NULL);
        
# ifdef NNT_DEBUG
        if (sta != 0)
        {
            autocollect;
            trace_fmt(@"failed to reuse audio buffer, %.4s", (char*)&sta);
        }
# endif
    }
}

NNT_END_NS
NNT_END_CXX
