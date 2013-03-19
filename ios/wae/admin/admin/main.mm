
# include "wae.h"
# include "WSIExecution.h"
# include "AppDelegate.h"

int main(int argc, char *argv[])
{
    ::wsiapp::wae::App app;
    return app.execute(argc, argv);
}
