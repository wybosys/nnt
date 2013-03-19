
# include <wsi/WSIFoundation.h>

WSIAPP_BEGIN

class App
    : public cross::Console
{
public:

    void load()
    {
        int* p = 0;
        *p = 123;
    }

};

WSIAPP_END

int main(int argc, char* argv[])
{
    ::wsiapp::App app;
    return app.execute(argc, argv);
}

