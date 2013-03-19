
# ifndef __WAE_APP_E76B54DF1F174FFFA490F2F9CA10FCD9_H_INCLUDED
# define __WAE_APP_E76B54DF1F174FFFA490F2F9CA10FCD9_H_INCLUDED

# include "MainController.h"

WAE_BEGIN

class App
: public Application
{
public:
    
    void load();
    MainController ctlr;
    
};

WAE_END

# endif
