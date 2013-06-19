
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
    vp::Result res0, res1, res2;
    
    {
        core::data da;
        core::File::ReadAll(core::File::url_type("word.wav"), da);
        parser::Wav wv;
        wv.parse(da);
        wv.set_channel(1);
        wv.set_bps(8);
        wv.save(da);
        da.clear();
        wv.collect(da);
        vp::Digest dg;
        res0 = dg.calc(da);
    }
    
    {
        core::data da;
        core::File::ReadAll(core::File::url_type("word1.wav"), da);
        parser::Wav wv;
        wv.parse(da);
        wv.set_channel(1);
        wv.set_bps(8);
        wv.save(da);
        da.clear();
        wv.collect(da);
        vp::Digest dg;
        res1 = dg.calc(da);
    }
    
    {
        core::data da;
        core::File::ReadAll(core::File::url_type("word2.wav"), da);
        parser::Wav wv;
        wv.parse(da);
        wv.set_channel(1);
        wv.set_bps(8);
        wv.save(da);
        da.clear();
        wv.collect(da);
        vp::Digest dg;
        res2 = dg.calc(da);
    }
        
    trace_fmt(@"0-1 cmp: %f", res0.compare(res1));
    trace_fmt(@"0-2 cmp: %f", res0.compare(res2));
    trace_fmt(@"1-2 cmp: %f", res1.compare(res2));
    
}

int main(int argc, const char * argv[])
{    
    test_vp();
    return 0;
}
