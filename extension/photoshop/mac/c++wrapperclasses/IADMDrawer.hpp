/***********************************************************************/
/*                                                                     */
/* IADMDrawer.hpp                                                      */
/* Object wrapper for ADM Drawer Suite                                 */
/*                                                                     */
/* Copyright 1998-1999 Adobe Systems Incorporated.                     */
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
/* Started by Dave Lazarony, 07/07/1998                                */
/*                                                                     */
/***********************************************************************/

#ifndef __IADMDrawer_hpp__
#define __IADMDrawer_hpp__

/*
 * Includes
 */
 
#ifndef __ADMDrawer__
#include "ADMDrawer.h"
#endif

#ifndef __IASTypes_hpp__
#include "IASTypes.hpp"
#endif

#include "ADMAGMTypes.h"

#ifdef USING_ZADM
	#ifndef __ZADM__
	#include "ZADM.h"
	#endif
#endif


/*
 * Forward Declarations
 */
 
extern "C" typedef struct SPPlugin SPPlugin;
extern "C" typedef struct _t_AGMImageRecord AGMImageRecord;

/*
 * Global Suite Pointer
 */

extern "C" ADMDrawerSuite* sADMDrawer;

#ifdef USING_ZADM
extern "C" ZADMSuite* sZADM;
#endif


/*
 * Wrapper Class
 */

class IADMDrawer
{
private:
	ADMDrawerRef fDrawer;

public:	
	IADMDrawer();
	IADMDrawer(ADMDrawerRef c);
	
	operator ADMDrawerRef (void);
	
	
	ASPortRef GetPortRef();
	
	void Clear();
	
	void GetBoundsRect(IASRect& boundsRect);
	
	
	void GetClipRect(IASRect& clipRect);
	void SetClipRect(const IASRect& clipRect);
	void IntersectClipRect(const IASRect& clipRect);
	void UnionClipRect(const IASRect& clipRect);
	void SubtractClipRect(const IASRect& clipRect);

	void SetClipPolygon(const IASPoint* points, int numPoints);
	void IntersectClipPolygon(const IASPoint* points, int numPoints);
	void UnionClipPolygon(const IASPoint* points, int numPoints);
	void SubtractClipPolygon(const IASPoint* points, int numPoints);

	void GetOrigin(IASPoint& origin);
	void SetOrigin(const IASPoint& origin);
	
	void GetRGBColor(ADMRGBColor& color);
	void SetRGBColor(const ADMRGBColor& color);
	
	ADMColor GetADMColor();
	void SetADMColor(ADMColor color);
	
	ADMDrawMode GetDrawMode();
	void SetDrawMode(ADMDrawMode drawMode);
	
	ADMFont GetFont();
	void SetFont(ADMFont font);
	
	
	void DrawLine(const IASPoint& startPoint, const IASPoint& endPoint);
	
	void DrawPolygon(const IASPoint* points, int numPoints);
	void FillPolygon(const IASPoint* points, int numPoints);
	
	void DrawRect(const IASRect& rect);
	void FillRect(const IASRect& rect);
	void ClearRect(const IASRect& rect);
	void DrawSunkenRect(const IASRect& rect);
	void DrawRaisedRect(const IASRect& rect);
	void InvertRect(const IASRect& rect);
	
	void DrawOval(const IASRect& rect);
	void FillOval(const IASRect& rect);
	
	ADMAGMPortPtr GetAGMPort();
	void DrawAGMImage(AGMImageRecord* image, ADMFixedMatrix* matrix, long flags);

	void DrawADMImage(ADMImageRef image, const IASPoint& topLeftPoint);
	void DrawADMImageCentered(ADMImageRef image, const IASRect& rect);

	void DrawResPicture(SPPlugin* pluginRef, int resID, const IASPoint& topLeftPoint, ADMRecolorStyle style = kADMNoRecolor);
	void DrawResPictureCentered(SPPlugin* pluginRef, int resID, const IASRect& rect, ADMRecolorStyle style = kADMNoRecolor);

	void DrawIcon(ADMIconRef icon, const IASPoint& topLeftPoint, ADMRecolorStyle style = kADMNoRecolor);
	void DrawIconCentered(ADMIconRef icon, const IASRect& rect, ADMRecolorStyle style = kADMNoRecolor);

	void GetResPictureBounds(struct SPPlugin* pluginRef, int resID, IASRect& boundsRect);

#ifdef USING_ZADM
	int GetTextWidth( const ASZString text );
#else
	int GetTextWidth(const char* text);
#endif
	void GetFontInfo(const ADMFontInfo& fontInfo);
	
#ifdef USING_ZADM
	void DrawText( const ASZString text, const IASPoint& point );
	
	void DrawTextLeft( const ASZString text, const IASRect& rect );
	void DrawTextCentered( const ASZString text, const IASRect& rect );
	void DrawTextRight( const ASZString text, const IASRect& rect );
#else
	void DrawText(const char* text, const IASPoint& point);
	
	void DrawTextLeft(const char* text, const IASRect& rect);
	void DrawTextCentered(const char* text, const IASRect& rect);
	void DrawTextRight(const char* text, const IASRect& rect);
#endif
	
	void DrawUpArrow(const IASRect& rect);
	void DrawDownArrow(const IASRect& rect);
	void DrawLeftArrow(const IASRect& rect);
	void DrawRightArrow(const IASRect& rect);	
};

inline IADMDrawer::IADMDrawer()								
{
	fDrawer = NULL;
}

inline IADMDrawer::IADMDrawer(ADMDrawerRef drawer)	
{
	fDrawer = drawer;
}

inline IADMDrawer::operator ADMDrawerRef (void)
{
	return fDrawer;
}

inline ASPortRef IADMDrawer::GetPortRef()
{
	return sADMDrawer->GetPortRef(fDrawer);
}

inline void IADMDrawer::Clear()
{
	sADMDrawer->Clear(fDrawer);
}
	
inline void IADMDrawer::GetBoundsRect(IASRect& boundsRect)
{
	sADMDrawer->GetBoundsRect(fDrawer, &boundsRect);
}

inline void IADMDrawer::GetClipRect(IASRect& clipRect)
{
	sADMDrawer->GetClipRect(fDrawer, &clipRect);
}

inline void IADMDrawer::SetClipRect(const IASRect& clipRect)
{
	sADMDrawer->SetClipRect(fDrawer, &clipRect);
}

inline void IADMDrawer::IntersectClipRect(const IASRect& clipRect)
{
	sADMDrawer->IntersectClipRect(fDrawer, &clipRect);
}

inline void IADMDrawer::UnionClipRect(const IASRect& clipRect)
{
	sADMDrawer->UnionClipRect(fDrawer, &clipRect);
}

inline void IADMDrawer::SubtractClipRect(const IASRect& clipRect)
{
	sADMDrawer->SubtractClipRect(fDrawer, &clipRect);
}

inline void IADMDrawer::SetClipPolygon(const IASPoint* points, int numPoints)
{
	sADMDrawer->SetClipPolygon(fDrawer, points, numPoints);
}

inline void IADMDrawer::IntersectClipPolygon(const IASPoint* points, int numPoints)
{
	sADMDrawer->IntersectClipPolygon(fDrawer, points, numPoints);
}

inline void IADMDrawer::UnionClipPolygon(const IASPoint* points, int numPoints)
{
	sADMDrawer->UnionClipPolygon(fDrawer, points, numPoints);
}

inline void IADMDrawer::SubtractClipPolygon(const IASPoint* points, int numPoints)
{
	sADMDrawer->SubtractClipPolygon(fDrawer, points, numPoints);
}

inline void IADMDrawer::GetOrigin(IASPoint& origin)
{
	sADMDrawer->GetOrigin(fDrawer, &origin);
}

inline void IADMDrawer::SetOrigin(const IASPoint& origin)
{
	sADMDrawer->SetOrigin(fDrawer, &origin);
}

