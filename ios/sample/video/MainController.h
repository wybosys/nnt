
# ifndef __MAIN_CTLR_FE2BC02E012E4887BE5AA92407212661_H_INCLUDED
# define __MAIN_CTLR_FE2BC02E012E4887BE5AA92407212661_H_INCLUDED

# include "UIVideoController.h"

NNTAPP_BEGIN

class MainController
: public ui::VideoController
{
public:
    MainController();
    void view_loaded();
};

NNTAPP_END

# endif
