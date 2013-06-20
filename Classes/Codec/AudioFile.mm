
# import "Core.h"
# import "AudioFile.h"
# import "../Drivers/MicDevice.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(audio)

FormatType::FormatType()
{
    memset(&_format, 0, sizeof(_format));
    
    // default set.
    _format.mSampleRate = mic::Device::SampleRate();
    _format.mChannelsPerFrame = 2;
}

FormatType::~FormatType()
{
    
}

void FormatType::update(AudioQueueRef queue)
{
    UInt32 sz = sizeof(_format);
    OSStatus sta = AudioQueueGetProperty(queue,
                                         kAudioConverterCurrentOutputStreamDescription,
                                         &_format,
                                         &sz);
    if (sta != 0)
        trace_msg(@"failed to update format by queue");
}

void FormatType::update(FileType const& ft)
{
    if (ft.is_bigedian(_format.mBitsPerChannel))
        _format.mFormatFlags |= kLinearPCMFormatFlagIsBigEndian;
    
    if (_format.mFormatID == 0)
    {
        switch (ft)
        {
            case kAudioFileAIFFType: _format.mFormatID = kAudioFormatAppleLossless; break;
            case kAudioFileAIFCType: _format.mFormatID = kAudioFormatAppleIMA4; break;
            case kAudioFileWAVEType: _format.mFormatID = kAudioFormatLinearPCM; break;
            case kAudioFileMP1Type: _format.mFormatID = kAudioFormatMPEGLayer1; break;
            case kAudioFileMP2Type: _format.mFormatID = kAudioFormatMPEGLayer2; break;
            case kAudioFileMP3Type: _format.mFormatID = kAudioFormatMPEGLayer3; break;
            case kAudioFileAC3Type: _format.mFormatID = kAudioFormatAC3; break;
            case kAudioFileAAC_ADTSType: _format.mFormatID = kAudioFormatMPEG4AAC; break;
            case kAudioFileAMRType: _format.mFormatID = kAudioFormatAMR; break;
            default: trace_msg(@"failed to convert filetype to formattype"); break;
        }
    }
}

FileType::FileType()
{
    
}

FileType::FileType(ns::String const& str)
{
    _type = FindType(str);
}

FileType::~FileType()
{
    
}

void FileType::set(ns::String const& str)
{
    _type = FindType(str);
}

AudioFileTypeID FileType::FindType(ns::String const& str)
{
	OSStatus err;
    AudioFileTypeID ret = 0;
    
    CFStringRef filename = str.cf<CFStringRef>();
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
    
    if (err != 0)
    {
        trace_msg(@"failed get file type");
    }
# ifdef NNT_DEBUG
    else
    {
        core::string str((char const*)&ret, propertySize);
        str = core::string(str.rbegin(), str.rend());
        trace_fmt(@"got file type: %s", str.c_str());
    }
# endif
	
    return ret;
}

bool FileType::is_bigedian(uint bits) const
{
    AudioFileTypeAndFormatID ftf;
	UInt32 propertySize;
	OSStatus err;
	Boolean requiresBigEndian;
	
	ftf.mFileType = _type;
	ftf.mFormatID = kAudioFormatLinearPCM;
	
	err = AudioFileGetGlobalInfoSize(kAudioFileGlobalInfo_AvailableStreamDescriptionsForFormat, sizeof(ftf), &ftf, &propertySize);
	if (err) return FALSE;
    
	AudioStreamBasicDescription *formats = (AudioStreamBasicDescription *)malloc(propertySize);
	err = AudioFileGetGlobalInfo(kAudioFileGlobalInfo_AvailableStreamDescriptionsForFormat, sizeof(ftf), &ftf, &propertySize, formats);
	requiresBigEndian = TRUE;
    if (err == noErr) {
        int i, nFormats = propertySize / sizeof(AudioStreamBasicDescription);
        for (i = 0; i < nFormats; ++i) {
            if (formats[i].mBitsPerChannel == bits
                && !(formats[i].mFormatFlags & kLinearPCMFormatFlagIsBigEndian)) {
                requiresBigEndian = FALSE;
                break;
            }
        }
    }
	free(formats);
	return requiresBigEndian;
}

NNT_END_NS
NNT_END_CXX
