/***********************************************************************/
/*                                                                     */
/* IADMImage.hpp                                                       */
/* Object wrapper for ADM Image Suite                                  */
/*                                                                     */
/* Copyright 1996-1999 Adobe Systems Incorporated.                     */
/* All Rights Reserved.                                                */
/*                                                                     */
/* Patents Pending                                                     */
/*                                                                     */
/* NOTICE: All information contained herein is the property of Adobe   */
/* Systems Incorporated. Many of the intellectual and technical        */
/* concepts contained herein are proprietary to Adobe, are protected   */
/* as trade secrets, and are made available only to Adobe licensees    */
/* for their internal use. Any reproduction or dissemination of this   */
/* software is strictly forbidden unless prior written permission is   */
/* obtained from Adobe.                                                */
/*                                                                     */
/* Started by Dave Lazarony, 11/20/1996                                */
/*                                                                     */
/***********************************************************************/

#ifndef __IADMImage_hpp__
#define __IADMImage_hpp__

/*
 * Includes
 */
 
#ifndef __ADMImage__
#include "ADMImage.h"
#endif

#ifndef __IADMDrawer_hpp__
#include "IADMDrawer.hpp"
#endif

/*
 * Global Suite Pointer
 */

extern "C" ADMImageSuite* sADMImage;

/*
 * Wrapper Class
 */

class IADMImage
{
private:
	ADMImageRef fImage;

public:	
	IADMImage();
	IADMImage(ADMImageRef Image);
	IADMImage(int nilImage);

	operator ADMImageRef();

	int GetWidth();
	int GetHeight();
	int GetByteWidth();
	int GetBitsPerPixel();
	
	ASByte* BeginBaseAddressAccess();
	void EndBaseAddressAccess();
	
	IADMDrawer BeginADMDrawer();
	void EndADMDrawer();
	
	void BeginAGMImageAccess(struct _t_ADMAGMImageRecord* imageRecord);
	void EndAGMImageAccess();
	
	ASErr GetPixel(const IASPoint& point, ADMRGBColor& color);
	ASErr SetPixel(const IASPoint& point, const ADMRGBColor& color);
};


inline IADMImage::IADMImage()	
{ 
	fImage = NULL; 
}

inline IADMImage::IADMImage(ADMImageRef Image)		
{ 
	fImage = Image; 
}

inline IADMImage::IADMImage(int)
{
	fImage = NULL;
}

inline IADMImage::operator ADMImageRef()				
{ 
	return fImage; 
}

inline int IADMImage::GetWidth()						
{ 
	return sADMImage->GetWidth(fImage); 
}

inline int IADMImage::GetHeight()						
{ 
	return sADMImage->GetHeight(fImage); 
}

inline int IADMImage::GetByteWidth()					
{ 
	return sADMImage->GetByteWidth(fImage); 
}

inline int IADMImage::GetBitsPerPixel()				
{ 
	return sADMImage->GetBitsPerPixel(fImage); 
}

inline ASByte* IADMImage::BeginBaseAddressAccess()				
{ 
	return sADMImage->BeginBaseAddressAccess(fImage); 
}

inline void IADMImage::EndBaseAddressAccess()				
{ 
	sADMImage->EndBaseAddressAccess(fImage); 
}

inline IADMDrawer IADMImage::BeginADMDrawer()		
{ 
	return sADMImage->BeginADMDrawer(fImage); 
}

inline void IADMImage::EndADMDrawer()		
{ 
	sADMImage->EndADMDrawer(fImage); 
}

inline void IADMImage::BeginAGMImageAccess(struct _t_ADMAGMImageRecord* imageRecord)	
{ 
	sADMImage->BeginAGMImageAccess(fImage, imageRecord); 
}

inline void IADMImage::EndAGMImageAccess()	
{ 
	sADMImage->EndAGMImageAccess(fImage); 
}

inline ASErr IADMImage::GetPixel(const IASPoint& point, ADMRGBColor& color)
{
	return sADMImage->GetPixel(fImage, &point, &color);
}

inline ASErr IADMImage::SetPixel(const IASPoint& point, const ADMRGBColor& color)
{
	return sADMImage->SetPixel(fImage, &point, &color);
}

#endif
