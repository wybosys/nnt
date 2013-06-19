
# ifndef __NNTUICROSS_WINDOW_1A488DAAF07848BFA1AB63710D0B8C3A_H_INCLUDED
# define __NNTUICROSS_WINDOW_1A488DAAF07848BFA1AB63710D0B8C3A_H_INCLUDED

# include "UcView.h"

UC_BEGIN_HEADER

class Window
: public View<Window>
{
public:
    
    Window();
    ~Window();
    
    UC_OBJECT;
    
public:
    
    void show();
    
# ifdef NNT_QT
    
    operator QMainWindow* () const
    {
        return (QMainWindow*)_qt;
    }
    
    QMainWindow* qt() const
    {
        return (QMainWindow*)_qt;
    }
    
# endif
  
protected:
    
    void* _qt;
    
};

UC_END_HEADER

# endif