inline void IADMDrawer::GetRGBColor(ADMRGBColor& color)
{
	sADMDrawer->GetRGBColor(fDrawer, &color);
}

inline void IADMDrawer::SetRGBColor(const ADMRGBColor& color)
{
	sADMDrawer->SetRGBColor(fDrawer, &color);
}

inline ADMColor IADMDrawer::GetADMColor()
{
	return sADMDrawer->GetADMColor(fDrawer);
}

inline void IADMDrawer::SetADMColor(ADMColor color)
{
	sADMDrawer->SetADMColor(fDrawer, color);
}

inline ADMDrawMode IADMDrawer::GetDrawMode()
{
	return sADMDrawer->GetDrawMode(fDrawer);
}

inline void IADMDrawer::SetDrawMode(ADMDrawMode drawMode)
{
	sADMDrawer->SetDrawMode(fDrawer, drawMode);
}

inline ADMFont IADMDrawer::GetFont()
{
	return sADMDrawer->GetFont(fDrawer);
}

inline void IADMDrawer::SetFont(ADMFont font)
{
	sADMDrawer->SetFont(fDrawer, font);
}

inline void IADMDrawer::DrawLine(const IASPoint& startPoint, const IASPoint& endPoint)
{
	sADMDrawer->DrawLine(fDrawer, &startPoint, &endPoint);
}

inline void IADMDrawer::DrawPolygon(const IASPoint* points, int numPoints)
{
	sADMDrawer->DrawPolygon(fDrawer, points, numPoints);
}

inline void IADMDrawer::FillPolygon(const IASPoint* points, int numPoints)
{
	sADMDrawer->FillPolygon(fDrawer, points, numPoints);
}

inline void IADMDrawer::DrawRect(const IASRect& rect)
{
	sADMDrawer->DrawRect(fDrawer, &rect);
}

inline void IADMDrawer::FillRect(const IASRect& rect)
{
	sADMDrawer->FillRect(fDrawer, &rect);
}

inline void IADMDrawer::ClearRect(const IASRect& rect)
{
	sADMDrawer->ClearRect(fDrawer, &rect);
}

inline void IADMDrawer::DrawSunkenRect(const IASRect& rect)
{
	sADMDrawer->DrawSunkenRect(fDrawer, &rect);
}

inline void IADMDrawer::DrawRaisedRect(const IASRect& rect)
{
	sADMDrawer->DrawRaisedRect(fDrawer, &rect);
}

inline void IADMDrawer::InvertRect(const IASRect& rect)
{
	sADMDrawer->InvertRect(fDrawer, &rect);
}

inline void IADMDrawer::DrawOval(const IASRect& rect)
{
	sADMDrawer->DrawOval(fDrawer, &rect);
}

inline void IADMDrawer::FillOval(const IASRect& rect)
{
	sADMDrawer->FillOval(fDrawer, &rect);
}

inline ADMAGMPortPtr IADMDrawer::GetAGMPort()
{
	return sADMDrawer->GetAGMPort(fDrawer);
}

inline void IADMDrawer::DrawAGMImage(AGMImageRecord* image, ADMFixedMatrix* matrix, long flags)
{
	sADMDrawer->DrawAGMImage(fDrawer, (struct _t_ADMAGMImageRecord*) image, matrix, flags);
}

inline void IADMDrawer::DrawADMImage(ADMImageRef image, const IASPoint& topLeftPoint)
{
	sADMDrawer->DrawADMImage(fDrawer, image, &topLeftPoint);
}

inline void IADMDrawer::DrawADMImageCentered(ADMImageRef image, const IASRect& rect)
{
	sADMDrawer->DrawADMImageCentered(fDrawer, image, &rect);
}

inline void IADMDrawer::DrawResPicture(SPPlugin* pluginRef, int resID, const IASPoint& topLeftPoint, ADMRecolorStyle style)
{
	sADMDrawer->DrawRecoloredResPicture(fDrawer, pluginRef, resID, &topLeftPoint, style);
}

