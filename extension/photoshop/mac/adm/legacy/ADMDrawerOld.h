/***********************************************************************/
/*                                                                     */
/* ADMDrawerOld.h                                                      */
/* Old versions of ADM Drawer Suite                                    */
/*                                                                     */
/* ADOBE SYSTEMS INCORPORATED                                          */
/* Copyright 1996-2002 Adobe Systems Incorporated                      */
/* All Rights Reserved                                                 */
/*                                                                     */
/* NOTICE:  Adobe permits you to use, modify, and distribute this file */
/* in accordance with the terms of the Adobe license agreement         */
/* accompanying it. If you have received this file from a source other */
/* than Adobe, then your use, modification, or distribution of it      */
/* requires the prior written permission of Adobe.                     */
/*                                                                     */
/***********************************************************************/

#ifndef __ADMDrawerOld__
#define __ADMDrawerOld__

#ifndef __ADMTypes__
#include "ADMTypes.h"
#endif

#ifndef _ADMAGMTYPES_H_
#include "ADMAGMTypes.h"
#endif


// -----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

#pragma ADM_PRAGMA_ALIGN_BEGIN
#pragma ADM_PRAGMA_IMPORT_BEGIN


// =============================================================================
//		* ADM Drawer Suite, version 2
// =============================================================================

#define kADMDrawerSuiteVersion2 2

// -----------------------------------------------------------------------------

