
# ifndef __NNT_CORE_COLORPALETTE_739813B0652648548BFE6BE86F74051F_H_INCLUDED
# define __NNT_CORE_COLORPALETTE_739813B0652648548BFE6BE86F74051F_H_INCLUDED

NNT_BEGIN_HEADER_C

# define NNT_COLORWHEEL_COMPSIZE 7

NNT_EXTERN uint ColorWheel [][NNT_COLORWHEEL_COMPSIZE];

typedef struct {
    const uint* colorwheel;
    int current;
    int current_comp;
    int size;
    int size_comp;
} colorpicker_t;

//! init a color wheel.
NNT_EXTERN colorpicker_t ColorWheelPicker(void);

//! pick next color.
NNT_EXTERN uint ColorPickerNextColor(colorpicker_t*);

//! pick color at index.
NNT_EXTERN uint ColorPickerAtIndex(colorpicker_t*, uint);

//! reset color wheel.
NNT_EXTERN void ColorPickerReset(colorpicker_t*);

NNT_END_HEADER_C

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(core)

class ColorWheel
{
public:
    
    ColorWheel()
    {
        _picker = ColorWheelPicker();
    }
    
    void reset()
    {
        ColorPickerReset(&_picker);
    }
    
    uint next()
    {
        return ColorPickerNextColor(&_picker);
    }
    
    uint at(uint idx) const
    {
        return ColorPickerAtIndex((colorpicker_t*)&_picker, idx);
    }
    
protected:
    
    colorpicker_t _picker;
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif