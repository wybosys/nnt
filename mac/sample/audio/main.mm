
# include <nnt/Foundation+NNT.h>

# include <nnt/Drivers/MicDevice.h>
# include <nnt/Codec/MicRecorder.h>

# include <nnt/Core/File+NNT.h>
# include <nnt/Parser/WavParser.h>
# include <nnt/Codec/VoicePrint.h>

# include <nnt/Trail/Micphone.h>
# include <nnt/Core/Task+NNT.h>

NNT_USINGCXXNAMESPACE;

class RecordTask
: public core::Task
{
public:
    
    RecordTask()
    : recording(false)
    {
        infinite();
        dev_trail.start();
        
        au_rdr.set(dev_mic);
        au_rdr.type.set("wav");
        //au_rdr.format.set_sampler(8000);
        au_rdr.format.set_channel(1);
        au_rdr.format.set_bits(8);
    }
    
    ~RecordTask()
    {
        
    }
    
    virtual int main()
    {
        dev_trail.update();
        real p = dev_trail.peak_power();
        
        trace_fmt(@"mic power: %f", p);
        
        if (p > -10 && !recording)
        {
            recording = true;
            trace_msg(@"recording start");
            
            // begin recording.
            au_rdr.start();
        }
        else if (p < -20 && recording)
        {
            trace_msg(@"recording ended");
            recording = false;
            
            // end recording.
            au_rdr.stop();
            
            parser::Wav wav;
            if (wav.parse(au_rdr.buffer().data))
            {
                trace_msg(@"parsing audio");
                vp::Digest dg;
                core::data da;
                wav.collect(da);
                
                vp::Result result = dg.calc(da);
                if (result.empty() == false)
                {
                    // get nearest.
                    real min = FLT_MAX;
                    int match = -1;
                    for (core::counter<results_type::const_iterator> each = results.begin();
                         each != results.end();
                         ++each)
                    {
                        real res = result.compare(*each);
                        trace_fmt(@"compare %d: %f", each.count, res);
                        if (min > res)
                        {
                            match = each.count;
                            min = res;
                        }
                    }
                    
                    if (match != -1)
                    {
                        trace_fmt(@"matched audio: %d", match);
                    }
                    else
                    {
                        trace_msg(@"fail match");
                    }
                    
                    // save result.
                    results.push_back(result);
                    
                    // save record.
                    core::File::SaveAll(core::FileUrl<>("record.wav"), au_rdr.buffer().data);
                }
            }
            else
            {
                trace_msg(@"failed to digest vp");
            }
        }
        else
        {
            trace_msg(@"failed to parse audio");
        }
        
        ::sleep_second(1);
        return 0;
    }
 
    mic::Device dev_mic;
    mic::Recorder au_rdr;
    mic::Trail dev_trail;
    bool recording;
    typedef core::vector<vp::Result> results_type;
    results_type results;
    
};

RecordTask task;

void test_manual()
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
    
    trace_fmt(@"0-1 %f", res0.compare(res1));
    trace_fmt(@"0-2 %f", res0.compare(res2));
    trace_fmt(@"1-2 %f", res1.compare(res2));
    
}

int main(int argc, char** argv)
{
    task.start();
    
    //if (1) test_manual();
    
    cross::Application app;
    return app.execute(argc, argv);
}
