
# ifndef __NNT_TRAIL_MICPHONE_E191973467984FA1B24AC916BF7661B9_H_INCLUDED
# define __NNT_TRAIL_MICPHONE_E191973467984FA1B24AC916BF7661B9_H_INCLUDED

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(mic)

NNTDECL_PRIVATE_HEAD_CXX(Trail);

class Channel
{
public:
    
    Channel();
    ~Channel();
    
    real average_power() const;
    real peak_power() const;
    
protected:
    
    void* _buffer;
    
    NNTDECL_PRIVATE_FRIEND(Trail);
};

class Trail
: public cxx::Object<>
{
    
    NNTDECL_PRIVATE_CXX(Trail);
    
public:
    
    Trail(bool autostart = false);
    ~Trail();
  
    void start();
    void stop();
    bool update();
    
    real average_power() const;
    real peak_power() const;
    
    real interval;
    Channel left, right;
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
