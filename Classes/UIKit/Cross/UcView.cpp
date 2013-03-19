
# include "Core.h"
# include "UcKernel.h"
# include "UcView.h"
# include <QtGui/QtGui>
# include "../../Core/App.h"
# include "UcWindow.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(cross)

NNT_EXTERN Application* __gs_application;

NNT_END_NS
NNT_END_CXX

UC_BEGIN

NNT_BEGIN_NS(impl)

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

NNT_END_NS

UC_END
