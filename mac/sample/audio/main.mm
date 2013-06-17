
# include <nnt/Foundation+NNT.h>
# include <nnt/Drivers/MicDevice.h>
# include <nnt/Codec/MicRecorder.h>

int main(int argc, const char * argv[])
{
    NNT_USINGCXXNAMESPACE;
    
    mic::Device mic;
    mic::Recorder rdr(mic);
    rdr.type.set("wav");
    rdr.start();
    
    return 0;
}
