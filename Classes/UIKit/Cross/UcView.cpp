
# include "Core.h"
# include "UcKernel.h"
# include "UcView.h"
# include <QtGui/QtGui>
# include "../../Core/App.h"
# include "UcWindow.h"

WSI_BEGIN_CXX
WSI_BEGIN_NS(cross)

WSI_EXTERN Application* __gs_application;

WSI_END_NS
WSI_END_CXX

UC_BEGIN

WSI_BEGIN_NS(impl)

void* View::Create()
{
    Window* win = (Window*)cross::__gs_application->window();
    QWidget* qwin = (QWidget*)win->object();
    return new QWidget(qwin);
}

void View::Destroy(void*& obj)
{
    safe_delete_type(obj, QWidget*);
}

void View::Resize(void* obj, Size const& sz)
{
    QWidget* q = (QWidget*)obj;
    q->resize(sz.width, sz.height);
}

void View::Show(void* obj)
{
    QWidget* q = (QWidget*)obj;
    q->show();
}

WSI_END_NS

UC_END
