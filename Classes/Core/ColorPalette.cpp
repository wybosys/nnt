
# include "Core.h"
# include "ColorPalette.h"
# include "../Graphic/NGBase.h"

NNT_BEGIN_C

uint ColorWheel [][NNT_COLORWHEEL_COMPSIZE] = {
    {0xe60314, 0xe92938, 0xee5663, 0xf3888e, 0xf7b0b6, 0xfbd9ba, 0xfdefef},
    {0xb61477, 0xc13389, 0xcb589d, 0xd884b6, 0xe4a6cb, 0xeec8e1, 0xf8e4ef},
    {0x631b89, 0x743796, 0x8f5aa8, 0xaa84bf, 0xc2a7d0, 0xd7c7e2, 0xeae2ef},
    {0x424c91, 0x5b649f, 0x7a80b2, 0x9ba1c5, 0xb9bdd6, 0xd4d6e5, 0xeaeaf2},
    {0x2d6fab, 0x4581b3, 0x6c9cc4, 0x8eb2d2, 0xb4cde1, 0xd3e1ec, 0xd3e1ec},
    {0x19989e, 0x39a6ab, 0x5db6ba, 0x83c7ca, 0xa8d8da, 0xc6e5e7, 0xdff1f1},
    {0x039b46, 0x23a75c, 0x49b77a, 0x71c798, 0x99d6b4, 0xbae4cc, 0xd3eedf},
    {0x94c627, 0x9fcc3e, 0xb0d561, 0xc0dd81, 0xd1e6a3, 0xdeeebf, 0xebf6d8},
    {0xfff108, 0xfff32d, 0xfef550, 0xfff778, 0xfffa9f, 0xfefcbf, 0xfffdd7},
    {0xf3c325, 0xf4ca44, 0xf7d66b, 0xf9df8b, 0xfbe8ae, 0xfcf0c8, 0xfdf7e1},
    {0xe69017, 0xea9f39, 0xeeb05d, 0xf2c282, 0xf7d8ac, 0xf9e4c7, 0xfcf0e0},
    {0xec6200, 0xf07f2f, 0xf49a5c, 0xf7b990, 0xf9d2b5, 0xfde7da, 0xfff8f2}
};

colorpicker_t ColorWheelPicker() {
    colorpicker_t ret;
    ret.colorwheel = (const uint*)ColorWheel;
    ret.current = ret.current_comp = 0;
    ret.size = sizeof(ColorWheel) / sizeof(rgb_t[NNT_COLORWHEEL_COMPSIZE]);
    ret.size_comp = NNT_COLORWHEEL_COMPSIZE;
    return ret;
}

void ColorPickerReset(colorpicker_t* __obj) {
    __obj->current = __obj->current_comp = 0;
}

uint ColorPickerNextColor(colorpicker_t* __obj) {
    uint ret = __obj->colorwheel[__obj->current * __obj->size_comp + __obj->current_comp];
    ++__obj->current;
    if (__obj->current >= __obj->size) {
        __obj->current = 0;
        ++__obj->current_comp;
    }
    if (__obj->current_comp >= __obj->size_comp) {
        __obj->current = __obj->current_comp = 0;
    }
    return ret;
}

uint ColorPickerAtIndex(colorpicker_t* __obj, uint __idx) {
    uint ret = __obj->colorwheel[__idx * __obj->size_comp + __obj->current_comp];
    return ret;
}

NNT_END_C
