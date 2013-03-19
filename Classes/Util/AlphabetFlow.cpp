
# include "Core.h"
# include "AlphabetFlow.h"

NNT_BEGIN_C

char *alphabetflow_next(char const* str, uint len)
{
    char *buf = (char*)malloc(len + 2);
    memcpy(buf + 1, str, len);
    buf[len + 1] = 0;
    bool overflow = false;
    for (uint i = 0; i < len; ++i) 
    {
        for (uint j = len - i; j != 0; --j) {
            if (str[j - 1] == 'Z')
            {
                overflow = true;
                buf[j] = 'A';
            }
            else
            {
                if (overflow) 
                {
                    if (str[j - 1] == 'Z')
                    {
                        overflow = true;
                        buf[j] = 'A';
                    }
                    else
                    {
                        overflow = false;
                        buf[j] = str[j - 1] + 1;
                    }
                }
                else
                {
                    buf[j] = str[j - 1] + 1;
                    break;
                }
            }
        }
        if (overflow == false)
            break;
    }
    if (overflow)
    {
        buf[0] = 'A';
    }
    else
    {
        memmove(buf, buf + 1, len + 1);   
    }
    return buf;
}

char *alphabetflow_prev(char const* str, uint len)
{
    char *buf = (char*)malloc(len + 1);
    buf[len] = 0;
    memcpy(buf, str, len);
    bool overflow = false;
    for (uint i = 0; i < len; ++i) 
    {
        for (uint j = len - i; j != 0; --j) {
            if (str[j - 1] == 'A')
            {
                overflow = true;
                buf[j - 1] = 'Z';
            }
            else
            {
                if (overflow) 
                {
                    if (str[j - 1] == 'A')
                    {
                        overflow = true;
                        buf[j - 1] = 'Z';
                    }
                    else
                    {
                        overflow = false;
                        buf[j - 1] = str[j - 1] - 1;
                    }
                }
                else
                {
                    buf[j - 1] = str[j - 1] - 1;
                    break;
                }
            }
        }
        if (overflow == false)
            break;
    }
    if (overflow)
    {
        memmove(buf, buf + 1, len);
    }
    return buf;
}

NNT_END_C

NNT_BEGIN_CXX

AlphabetFlow::AlphabetFlow()
{
    //this->curValue = AlphabetFlow::defaultValue();
}

core::string AlphabetFlow::defaultValue() const
{
    return "A";
}

core::string AlphabetFlow::nextValue(const core::string & value)
{
    char *ret = alphabetflow_next(value.c_str(), (uint)value.length());
    core::string str = ret;
    free(ret);
    return str;
}

core::string AlphabetFlow::prevValue(const core::string & value)
{
    char *ret = alphabetflow_prev(value.c_str(), (uint)value.length());
    core::string str = ret;
    free(ret);
    return str;   
}

core::string AlphabetFlow::next()
{
    if (curValue.empty())
    {
        curValue = AlphabetFlow::defaultValue();
        return curValue;
    }
    
    char *ret = alphabetflow_next(curValue.c_str(), (uint)curValue.length());
    curValue = ret;
    free(ret);
    return curValue;
}

core::string AlphabetFlow::prev()
{    
    char *ret = alphabetflow_prev(curValue.c_str(), (uint)curValue.length());
    curValue = ret;
    free(ret);
    return curValue;
}

NNT_END_CXX