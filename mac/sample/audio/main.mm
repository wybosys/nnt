
# include <nnt/Foundation+NNT.h>

# include <nnt/Drivers/MicDevice.h>
# include <nnt/Codec/MicRecorder.h>

# include <nnt/Core/File+NNT.h>
# include <nnt/Parser/WavParser.h>
# include <nnt/Codec/VoicePrint.h>

NNT_USINGCXXNAMESPACE;

mic::Device dev_mic;
mic::Recorder au_rdr;
core::File f_rdr;

void mic_bytes(cxx::eventobj_t& evt)
{
    core::data& da = evt;
    f_rdr.write(da);
}

void test_mic()
{
    f_rdr.open(core::FileUrl<>("record.wav"), mask_t().on<Io::write>().on<Io::create>());
    au_rdr.set(dev_mic);
    au_rdr.type.set("wav");
    au_rdr.buffer().connect(kSignalBytesAvailable, mic_bytes);
    au_rdr.start();
    sleep_second(1);
    au_rdr.stop();
    f_rdr.close();
}

void test_vp()
{
    vp::Result res0, res1, res2;
    
    {
        core::data da;
        core::File::ReadAll(core::File::url_type("record.wav"), da);
        parser::Wav wv;
        wv.parse(da);
        wv.set_channel(1);
        wv.set_bps(8);
        wv.save(da);
    }
    
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

int main(int argc, char** argv)
{
    if (1) test_mic();
    if (1) test_vp();
    
    cross::Application app;
    return app.execute(argc, argv);
}