typedef struct ADMDrawerSuite2
{

	// port accessor

	ADMPortRef ADMAPI (*GetPortRef)(ADMDrawerRef inDrawer);

	// clear entire area of drawer
	
	void ADMAPI (*Clear)(ADMDrawerRef inDrawer);

	// bounds accessor
	
	void ADMAPI (*GetBoundsRect)(ADMDrawerRef inDrawer, ADMRect* outBoundsRect);

	// clipping
	
	void ADMAPI (*GetClipRect)(ADMDrawerRef inDrawer, ADMRect* outClipRect);
	void ADMAPI (*SetClipRect)(ADMDrawerRef inDrawer, const ADMRect* inClipRect);
	void ADMAPI (*IntersectClipRect)(ADMDrawerRef inDrawer, const ADMRect* inClipRect);
	void ADMAPI (*UnionClipRect)(ADMDrawerRef inDrawer, const ADMRect* inClipRect);
	void ADMAPI (*SubtractClipRect)(ADMDrawerRef inDrawer, const ADMRect* inClipRect);

	void ADMAPI (*SetClipPolygon)(ADMDrawerRef inDrawer, const ADMPoint* inPoints,
				ADMInt32 inNumPoints);

	void ADMAPI (*IntersectClipPolygon)(ADMDrawerRef inDrawer, const ADMPoint* inPoints,
				ADMInt32 inNumPoints);

	void ADMAPI (*UnionClipPolygon)(ADMDrawerRef inDrawer, const ADMPoint* inPoints,
				ADMInt32 inNumPoints);

	void ADMAPI (*SubtractClipPolygon)(ADMDrawerRef inDrawer, const ADMPoint* inPoints,
				ADMInt32 inNumPoints);
	
	// port origin
	
	void ADMAPI (*GetOrigin)(ADMDrawerRef inDrawer, ADMPoint* outOrigin);
	void ADMAPI (*SetOrigin)(ADMDrawerRef inDrawer, const ADMPoint* inOrigin);
	
	// drawing state accessors
	
	void ADMAPI (*GetRGBColor)(ADMDrawerRef inDrawer, ADMRGBColor* outColor);
	void ADMAPI (*SetRGBColor)(ADMDrawerRef inDrawer, const ADMRGBColor* inColor);
	
	ADMColor ADMAPI (*GetADMColor)(ADMDrawerRef inDrawer);
	void ADMAPI (*SetADMColor)(ADMDrawerRef inDrawer, ADMColor inColor);
	
	ADMDrawMode ADMAPI (*GetDrawMode)(ADMDrawerRef inDrawer);
	void ADMAPI (*SetDrawMode)(ADMDrawerRef inDrawer, ADMDrawMode inDrawMode);
	
	ADMFont ADMAPI (*GetFont)(ADMDrawerRef inDrawer);
	void ADMAPI (*SetFont)(ADMDrawerRef inDrawer, ADMFont inFont);

	// simple shape drawers
	
	void ADMAPI (*DrawLine)(ADMDrawerRef inDrawer, const ADMPoint* inStartPoint,
				const ADMPoint* inEndPoint);
	
	void ADMAPI (*DrawPolygon)(ADMDrawerRef inDrawer, const ADMPoint* inPoints, ADMInt32 inNumPoints);
	void ADMAPI (*FillPolygon)(ADMDrawerRef inDrawer, const ADMPoint* inPoints, ADMInt32 inNumPoints);
	
	void ADMAPI (*DrawRect)(ADMDrawerRef inDrawer, const ADMRect* inRect);
	void ADMAPI (*FillRect)(ADMDrawerRef inDrawer, const ADMRect* inRect);
	void ADMAPI (*ClearRect)(ADMDrawerRef inDrawer, const ADMRect* inRect);
	void ADMAPI (*DrawSunkenRect)(ADMDrawerRef inDrawer, const ADMRect* inRect);
	void ADMAPI (*DrawRaisedRect)(ADMDrawerRef inDrawer, const ADMRect* inRect);
	void ADMAPI (*InvertRect)(ADMDrawerRef inDrawer, const ADMRect* inRect);
	
	void ADMAPI (*DrawOval)(ADMDrawerRef inDrawer, const ADMRect* inRect);
	void ADMAPI (*FillOval)(ADMDrawerRef inDrawer, const ADMRect* inRect);

	// AGM access
	
	ADMAGMPortPtr ADMAPI (*GetAGMPort)(ADMDrawerRef inDrawer);

	void ADMAPI (*DrawAGMImage)(ADMDrawerRef inDrawer,
				const struct _t_ADMAGMImageRecord* inImage,
				const ADMFixedMatrix* inMatrix, ADMInt32 inFlags);

	// resource drawing
	
	void ADMAPI (*DrawResPicture)(ADMDrawerRef inDrawer, SPPluginRef inPluginRef,
				ADMInt32 inRsrcID, const ADMPoint* inTopLeftPoint);

	void ADMAPI (*DrawResPictureCentered)(ADMDrawerRef inDrawer, SPPluginRef inPluginRef,
				ADMInt32 inRsrcID, const ADMRect* inRect);
	
	void ADMAPI (*DrawRecoloredResPicture)(ADMDrawerRef inDrawer, SPPluginRef inPluginRef,
				ADMInt32 inRsrcID, const ADMPoint* inTopLeftPoint, ADMRecolorStyle inStyle);

	void ADMAPI (*DrawRecoloredResPictureCentered)(ADMDrawerRef inDrawer,
				SPPluginRef inPluginRef, ADMInt32 inRsrcID, const ADMRect* inRect,
				ADMRecolorStyle inStyle);

	// icon drawing

	void ADMAPI (*DrawIcon)(ADMDrawerRef inDrawer, ADMIconRef inIcon, const ADMPoint* inTopLeftPoint);
	void ADMAPI (*DrawIconCentered)(ADMDrawerRef inDrawer, ADMIconRef inIcon, const ADMRect* inRect);

	void ADMAPI (*DrawRecoloredIcon)(ADMDrawerRef inDrawer, ADMIconRef inIcon,
				const ADMPoint* inTopLeftPoint, ADMRecolorStyle inStyle);

	void ADMAPI (*DrawRecoloredIconCentered)(ADMDrawerRef inDrawer, ADMIconRef inIcon,
				const ADMRect* inRect, ADMRecolorStyle inStyle);

	void ADMAPI (*GetResPictureBounds)(ADMDrawerRef inDrawer, SPPluginRef inPluginRef,
				ADMInt32 inRsrcID, ADMRect* outBoundsRect);

	// text drawing

	ADMInt32 ADMAPI (*GetTextWidth)(ADMDrawerRef inDrawer, const char* inText);
	void ADMAPI (*GetFontInfo)(ADMDrawerRef inDrawer, ADMFontInfo* outFontInfo);
	
	void ADMAPI (*DrawText)(ADMDrawerRef inDrawer, const char* inText, const ADMPoint* inPoint);
	void ADMAPI (*DrawTextLeft)(ADMDrawerRef inDrawer, const char* inText, const ADMRect* inRect);
	void ADMAPI (*DrawTextCentered)(ADMDrawerRef inDrawer, const char* inText, const ADMRect* inRect);
	void ADMAPI (*DrawTextRight)(ADMDrawerRef inDrawer, const char* inText, const ADMRect* inRect);

	// standard arrows
	
	void ADMAPI (*DrawUpArrow)(ADMDrawerRef inDrawer, const ADMRect* inRect);
	void ADMAPI (*DrawDownArrow)(ADMDrawerRef inDrawer, const ADMRect* inRect);
	void ADMAPI (*DrawLeftArrow)(ADMDrawerRef inDrawer, const ADMRect* inRect);
	void ADMAPI (*DrawRightArrow)(ADMDrawerRef inDrawer, const ADMRect* inRect);

	// drawer creation/destruction

	ADMDrawerRef ADMAPI (*Create)(ADMPortRef inPortRef, const ADMRect* inBoundsRect, ADMFont inFont);	
	void ADMAPI (*Destroy)(ADMDrawerRef inDrawer);

	// image drawing

	void ADMAPI (*DrawADMImage)(ADMDrawerRef inDrawer, ADMImageRef inImage,
				const ADMPoint* inTopLeftPoint);

	void ADMAPI (*DrawADMImageCentered)(ADMDrawerRef inDrawer, ADMImageRef inImage,
				const ADMRect* inRect);
	
}
ADMDrawerSuite2;


