
# include "Core.h"
# include "../../Qt/Qt+NNT.h"
# include "UcKernel.h"
# include "UcWindow.h"

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
    _new<QMainWindow>();
    
    QMainWindow* win = (QMainWindow*)_obj;
    
    // set center widget.
    _qt = new QWidget(win);
    win->setCentralWidget((QWidget*)_qt);
}

void Window::destroy()
{
    safe_delete<QWidget>(_qt);
    _delete<QMainWindow>();
}

void Window::init()
{
    
}

void Window::show()
{
    _as<QMainWindow>()->show();
}

UC_END
