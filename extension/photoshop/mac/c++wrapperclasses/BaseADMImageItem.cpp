/***********************************************************************/
/*                                                                     */
/* BaseADMImageItem.cpp                                                */
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
/* Started by Dave Lazarony, 03/11/1996                                */
/*                                                                     */
/***********************************************************************/

/*
 * Includes
 */

#include "BaseADMImageItem.hpp"
#include "IADMDrawer.hpp"

//#include "AGMImage.h"

/*
 * Constructor
 */

BaseADMImageItem::BaseADMImageItem(IADMItem item, ADMUserData data) : BaseADMItem(item, data)								
{
	fImage = NULL;
}


/*
 * Destructor
 */

BaseADMImageItem::~BaseADMImageItem()
{
	if (fImage && sADMImage)
	{
		sADMImage->Destroy(fImage);
		fImage = NULL;
	}
}


/*
 * Virtual Functions that call Defaults.
 */
	
/*
 * Static Procs that call Virtual Functions.
 */
	
ASBoolean BaseADMImageItem::UseImage()
{
	return true;
}

void BaseADMImageItem::BaseDraw(IADMDrawer drawer)
{
	ASBoolean needNormalDraw = true;

	if (UseImage())
	{
		IASRect boundsRect;

		drawer.GetBoundsRect(boundsRect);
	
		if (fImage && (fImage.GetWidth() != boundsRect.Width() || fImage.GetHeight() != boundsRect.Height()))
		{
			sADMImage->Destroy(fImage);
			fImage = NULL;
		}

		if (!fImage)
			fImage = sADMImage->CreateOffscreen(boundsRect.Width(), boundsRect.Height());
		
		if (fImage)	
		{
			IADMDrawer imageDrawer = fImage.BeginADMDrawer();
			
			if (imageDrawer)
			{
				imageDrawer.ClearRect(boundsRect);
				
				Draw(imageDrawer);

				fImage.EndADMDrawer();

				needNormalDraw = false;
			}
			
			IASPoint point(0, 0);

			drawer.DrawADMImage(fImage, point);
		}
	}
	
	if (needNormalDraw)
		Draw(drawer);
}