// =============================================================================
//		* ADM Drawer Suite, version 3
// =============================================================================

#define kADMDrawerSuiteVersion3 3

// -----------------------------------------------------------------------------

typedef struct ADMDrawerSuite3
{

	// *** This suite is FROZEN.
	// *** It shipped with Photoshop 5.5 and ImageReady 2.0.

	// port accessor

	ADMPortRef ADMAPI (*GetPortRef)(ADMDrawerRef inDrawer);

	// clear entire area of drawer
	
	void ADMAPI (*Clear)(ADMDrawerRef inDrawer);

	// bounds accessor
	
	void ADMAPI (*GetBoundsRect)(ADMDrawerRef inDrawer, ADMRect* outBoundsRect);

	// clipping
	
	void ADMAPI (*GetClipRect)(ADMDrawerRef inDrawer, ADMRect* outClipRect);
	void ADMAPI (*SetClipRect)(ADMDrawerRef inDrawer, const ADMRect* inClipRect);
	void ADMAPI (*IntersectClipRect)(ADMDrawerRef inDrawer, const ADMRect* inClipRect);
	void ADMAPI (*UnionClipRect)(ADMDrawerRef inDrawer, const ADMRect* inClipRect);
	void ADMAPI (*SubtractClipRect)(ADMDrawerRef inDrawer, const ADMRect* inClipRect);

	void ADMAPI (*SetClipPolygon)(ADMDrawerRef inDrawer, const ADMPoint* inPoints,
				ADMInt32 inNumPoints);

	void ADMAPI (*IntersectClipPolygon)(ADMDrawerRef inDrawer, const ADMPoint* inPoints,
				ADMInt32 inNumPoints);

	void ADMAPI (*UnionClipPolygon)(ADMDrawerRef inDrawer, const ADMPoint* inPoints,
				ADMInt32 inNumPoints);

	void ADMAPI (*SubtractClipPolygon)(ADMDrawerRef inDrawer, const ADMPoint* inPoints,
				ADMInt32 inNumPoints);
	
	// port origin
	
	void ADMAPI (*GetOrigin)(ADMDrawerRef inDrawer, ADMPoint* outOrigin);
	void ADMAPI (*SetOrigin)(ADMDrawerRef inDrawer, const ADMPoint* inOrigin);
	
	// drawing state accessors
	
	void ADMAPI (*GetRGBColor)(ADMDrawerRef inDrawer, ADMRGBColor* outColor);
	void ADMAPI (*SetRGBColor)(ADMDrawerRef inDrawer, const ADMRGBColor* inColor);
	
	ADMColor ADMAPI (*GetADMColor)(ADMDrawerRef inDrawer);
	void ADMAPI (*SetADMColor)(ADMDrawerRef inDrawer, ADMColor inColor);
	
	ADMDrawMode ADMAPI (*GetDrawMode)(ADMDrawerRef inDrawer);
	void ADMAPI (*SetDrawMode)(ADMDrawerRef inDrawer, ADMDrawMode inDrawMode);
	
	ADMFont ADMAPI (*GetFont)(ADMDrawerRef inDrawer);
	void ADMAPI (*SetFont)(ADMDrawerRef inDrawer, ADMFont inFont);

	// simple shape drawers
	
	void ADMAPI (*DrawLine)(ADMDrawerRef inDrawer, const ADMPoint* inStartPoint,
				const ADMPoint* inEndPoint);
	
	void ADMAPI (*DrawPolygon)(ADMDrawerRef inDrawer, const ADMPoint* inPoints,
				ADMInt32 inNumPoints);

	void ADMAPI (*FillPolygon)(ADMDrawerRef inDrawer, const ADMPoint* inPoints,
				ADMInt32 inNumPoints);
	
	void ADMAPI (*DrawRect)(ADMDrawerRef inDrawer, const ADMRect* inRect);
	void ADMAPI (*FillRect)(ADMDrawerRef inDrawer, const ADMRect* inRect);
	void ADMAPI (*ClearRect)(ADMDrawerRef inDrawer, const ADMRect* inRect);
	void ADMAPI (*DrawSunkenRect)(ADMDrawerRef inDrawer, const ADMRect* inRect);
	void ADMAPI (*DrawRaisedRect)(ADMDrawerRef inDrawer, const ADMRect* inRect);
	void ADMAPI (*InvertRect)(ADMDrawerRef inDrawer, const ADMRect* inRect);
	
	void ADMAPI (*DrawOval)(ADMDrawerRef inDrawer, const ADMRect* inRect);
	void ADMAPI (*FillOval)(ADMDrawerRef inDrawer, const ADMRect* inRect);

	// AGM access
	
	ADMAGMPortPtr ADMAPI (*GetAGMPort)(ADMDrawerRef inDrawer);

	void ADMAPI (*DrawAGMImage)(ADMDrawerRef inDrawer,
				const struct _t_ADMAGMImageRecord* inImage,
				const ADMFixedMatrix* inMatrix, ADMInt32 inFlags);

	// resource drawing
	
	void ADMAPI (*DrawResPicture)(ADMDrawerRef inDrawer, SPPluginRef inPluginRef,
				ADMInt32 inRsrcID, const ADMPoint* inTopLeftPoint);

	void ADMAPI (*DrawResPictureCentered)(ADMDrawerRef inDrawer, SPPluginRef inPluginRef,
				ADMInt32 inRsrcID, const ADMRect* inRect);
	
	void ADMAPI (*DrawRecoloredResPicture)(ADMDrawerRef inDrawer, SPPluginRef inPluginRef,
				ADMInt32 inRsrcID, const ADMPoint* inTopLeftPoint, ADMRecolorStyle inStyle);

	void ADMAPI (*DrawRecoloredResPictureCentered)(ADMDrawerRef inDrawer,
				SPPluginRef inPluginRef, ADMInt32 inRsrcID, const ADMRect* inRect,
				ADMRecolorStyle inStyle);

	// icon drawing

	void ADMAPI (*DrawIcon)(ADMDrawerRef inDrawer, ADMIconRef inIcon, const ADMPoint* inTopLeftPoint);
	void ADMAPI (*DrawIconCentered)(ADMDrawerRef inDrawer, ADMIconRef inIcon, const ADMRect* inRect);

	void ADMAPI (*DrawRecoloredIcon)(ADMDrawerRef inDrawer, ADMIconRef inIcon,
				const ADMPoint* inTopLeftPoint, ADMRecolorStyle inStyle);

	void ADMAPI (*DrawRecoloredIconCentered)(ADMDrawerRef inDrawer, ADMIconRef inIcon,
				const ADMRect* inRect, ADMRecolorStyle inStyle);

	void ADMAPI (*GetResPictureBounds)(ADMDrawerRef inDrawer, SPPluginRef inPluginRef,
				ADMInt32 inRsrcID, ADMRect* outBoundsRect);

	// text drawing

	ADMInt32 ADMAPI (*GetTextWidth)(ADMDrawerRef inDrawer, const char* inText);
	void ADMAPI (*GetFontInfo)(ADMDrawerRef inDrawer, ADMFontInfo* outFontInfo);
	
	void ADMAPI (*DrawText)(ADMDrawerRef inDrawer, const char* inText, const ADMPoint* inPoint);
	void ADMAPI (*DrawTextLeft)(ADMDrawerRef inDrawer, const char* inText, const ADMRect* inRect);
	void ADMAPI (*DrawTextCentered)(ADMDrawerRef inDrawer, const char* inText, const ADMRect* inRect);
	void ADMAPI (*DrawTextRight)(ADMDrawerRef inDrawer, const char* inText, const ADMRect* inRect);
	
	// standard arrows

	void ADMAPI (*DrawUpArrow)(ADMDrawerRef inDrawer, const ADMRect* inRect);
	void ADMAPI (*DrawDownArrow)(ADMDrawerRef inDrawer, const ADMRect* inRect);
	void ADMAPI (*DrawLeftArrow)(ADMDrawerRef inDrawer, const ADMRect* inRect);
	void ADMAPI (*DrawRightArrow)(ADMDrawerRef inDrawer, const ADMRect* inRect);

	// drawer creation/destruction

	ADMDrawerRef ADMAPI (*Create)(ADMPortRef inPortRef, const ADMRect* inBoundsRect, ADMFont inFont);	
	void ADMAPI (*Destroy)(ADMDrawerRef inDrawer);

	// image drawing

	void ADMAPI (*DrawADMImage)(ADMDrawerRef inDrawer, ADMImageRef inImage,
				const ADMPoint* inTopLeftPoint);

	void ADMAPI (*DrawADMImageCentered)(ADMDrawerRef inDrawer, ADMImageRef inImage,
				const ADMRect* inRect);	

	// platform port accessors

	ADMPortRef ADMAPI (*GetADMWindowPort)(ADMWindowRef inWindowRef);
	void ADMAPI (*ReleaseADMWindowPort)(ADMWindowRef inWindowRef, ADMPortRef inPort);

	// font information

	void ADMAPI (*GetThisFontInfo)(ADMFont inFont, ADMFontInfo* outFontInfo);

	// text drawing

	void ADMAPI (*DrawTextInABox)(ADMDrawerRef inDrawer, const ADMRect* inRect, const char* inText);

	// update area accessor

	void ADMAPI (*GetUpdateRect)(ADMDrawerRef inDrawer, ADMRect* outRect);

}
ADMDrawerSuite3;

