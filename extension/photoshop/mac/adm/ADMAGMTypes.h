/*******************************************************************************
*
* ADMAGMTypes.h -- Abstract references to AGM types for ADM interfaces
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 1999-2001,2003 Adobe Systems Incorporated
* All Rights Reserved
*
* NOTICE: Adobe permits you to use, modify, and distribute this file in
* accordance with the terms of the Adobe license agreement accompanying it.
* If you have received this file from a source other than Adobe, then your use,
* modification, or distribution of it requires the prior written permission of
* Adobe.
*
********************************************************************************/

/** @file ADMAGMTypes.h Abstract references to AGM types for ADM interfaces */

#ifndef _ADMAGMTYPES_H_
#define _ADMAGMTYPES_H_

#include "ADMTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Opaque color space */
typedef struct _t_ADMAGMColrSpace ADMAGMColorSpace;

/** Defined as int */
typedef int ADMAGMColorSpaceFamily;

/** Opaque AGM raster port */
typedef struct _t_ADMAGMRasterPort ADMAGMRasterPort;

/** Opaque AGM port */
typedef struct _t_ADMAGMPort ADMAGMPort;

/** Pointer to an AGM port */
typedef ADMAGMPort* ADMAGMPortPtr;

/** Color table */
typedef struct _t_ADMAGMColorTab ADMAGMColorTab;

/** Image record */
typedef struct _t_ADMAGMImageRecord ADMAGMImageRecord;

/** Line cap */
enum _ADMLineCap {
	/** Butt line caps */
	kButtCap = 0,
	/** Round line caps */
	kRoundCap,
	/** Projecting line caps */
	kProjectingCap
};

/** Line cap */
typedef enum _ADMLineCap ADMLineCap;

/** Color table */
struct _t_ADMAGMColorTab	{
	/** */
	ADMInt32	numColors;
	/** */
	void*	theColors;
};

/** Rectangle with 16 bit integer coordinates */
typedef struct _t_ADMAGMInt16Rect {
	/** */
	ADMInt16	xMin;
	/** */
	ADMInt16	yMin;
	/** */
	ADMInt16	xMax;
	/** */
	ADMInt16	yMax;
}
ADMAGMInt16Rect;

/** Image record */
struct _t_ADMAGMImageRecord	{
	/** */
	ADMAGMInt16Rect	bounds;
	/** */
	void*			baseAddr;
	/** */
	ADMInt32			byteWidth;
	/** */
	ADMInt16			colorSpace;
	/** */
	ADMInt16			bitsPerPixel;
	/** */
	float*		decodeArray;
	/** */
	ADMAGMColorTab	colorTab;
};

#ifdef __cplusplus
}
#endif

#endif // _ADMAGMTYPES_H_