inline void IADMDrawer::DrawResPictureCentered(SPPlugin* pluginRef, int resID, const IASRect& rect, ADMRecolorStyle style)
{
	sADMDrawer->DrawRecoloredResPictureCentered(fDrawer, pluginRef, resID, &rect, style);
}

inline void IADMDrawer::DrawIcon(ADMIconRef icon, const IASPoint& topLeftPoint, ADMRecolorStyle style)
{
	sADMDrawer->DrawRecoloredIcon(fDrawer, icon, &topLeftPoint, style);
}

inline void IADMDrawer::DrawIconCentered(ADMIconRef icon, const IASRect& rect, ADMRecolorStyle style)
{
	sADMDrawer->DrawRecoloredIconCentered(fDrawer, icon, &rect, style);
}

inline void IADMDrawer::GetResPictureBounds(struct SPPlugin* pluginRef, int resID, IASRect& boundsRect)
{
	sADMDrawer->GetResPictureBounds(fDrawer, pluginRef, resID, &boundsRect);
}

#ifdef USING_ZADM
inline int IADMDrawer::GetTextWidth( ASZString text )
{
	return sZADM->DrawerGetTextWidth( fDrawer, text );
}
#else
inline int IADMDrawer::GetTextWidth(const char* text)
{
	return sADMDrawer->GetTextWidth(fDrawer, text);
}
#endif

inline void IADMDrawer::GetFontInfo(const ADMFontInfo& fontInfo)
{
	sADMDrawer->GetFontInfo(fDrawer, (ADMFontInfo*)&fontInfo);
}

#ifdef USING_ZADM
inline void IADMDrawer::DrawText( const ASZString text, const IASPoint& point )
{
	sZADM->DrawerDrawText( fDrawer, const_cast< ASZString >( text ), const_cast< IASPoint* >(& point ) );
}
#else
inline void IADMDrawer::DrawText(const char* text, const IASPoint& point)
{
	sADMDrawer->DrawText(fDrawer, text, &point);
}
#endif

#ifdef USING_ZADM
inline void IADMDrawer::DrawTextLeft( const ASZString text, const IASRect& rect )
{
	sZADM->DrawerDrawTextLeft( fDrawer, const_cast< ASZString >( text ), const_cast< IASRect* >(& rect ) );
}
#else
inline void IADMDrawer::DrawTextLeft(const char* text, const IASRect& rect)
{
	sADMDrawer->DrawTextLeft(fDrawer, text, &rect);
}
#endif

#ifdef USING_ZADM
inline void IADMDrawer::DrawTextCentered( const ASZString text, const IASRect& rect )
{
	sZADM->DrawerDrawTextCentered( fDrawer, const_cast< ASZString >( text ), const_cast< IASRect* >(& rect ) );
}
#else
inline void IADMDrawer::DrawTextCentered(const char* text, const IASRect& rect)
{
	sADMDrawer->DrawTextCentered(fDrawer, text, &rect);
}
#endif

#ifdef USING_ZADM
inline void IADMDrawer::DrawTextRight( const ASZString text, const IASRect& rect )
{
	sZADM->DrawerDrawTextRight( fDrawer, const_cast< ASZString >( text ), const_cast< IASRect* >(& rect ) );
}
#else
inline void IADMDrawer::DrawTextRight(const char* text, const IASRect& rect)
{
	sADMDrawer->DrawTextRight(fDrawer, text, &rect);
}
#endif

inline void IADMDrawer::DrawUpArrow(const IASRect& rect)
{
	sADMDrawer->DrawUpArrow(fDrawer, &rect);
}	

inline void IADMDrawer::DrawDownArrow(const IASRect& rect)
{
	sADMDrawer->DrawDownArrow(fDrawer, &rect);
}	

inline void IADMDrawer::DrawLeftArrow(const IASRect& rect)
{
	sADMDrawer->DrawLeftArrow(fDrawer, &rect);
}	

inline void IADMDrawer::DrawRightArrow(const IASRect& rect)
{
	sADMDrawer->DrawRightArrow(fDrawer, &rect);
}	

#endif