// -----------------------------------------------------------------------------

typedef ADMDrawerSuite3 ADMDrawerSuite;
#define kADMDrawerSuiteVersion kADMDrawerSuiteVersion3  // for historical reasons

// =============================================================================
//		* ADM Drawer Suite, version 4
// =============================================================================


#define kADMDrawerSuite "ADM Drawer Suite"
#define kADMDrawerSuiteVersion4 4

// -----------------------------------------------------------------------------

typedef struct ADMDrawerSuite4
{

	// *** This suite is FROZEN.
	// *** It shipped with Acrobat 5.0.

	// port accessor

	ADMPortRef ADMAPI (*GetPortRef)(ADMDrawerRef inDrawer);

	// clear entire area of drawer
	
	void ADMAPI (*Clear)(ADMDrawerRef inDrawer);

	// bounds accessor
	
	void ADMAPI (*GetBoundsRect)(ADMDrawerRef inDrawer, ADMRect* outBoundsRect);

	// clipping
	
	void ADMAPI (*GetClipRect)(ADMDrawerRef inDrawer, ADMRect* outClipRect);
	void ADMAPI (*SetClipRect)(ADMDrawerRef inDrawer, const ADMRect* inClipRect);
	void ADMAPI (*IntersectClipRect)(ADMDrawerRef inDrawer, const ADMRect* inClipRect);
	void ADMAPI (*UnionClipRect)(ADMDrawerRef inDrawer, const ADMRect* inClipRect);
	void ADMAPI (*SubtractClipRect)(ADMDrawerRef inDrawer, const ADMRect* inClipRect);

	void ADMAPI (*SetClipPolygon)(ADMDrawerRef inDrawer, const ADMPoint* inPoints,
				ADMInt32 inNumPoints);

	void ADMAPI (*IntersectClipPolygon)(ADMDrawerRef inDrawer, const ADMPoint* inPoints,
				ADMInt32 inNumPoints);

	void ADMAPI (*UnionClipPolygon)(ADMDrawerRef inDrawer, const ADMPoint* inPoints,
				ADMInt32 inNumPoints);

	void ADMAPI (*SubtractClipPolygon)(ADMDrawerRef inDrawer, const ADMPoint* inPoints,
				ADMInt32 inNumPoints);
	
	// port origin
	
	void ADMAPI (*GetOrigin)(ADMDrawerRef inDrawer, ADMPoint* outOrigin);
	void ADMAPI (*SetOrigin)(ADMDrawerRef inDrawer, const ADMPoint* inOrigin);
	
	// drawing state accessors
	
	void ADMAPI (*GetRGBColor)(ADMDrawerRef inDrawer, ADMRGBColor* outColor);
	void ADMAPI (*SetRGBColor)(ADMDrawerRef inDrawer, const ADMRGBColor* inColor);
	
	ADMColor ADMAPI (*GetADMColor)(ADMDrawerRef inDrawer);
	void ADMAPI (*SetADMColor)(ADMDrawerRef inDrawer, ADMColor inColor);
	
	ADMDrawMode ADMAPI (*GetDrawMode)(ADMDrawerRef inDrawer);
	void ADMAPI (*SetDrawMode)(ADMDrawerRef inDrawer, ADMDrawMode inDrawMode);
	
	ADMFont ADMAPI (*GetFont)(ADMDrawerRef inDrawer);
	void ADMAPI (*SetFont)(ADMDrawerRef inDrawer, ADMFont inFont);

	// simple shape drawers
	
	void ADMAPI (*DrawLine)(ADMDrawerRef inDrawer, const ADMPoint* inStartPoint,
				const ADMPoint* inEndPoint);
	
	void ADMAPI (*DrawPolygon)(ADMDrawerRef inDrawer, const ADMPoint* inPoints,
				ADMInt32 inNumPoints);

	void ADMAPI (*FillPolygon)(ADMDrawerRef inDrawer, const ADMPoint* inPoints,
				ADMInt32 inNumPoints);
	
	void ADMAPI (*DrawRect)(ADMDrawerRef inDrawer, const ADMRect* inRect);
	void ADMAPI (*FillRect)(ADMDrawerRef inDrawer, const ADMRect* inRect);
	void ADMAPI (*ClearRect)(ADMDrawerRef inDrawer, const ADMRect* inRect);
	void ADMAPI (*DrawSunkenRect)(ADMDrawerRef inDrawer, const ADMRect* inRect);
	void ADMAPI (*DrawRaisedRect)(ADMDrawerRef inDrawer, const ADMRect* inRect);
	void ADMAPI (*InvertRect)(ADMDrawerRef inDrawer, const ADMRect* inRect);
	
	void ADMAPI (*DrawOval)(ADMDrawerRef inDrawer, const ADMRect* inRect);
	void ADMAPI (*FillOval)(ADMDrawerRef inDrawer, const ADMRect* inRect);

	// AGM access
	
	ADMAGMPortPtr ADMAPI (*GetAGMPort)(ADMDrawerRef inDrawer);

	void ADMAPI (*DrawAGMImage)(ADMDrawerRef inDrawer,
				const struct _t_ADMAGMImageRecord* inImage,
				const ADMFixedMatrix* inMatrix, ADMInt32 inFlags);

	// resource drawing
	
	void ADMAPI (*DrawResPicture)(ADMDrawerRef inDrawer, SPPluginRef inPluginRef,
				ADMInt32 inRsrcID, const ADMPoint* inTopLeftPoint);

	void ADMAPI (*DrawResPictureCentered)(ADMDrawerRef inDrawer, SPPluginRef inPluginRef,
				ADMInt32 inRsrcID, const ADMRect* inRect);
	
	void ADMAPI (*DrawRecoloredResPicture)(ADMDrawerRef inDrawer, SPPluginRef inPluginRef,
				ADMInt32 inRsrcID, const ADMPoint* inTopLeftPoint, ADMRecolorStyle inStyle);

	void ADMAPI (*DrawRecoloredResPictureCentered)(ADMDrawerRef inDrawer,
				SPPluginRef inPluginRef, ADMInt32 inRsrcID, const ADMRect* inRect,
				ADMRecolorStyle inStyle);

	// icon drawing

	void ADMAPI (*DrawIcon)(ADMDrawerRef inDrawer, ADMIconRef inIcon, const ADMPoint* inTopLeftPoint);
	void ADMAPI (*DrawIconCentered)(ADMDrawerRef inDrawer, ADMIconRef inIcon, const ADMRect* inRect);

	void ADMAPI (*DrawRecoloredIcon)(ADMDrawerRef inDrawer, ADMIconRef inIcon,
				const ADMPoint* inTopLeftPoint, ADMRecolorStyle inStyle);

	void ADMAPI (*DrawRecoloredIconCentered)(ADMDrawerRef inDrawer, ADMIconRef inIcon,
				const ADMRect* inRect, ADMRecolorStyle inStyle);

	void ADMAPI (*GetResPictureBounds)(ADMDrawerRef inDrawer, SPPluginRef inPluginRef,
				ADMInt32 inRsrcID, ADMRect* outBoundsRect);

	// text drawing

	ADMInt32 ADMAPI (*GetTextWidth)(ADMDrawerRef inDrawer, const char* inText);
	ADMInt32 ADMAPI (*GetTextWidthW)(ADMDrawerRef inDrawer, const ADMUnicode* inText);

	void ADMAPI (*GetFontInfo)(ADMDrawerRef inDrawer, ADMFontInfo* outFontInfo);
	
	void ADMAPI (*DrawText)(ADMDrawerRef inDrawer, const char* inText, const ADMPoint* inPoint);
	void ADMAPI (*DrawTextW)(ADMDrawerRef inDrawer, const ADMUnicode* inText, const ADMPoint* inPoint);

	void ADMAPI (*DrawTextLeft)(ADMDrawerRef inDrawer, const char* inText, const ADMRect* inRect);
	void ADMAPI (*DrawTextLeftW)(ADMDrawerRef inDrawer, const ADMUnicode* inText, const ADMRect* inRect);

	void ADMAPI (*DrawTextCentered)(ADMDrawerRef inDrawer, const char* inText, const ADMRect* inRect);
	void ADMAPI (*DrawTextCenteredW)(ADMDrawerRef inDrawer, const ADMUnicode* inText, const ADMRect* inRect);

	void ADMAPI (*DrawTextRight)(ADMDrawerRef inDrawer, const char* inText, const ADMRect* inRect);
	void ADMAPI (*DrawTextRightW)(ADMDrawerRef inDrawer, const ADMUnicode* inText, const ADMRect* inRect);
	
	// standard arrows

	void ADMAPI (*DrawUpArrow)(ADMDrawerRef inDrawer, const ADMRect* inRect);
	void ADMAPI (*DrawDownArrow)(ADMDrawerRef inDrawer, const ADMRect* inRect);
	void ADMAPI (*DrawLeftArrow)(ADMDrawerRef inDrawer, const ADMRect* inRect);
	void ADMAPI (*DrawRightArrow)(ADMDrawerRef inDrawer, const ADMRect* inRect);

	// drawer creation/destruction

	ADMDrawerRef ADMAPI (*Create)(ADMPortRef inPortRef, const ADMRect* inBoundsRect, ADMFont inFont);	
	void ADMAPI (*Destroy)(ADMDrawerRef inDrawer);

	// image drawing

	void ADMAPI (*DrawADMImage)(ADMDrawerRef inDrawer, ADMImageRef inImage,
				const ADMPoint* inTopLeftPoint);

	void ADMAPI (*DrawADMImageCentered)(ADMDrawerRef inDrawer, ADMImageRef inImage,
				const ADMRect* inRect);	

	// platform port accessors

	ADMPortRef ADMAPI (*GetADMWindowPort)(ADMWindowRef inWindowRef);
	void ADMAPI (*ReleaseADMWindowPort)(ADMWindowRef inWindowRef, ADMPortRef inPort);

	// font information

	void ADMAPI (*GetThisFontInfo)(ADMFont inFont, ADMFontInfo* outFontInfo);

	// text drawing

	void ADMAPI (*DrawTextInABox)(ADMDrawerRef inDrawer, const ADMRect* inRect,
				const char* inText);
	void ADMAPI (*DrawTextInABoxW)(ADMDrawerRef inDrawer, const ADMRect* inRect,
				const ADMUnicode* inText);

	// update area accessor

	void ADMAPI (*GetUpdateRect)(ADMDrawerRef inDrawer, ADMRect* outRect);

	// text measurement
	
	ADMInt16 ADMAPI (*GetTextRectHeight)(ADMDrawerRef inDrawer, ADMInt16 inWidth,
				const char* inText);
	ADMInt16 ADMAPI (*GetTextRectHeightW)(ADMDrawerRef inDrawer, ADMInt16 inWidth,
				const ADMUnicode* inText);

}
ADMDrawerSuite4;

#pragma ADM_PRAGMA_IMPORT_END
#pragma ADM_PRAGMA_ALIGN_END

#ifdef __cplusplus
}
#endif

#endif
