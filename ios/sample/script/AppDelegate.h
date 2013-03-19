
# ifndef APP_DELEGATE
# define APP_DELEGATE

# include "ScriptController.h"

NNTAPP_BEGIN

class App
: public Application
{
public:
  
    void load();
    ScriptController ctlr;
    
};

NNTAPP_END

# endif
