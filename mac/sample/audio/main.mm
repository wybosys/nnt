
# include <nnt/Foundation+NNT.h>

# include <nnt/Drivers/MicDevice.h>
# include <nnt/Codec/MicRecorder.h>

# include <nnt/Codec/VoicePrint.h>

NNT_USINGCXXNAMESPACE;

void test_mic()
{
    mic::Device mic;
    mic::Recorder rdr(mic);
    rdr.type.set("wav");
    rdr.start();
}

void test_vp()
{
    vp::Digest dg;
}

int main(int argc, const char * argv[])
{
    test_vp();
    return 0;
}
