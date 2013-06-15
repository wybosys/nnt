
# include "Foundation+NNT.h"
# include "Execution+NNT.h"
# include "AppDelegate.h"
# include "AppStatistics.h"

int main(int argc, char *argv[])
{
    ::nntapp::App app;
    ::nnt::ns::Object<AppStatistics> as;
    return app.execute(argc, argv);
}
