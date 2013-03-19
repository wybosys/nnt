
# ifndef __NNT_UIKIT_COREPLOT_CPBARLAYER_0FFAC5E12EED469A9AACE30656CA319C_H_INCLUDED
# define __NNT_UIKIT_COREPLOT_CPBARLAYER_0FFAC5E12EED469A9AACE30656CA319C_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface CPBarLayer : CPLayer {
    
    //! fill normal
    CPFill *layerFill;
    
    //! fill highlight
    CPFill *layerFillHighlight;
    
    //! border style
    CPLineStyle *layerBorderLineStyle;
    
    //! border style highlight
    CPLineStyle *layerBorderLineStyleHighlight;
    
}

@property (nonatomic, retain) CPFill *layerFill, *layerFillHighlight;
@property (nonatomic, retain) CPLineStyle *layerBorderLineStyle, *layerBorderLineStyleHighlight;

@end

typedef CPBarLayer UICPBarLayer;

NNT_END_HEADER_OBJC

# endif