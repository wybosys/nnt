
# include "Core.h"
# include "AudioStream.h"
# include <AudioToolbox/AudioToolbox.h>

NNT_BEGIN_CXX
NNT_BEGIN_NS(audio)

PCMAudioStreamIOS::PCMAudioStreamIOS()
{
    _ofmt = new AudioStreamBasicDescription;
}

PCMAudioStreamIOS::~PCMAudioStreamIOS()
{
    delete _ofmt;
}

bool PCMAudioStreamIOS::load(core::string const& file)
{
    NSString* strurl = [NSString stringWithCString:file.c_str() encoding:NSUTF8StringEncoding];
    NSURL* url = [NSURL URLWithString:[strurl stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding]];
    
    // 使用exfile读取文件
    ExtAudioFileRef af = NULL;
    ExtAudioFileOpenURL((CFURLRef)url, &af);
    if (af == NULL)
        return false;
    
    // 获取目标文件音频格式信息
    AudioStreamBasicDescription infmt;
    UInt32 propSize = sizeof(infmt);
    ExtAudioFileGetProperty(af, kExtAudioFileProperty_FileDataFormat, &propSize, &infmt);
    
    // set output file info.
    _ofmt->mSampleRate = infmt.mSampleRate;
    _ofmt->mChannelsPerFrame = infmt.mChannelsPerFrame;
    _ofmt->mFormatID = kAudioFormatLinearPCM;
    _ofmt->mBytesPerPacket = 2 * _ofmt->mChannelsPerFrame;
    _ofmt->mFramesPerPacket = 1;
    _ofmt->mBytesPerFrame = 2 * _ofmt->mChannelsPerFrame;
    _ofmt->mBitsPerChannel = 16;
    _ofmt->mFormatFlags = kAudioFormatFlagsNativeEndian | kAudioFormatFlagIsPacked | kAudioFormatFlagIsSignedInteger;
    
    ExtAudioFileSetProperty(af,
                            kExtAudioFileProperty_ClientDataFormat,
                            sizeof(*_ofmt),
                            _ofmt);
    
    SInt64 frames;
    propSize = sizeof(frames);
    ExtAudioFileGetProperty(af,
                            kExtAudioFileProperty_FileLengthFrames,
                            &propSize,
                            &frames);
    
    // 生成缓存
    _buf.alloc(frames * _ofmt->mBytesPerFrame);
    
    // 读取PCM数据
    AudioBufferList readbuf;
    readbuf.mNumberBuffers = 1;
    readbuf.mBuffers[0].mNumberChannels = _ofmt->mChannelsPerFrame;
    readbuf.mBuffers[0].mData = _buf.bytes();
    readbuf.mBuffers[0].mDataByteSize = _buf.length();
    
    UInt32 readed = frames;
    ExtAudioFileRead(af,
                     &readed,
                     &readbuf);
    
    _buf.set_length(readed * _ofmt->mBytesPerFrame);
    
    ExtAudioFileDispose(af);
    return readed != 0;
}

NNT_END_NS
NNT_END_CXX
