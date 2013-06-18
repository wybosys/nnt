
# include <nnt/Foundation+NNT.h>

# include <nnt/Drivers/MicDevice.h>
# include <nnt/Codec/MicRecorder.h>

# include <nnt/Core/File+NNT.h>
# include <nnt/Parser/WavParser.h>
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
    {
        core::data da;
        core::File::ReadAll(core::File::url_type("word.wav"), da);
        parser::Wav wv;
        wv.parse(da);
        wv.set_channel(1);
        wv.set_bps(8);
        wv.save(da);
        core::File::SaveAll(core::File::url_type("word-tmp.wav"), da);
        vp::Digest dg;
    }
    
}

int main(int argc, const char * argv[])
{
    test_vp();
    return 0;
}
