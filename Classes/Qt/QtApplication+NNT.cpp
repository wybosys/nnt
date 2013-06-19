
# include "Core.h"
# include "Qt+NNT.h"
# include "QtApplication+NNT.h"
# include "../UIKit/Cross/UcKernel.h"
# include "../UIKit/Cross/UcWindow.h"
# include "../Core/framework.prv.h"

# ifdef NNT_MSVC
# endif

NNT_BEGIN_CXX
NNT_BEGIN_NS(cross)

class LogoWindow
: public ui::uc::Window
{
public:
    
    virtual void init()
    {
        core::string f_logo = prv::resource_directory() + "logo.png";
        QPixmap* pm = new QPixmap(QString::fromStdString(f_logo));
        QLabel* logo = new QLabel;
        logo->setPixmap(pm->scaled(64, 64));
        QVBoxLayout* lyt = new QVBoxLayout(widget());
        lyt->addWidget(logo);
    }
    
};

QApplication* __gsqt_application = NULL;
Application* __gs_application = NULL;

Application::Application()
: _root(NULL)
{
    __gs_application = this;
}

Application::~Application()
{
    safe_delete(_window);
}

void Application::load()
{
    PASS;
}

int Application::execute(int argc, char **argv)
{
    // create Qt App.
    __gsqt_application = new QApplication(argc, argv);
    
    // create root window.
    _window = new LogoWindow;
    _window->init();
    
    // call nnt.
    this->load();
    
    // show main window.
# ifdef NNT_DEBUG
    
    _window->show();
    
# endif
    
    // into loop.
    int ret = 0;
    
    try
    {
        ret = __gsqt_application->exec();
    }
    catch (...)
    {
        trace_msg("unknown exception.");
    }
    
    return ret;
}

Application& Application::getInstance()
{
    return *__gs_application;
}

IArguments* Application::arguments()
{
    return NULL;
}

NNT_END_NS
NNT_END_CXX
