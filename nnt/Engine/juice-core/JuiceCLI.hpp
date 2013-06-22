
# ifndef __JUICE_CLI_DFF7CBED3C72404892B0F1B373020231_H_INCLUDED
# define __JUICE_CLI_DFF7CBED3C72404892B0F1B373020231_H_INCLUDED

# include "JuiceInteractive.hpp"

JUICE_BEGIN

template <typename classT>
class InteractiveCLI
: public Interactive<classT>
{
    
public:
    
    void println(rawstr_t str)
    {
        printf("%s\n", str);
    }
    
};

JUICE_END

# endif