/***********************************************************************/
/*                                                                     */
/* BaseADMImageItem.hpp                                                */
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
/* Started by Dave Lazarony, 03/06/1996                                */
/*                                                                     */
/***********************************************************************/

#ifndef __BaseADMImageItem_hpp__
#define __BaseADMImageItem_hpp__

/*
 * Includes
 */
 
#ifndef __BaseADMItem_hpp__
#include "BaseADMItem.hpp"
#endif

#ifndef __IADMImage_hpp__
#include "IADMImage.hpp"
#endif

class IADMDrawer;
class IADMNotifier;
class IADMTracker;


/*
 * Base Class
 */

class BaseADMImageItem : public BaseADMItem
{

protected:
	IADMImage fImage;

	virtual ASBoolean UseImage();
	virtual void BaseDraw(IADMDrawer drawer);

public:	
	BaseADMImageItem(IADMItem item, ADMUserData data = NULL);
	
	virtual ~BaseADMImageItem();
};

#endif