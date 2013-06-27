
# include "Core.h"
# include "AudioFile.h"
# include "../Drivers/MicDevice.h"
# include "../Core/File+NNT.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(audio)

# ifdef NNT_MACH

FormatType::FormatType()
{
    memset(&_format, 0, sizeof(_format));
    
    // default set.
    _format.mSampleRate = mic::Device::SampleRate();
    _format.mChannelsPerFrame = 2;
}

FormatType::~FormatType()
{
    PASS;
}

void FormatType::set_channel(uint v)
{
    _format.mChannelsPerFrame = v;
}

uint FormatType::channel() const
{
    return _format.mChannelsPerFrame;
}

void FormatType::set_bits(uint v)
{
    _format.mBitsPerChannel = v;
}

uint FormatType::bits() const
{
    return _format.mBitsPerChannel;
}

void FormatType::set_sampler(real v)
{
    _format.mSampleRate = v;
}

real FormatType::sampler() const
{
    return _format.mSampleRate;
}

void FormatType::update(AudioQueueRef queue)
{
    UInt32 sz = sizeof(_format);
    OSStatus sta = AudioQueueGetProperty(queue,
                                         kAudioConverterCurrentOutputStreamDescription,
                                         &_format,
                                         &sz);
    if (sta != 0)
        trace_msg("failed to update format by queue");
}

void FormatType::update(FileType const& ft)
{
    core::string file = ft;
    
    if (_format.mFormatID == 0)
    {
        switch (ft)
        {
            case kAudioFileAIFFType: _format.mFormatID = kAudioFormatAppleLossless; break;
            case kAudioFileWAVEType: _format.mFormatID = kAudioFormatLinearPCM; break;
            case kAudioFileMP1Type: _format.mFormatID = kAudioFormatMPEGLayer1; break;
            case kAudioFileMP2Type: _format.mFormatID = kAudioFormatMPEGLayer2; break;
            case kAudioFileMP3Type: _format.mFormatID = kAudioFormatMPEGLayer3; break;
            case kAudioFileAC3Type: _format.mFormatID = kAudioFormatAC3; break;
            case kAudioFileAAC_ADTSType: _format.mFormatID = kAudioFormatMPEG4AAC; break;
            case kAudioFileAMRType: _format.mFormatID = kAudioFormatAMR; break;
            case kAudioFile3GPType: _format.mFormatID = kAudioFormatMPEG4AAC; break;
            case kAudioFile3GP2Type: _format.mFormatID = kAudioFormatMPEG4AAC; break;
            case kAudioFileM4AType: _format.mFormatID = kAudioFormatMPEG4AAC; break;
            case kAudioFileM4BType: _format.mFormatID = kAudioFormatMPEG4AAC; break;
            case kAudioFileCAFType:
            {
                if (file == "lbc")
                    _format.mFormatID = kAudioFormatiLBC;
                else
                    _format.mFormatID = kAudioFormatAppleLossless;
            } break;
            default: trace_fmt("failed to convert file-type to format-type, %.4s", (char*)&ft); break;
        }
    }
    
    if (_format.mFormatID == 0)
        _format.mFormatID = kAudioFormatLinearPCM;
    
    switch (_format.mFormatID)
    {
        case kAudioFormatLinearPCM:
        {
            _format.mFormatID = kAudioFormatLinearPCM;
            
            if (_format.mBitsPerChannel == 0)
                _format.mBitsPerChannel = 16;
            if (_format.mBitsPerChannel > 8)
                
                _format.mFormatFlags |= kLinearPCMFormatFlagIsSignedInteger;
            _format.mFormatFlags |= kLinearPCMFormatFlagIsPacked;
            
            if (ft.is_bigedian(*this))
                _format.mFormatFlags |= kLinearPCMFormatFlagIsBigEndian;
            
            _format.mBytesPerPacket = _format.mBytesPerFrame = (_format.mBitsPerChannel / 8) * _format.mChannelsPerFrame;
            _format.mFramesPerPacket = 1;
            _format.mReserved = 0;
        } break;
            
        case kAudioFormatiLBC:
        {
            _format.mChannelsPerFrame = 1;
            _format.mSampleRate = 8000;
        } break;
            
        case kAudioFormatMPEG4AAC:
        {
           
        } break;
            
    }
    
    update();
    
}

