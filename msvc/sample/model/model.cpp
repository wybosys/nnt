// model.cpp : Defines the entry point for the console application.
//

# include <wsi/WSIFoundation.h>
# include "classes/AppModel.h"

WSIAPP_BEGIN

class App
    : public cross::Console
{
public:

    void load()
    {
        ::wsiapp::GoogleModel mdl;
    }

};

WSIAPP_END

int main(int argc, char* argv[])
{
    ::wsiapp::App app;
    return app.execute(argc, argv);
}

