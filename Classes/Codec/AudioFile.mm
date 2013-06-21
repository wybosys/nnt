
# include "Core.h"
# include "AudioFile.h"
# include "../Drivers/MicDevice.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(audio)

FileType::FileType(ns::String const& str)
{
    _type = FindType(str);
}

void FileType::set(ns::String const& str)
{
    _strtype = str.lower();
    _type = FindType(_strtype);
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
    
    if (propertySize == 0)
    {
        ret = kAudioFileCAFType;
    }
    
    if (err != 0)
    {
        trace_msg(@"failed get file type");
    }
# ifdef NNT_DEBUG
    else
    {
        trace_fmt(@"got file type: %.4s", (char*)&ret);
    }
# endif
	
    return ret;
}

NNT_END_NS
NNT_END_CXX
