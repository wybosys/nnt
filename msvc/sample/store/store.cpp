// store.cpp : Defines the entry point for the console application.
//

# include <nnt/Foundation+NNT.h>
# include <nnt/Store/SqlServer+NNT.h>

NNTAPP_BEGIN

class App
    : public cross::Console
{
public:

    void load()
    {
        if (1)
        {
            store::SqlServer sqlsrv;
            store::connection_info info;
            info.url = "WYBO-WIN\\TEST";
            info.user = "test";
            info.passwd = "test";
            info.database = "TEST";
            sqlsrv.connect(info);

            store::datatable_t* dt = NULL;

            if (1)
            {
                dt = sqlsrv.exec("select * from TEST");
                core::string str = dt->to_string();
                trace_msg(str);
                dt->drop();
            }

            if (1)
            {
                dt = sqlsrv.exec("select * from TEST where ID = @id; select * from TEST where NAME = @name;", 
                    core::push_back<store::SqlServer::params_type>(
                    core::make_pair("id", variant_t(1)),
                    core::make_pair("name", variant_t("DDDDD", core::assign))
                    ));
                store::datatable_t* next = dt;
                while (next)
                {
                    trace_msg(next->to_string());
                    next = next->next;
                }
                dt->drop();
            }
        }
    }

};

NNTAPP_END

int main(int argc, char* argv[])
{
    ::nntapp::App app;
    return app.execute(argc, argv);
}

