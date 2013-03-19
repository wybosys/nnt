
# ifndef __WSI_CORE_COLORPALETTE_739813B0652648548BFE6BE86F74051F_H_INCLUDED
# define __WSI_CORE_COLORPALETTE_739813B0652648548BFE6BE86F74051F_H_INCLUDED

WSI_BEGIN_HEADER_C

# define WSI_COLORWHEEL_COMPSIZE 7

WSI_EXTERN uint ColorWheel [][WSI_COLORWHEEL_COMPSIZE];

typedef struct {
    const uint* colorwheel;
    int current;
    int current_comp;
    int size;
    int size_comp;
} colorpicker_t;

//! init a color wheel.
WSI_EXTERN colorpicker_t ColorWheelPicker(void);

//! pick next color.
WSI_EXTERN uint ColorPickerNextColor(colorpicker_t*);

//! pick color at index.
WSI_EXTERN uint ColorPickerAtIndex(colorpicker_t*, uint);

//! reset color wheel.
WSI_EXTERN void ColorPickerReset(colorpicker_t*);

WSI_END_HEADER_C

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(core)

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

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif