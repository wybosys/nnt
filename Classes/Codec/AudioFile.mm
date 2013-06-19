
# import "Core.h"
# import "AudioFile.h"
# import "../Drivers/MicDevice.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(audio)

FormatType::FormatType()
{    
    _format.mChannelsPerFrame = 2;
    _format.mFormatID = kAudioFormatLinearPCM;
    _format.mFormatFlags = kLinearPCMFormatFlagIsSignedInteger | kLinearPCMFormatFlagIsPacked;
    _format.mBitsPerChannel = 16;
    _format.mReserved = 0;
    _format.mFramesPerPacket = 1;
    _format.mBytesPerPacket = _format.mBytesPerFrame = (_format.mBitsPerChannel / 8) * _format.mChannelsPerFrame;
    _format.mSampleRate = mic::Device::SampleRate();
    _format.mReserved = 0;
}

FormatType::~FormatType()
{
    
}

void FormatType::update(FileType const& ft)
{
    if (ft.is_bigedian(_format.mBitsPerChannel))
        _format.mFormatFlags |= kLinearPCMFormatFlagIsBigEndian;
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
	err = AudioFileGetGlobalInfo(kAudioFileGlobalInfo_TypesForExtension, sizeof(extension), &extension, &propertySize, &ret);
	CFRelease(extension);
	
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