void FormatType::update()
{
    UInt32 sz = sizeof(_format);
    AudioFormatGetProperty(kAudioFormatProperty_FormatInfo,
                           0, NULL,
                           &sz, &_format);
}

FileType::FileType()
{
    
}

FileType::~FileType()
{
    
}

FileType::FileType(core::string const& str)
{
    _type = FindType(str);
}

FileType::FileType(NntAudioFormat fmt)
{
    switch (fmt)
    {
        case AUDIO_FORMAT_AAC:
            _type = kAudioFileAAC_ADTSType; break;
        case AUDIO_FORMAT_MP3:
            _type = kAudioFileMP3Type; break;
        case AUDIO_FORMAT_WAVE:
            _type = kAudioFileWAVEType; break;
    }
}

void FileType::set(core::string const& str)
{
    _strtype = str;
    ::std::transform(_strtype.begin(), _strtype.end(), _strtype.begin(), ::tolower);
    _type = FindType(_strtype);
}

AudioFileTypeID FileType::FindType(core::string const& str)
{
	OSStatus err;
    AudioFileTypeID ret = 0;
    
    CFStringRef filename = CFStringCreateWithCString(kCFAllocatorDefault, str.c_str(), kCFStringEncodingASCII);
    CFStringRef extension = NULL;
    
	// find the extension in the filename.
	CFRange range = CFStringFind(filename, CFSTR("."), kCFCompareBackwards);
	if (range.location == kCFNotFound)
    {
		extension = filename;
    }
    else
    {
        range.location += 1;
        range.length = CFStringGetLength(filename) - range.location;
        extension = CFStringCreateWithSubstring(NULL, filename, range);
    }
	
	UInt32 propertySize = sizeof(AudioFileTypeID);
	err = AudioFileGetGlobalInfo(kAudioFileGlobalInfo_TypesForExtension,
                                 sizeof(extension),
                                 &extension,
                                 &propertySize,
                                 &ret);
    if (extension != filename)
        CFRelease(extension);
    CFRelease(filename);
    
    if (propertySize == 0)
    {
        ret = kAudioFileCAFType;
    }
    
    if (err != 0)
    {
        trace_msg("failed get file type");
    }
# ifdef NNT_DEBUG
    else
    {
        trace_fmt("got file type: %.4s", (char*)&ret);
    }
# endif
	
    return ret;
}

bool FileType::is_bigedian(FormatType const& fmt) const
{
    AudioFileTypeAndFormatID ftf;
	UInt32 propertySize;
	OSStatus err;
	Boolean requiresBigEndian;
	
	ftf.mFileType = _type;
	ftf.mFormatID = ((AudioStreamBasicDescription const*)fmt)->mFormatID;
	
	err = AudioFileGetGlobalInfoSize(kAudioFileGlobalInfo_AvailableStreamDescriptionsForFormat, sizeof(ftf), &ftf, &propertySize);
	if (err)
        return FALSE;
    
	AudioStreamBasicDescription *formats = (AudioStreamBasicDescription *)malloc(propertySize);
	err = AudioFileGetGlobalInfo(kAudioFileGlobalInfo_AvailableStreamDescriptionsForFormat, sizeof(ftf), &ftf, &propertySize, formats);
	requiresBigEndian = TRUE;
    if (err == noErr) {
        int i, nFormats = propertySize / sizeof(AudioStreamBasicDescription);
        for (i = 0; i < nFormats; ++i)
        {
            if (formats[i].mBitsPerChannel == ((AudioStreamBasicDescription const*)fmt)->mBitsPerChannel
                && !(formats[i].mFormatFlags & kLinearPCMFormatFlagIsBigEndian))
            {
                requiresBigEndian = FALSE;
                break;
            }
        }
    }
	free(formats);
	return requiresBigEndian;
}

/*
 
FileFormat::FileFormat()
{
    
}

FileFormat::~FileFormat()
{
    
}

void FileFormat::load(core::IoStream &stm)
{
    
}

 */
 
# endif

NNT_END_NS
NNT_END_CXX
