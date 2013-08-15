
# include <nnt/Foundation+NNT.h>
# include <nnt/Core/CmdArguments.h>
# include <nnt/Store/Sqlite+NNT.h>

NNT_USINGNAMESPACE;

int main(int argc, char** argv)
{
    cmd::Arguments args(argc, argv);
    if (args.count() == 0)
    {
        trace_msg("lost arguments");
        //return 0;
    }
    
    //core::string type = args["-t"].value();
    //core::string key = args["-k"].value();
    //core::string path = args.last();
    
    core::string type = "decrypt";
    core::string key = "u42hpdfsaphyp9r32hjiofw";
    core::string path = "/Users/wybo/Desktop/dog.db";
    
    trace_msg("type " + type);
    trace_msg("key " + key);
        
    if (type == "encrypt")
    {
        store::Sqlite db;
        db.readonly = false;
        store::connection_info dbinfo;
        dbinfo.url = path;
        if (db.connect(dbinfo))
        {
            db.re_key(key);
            trace_msg("数据库加密成功");
        }
        else
        {
            trace_msg("数据库打开失败");
        }
        db.close();
    }
    else if (type == "decrypt")
    {
        store::Sqlite db;
        db.readonly = false;
        store::connection_info dbinfo;
        dbinfo.url = path;
        if (db.connect(dbinfo))
        {
            db.set_key(key);
            db.re_key("");
            trace_msg("数据库解密成功");
        }
        else
        {
            trace_msg("数据库打开失败");
        }
        db.close();
    }
    else if (type == "create")
    {
        store::Sqlite db;
        db.readonly = false;
        db.creatable = true;
        store::connection_info dbinfo;
        dbinfo.url = path;
        if (db.connect(dbinfo))
        {
            trace_msg("数据库建立成功");
        }
        else
        {
            trace_msg("数据库建立失败");
        }
        db.close();
    }
    
    return 0;
}

