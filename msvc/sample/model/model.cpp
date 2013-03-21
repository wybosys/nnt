// model.cpp : Defines the entry point for the console application.
//

# include <nnt/Foundation+NNT.h>
# include "classes/AppModel.h"

NNTAPP_BEGIN

class App
    : public cross::Console
{
public:

    void load()
    {
        ::nntapp::GoogleModel mdl;
    }

};

NNTAPP_END

int main(int argc, char* argv[])
{
    ::nntapp::App app;
    return app.execute(argc, argv);
}

