
# import "Core.h"
# import "NGUtils.h"

NNT_BEGIN_OBJC

/**
 *	@brief Extracts the color information from a CGColorRef and returns it as a NgRGBAColor.
 *
 *	Supports RGBA and grayscale colorspaces.
 *
 *	@param color The color.
 *	@return The RGBA components of the color.
 **/
NgRGBAColor NgRGBAColorFromCGColor(CGColorRef color)
{
	NgRGBAColor rgbColor;
	
	size_t numComponents = CGColorGetNumberOfComponents(color);
	
	if (numComponents == 2) {
		const CGFloat *components = CGColorGetComponents(color);
		CGFloat all = components[0];
		rgbColor.red = all;
		rgbColor.green = all;
		rgbColor.blue = all;
		rgbColor.alpha = components[1];
	} else {
		const CGFloat *components = CGColorGetComponents(color);
		rgbColor.red = components[0];
		rgbColor.green = components[1];
		rgbColor.blue = components[2];
		rgbColor.alpha = components[3];
	}
    
	return rgbColor;
}

NNT_END_OBJC
