
# include "Core.h"
# include "UcKernel.h"
# include "UcWindow.h"
# include <QtGui/QtGui>

UC_BEGIN

Window::Window()
{

}

Window::~Window()
{
    
}

void Window::create()
{
    // create main window.
    _create<QMainWindow>();
    
    QMainWindow* win = (QMainWindow*)_obj;
    
    // set center widget.
    _4qt = new QWidget(win);
    win->setCentralWidget((QWidget*)_4qt);
}

void Window::destroy()
{
    _destroy<QMainWindow>();
}

void Window::show()
{
    _as<QMainWindow>()->show();
}

UC_END
