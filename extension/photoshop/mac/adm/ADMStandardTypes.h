/***********************************************************************/
/*                                                                     */
/* ADMStandardTypes.h                                                  */
/* Adobe Standard Types                                                */
/*                                                                     */
/* Copyright 1996-1999,2003 Adobe Systems Incorporated.                     */
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
/* Started by David Hearst, 05/20/2002                                 */
/*                                                                     */
/***********************************************************************/

/** @file ADMStandardTypes.h Adobe Standard Types */

#ifndef __ADMStandardTypes__
#define __ADMStandardTypes__

/*
 * Includes
 */
 
#ifndef __PlatformConfig__
#include "PlatformConfig.h"
#endif

#ifndef __PlatformPragma__
#include "PlatformPragma.h"
#endif


#ifdef __cplusplus
extern "C" {
#endif

#pragma ADM_PRAGMA_ALIGN_BEGIN
#pragma ADM_PRAGMA_IMPORT_BEGIN


/*
 * Constants
 */

// true and false

#ifndef __cplusplus	

#ifndef true
/** ... */
#define true	1
#endif

#ifndef false
/** ... */
#define false	0
#endif

#endif // __cplusplus

#ifndef TRUE
/** ... */
#define TRUE	true
#endif

#ifndef FALSE
/** ... */
#define FALSE	false
#endif

// error codes
/** ... */
#define kNoErr					0
/** ... */
#define kOutOfMemoryErr			'!MEM'
/** ... */
#define kBadParameterErr		'PARM'
/** ... */
#define kNotImplementedErr		'!IMP'
/** ... */
#define kCantHappenErr			'CANT'


// NULL

#ifndef NULL

#ifdef MAC_ENV
#if !defined(__cplusplus) && (defined(__SC__) || defined(THINK_C))
#define NULL	((void *) 0)
#else
/** ... */
#define NULL	0
#endif
#endif

#ifdef WIN_ENV
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#endif

// dhearst 8/11/99 - we now specifically prefer NULL, so nil
// is obsolete. We no longer provide it, but can't enforce this
// policy because platform headers often provide nil.
//#ifndef nil
//#define nil NULL
//#endif


// AMPAPI  Adobe Standard Plugin API calling convention.

#ifndef AMPAPI
#ifdef MAC_ENV
#define ADMAPI pascal
#endif
#ifdef WIN_ENV
#define ADMAPI
#endif
#endif

// C calling convention for those places that need it.
// This doesn't really do anything, but is  more for
// an explicity declaration when it matters.
#define ADMCAPI	


/*
 * Types
 */

// Integer Types

/** ... */
typedef signed char ADMInt8;
/** ... */
typedef signed short ADMInt16;
/** ... */
typedef signed long ADMInt32;

/** ... */
typedef unsigned char ADMUInt8;
/** ... */
typedef unsigned short ADMUInt16;
/** ... */
typedef unsigned long ADMUInt32;

/** ... */
typedef long ADMErr;

// Storage Types

/** ... */
typedef unsigned char ADMByte;
/** ... */
typedef ADMByte* ADMBytePtr;

// Unicode Types
/** ... */
typedef ADMUInt16 ADMUnicode;

// Pointer Types

/** ... */
typedef void* ADMPtr;
/** ... */
typedef void** ADMHandle;

// Fixed Types

/** ... */
typedef	long ADMFixed;
/** ... */
typedef long ADMFract;
/** ... */
typedef float ADMReal;

/** ... */
typedef struct _t_ADMFixedPoint {
	/** ... */
	ADMFixed h, v;
} ADMFixedPoint;

/** ... */
typedef struct _t_ADMFixedRect {
	/** ... */
	ADMFixed left, top, right, bottom;
} ADMFixedRect;

/** ... */
typedef struct _t_ADMFixedMatrix {
	/** ... */
	ADMFixed a, b, c, d, tx, ty;
} ADMFixedMatrix;

/** ... */
typedef struct _t_ADMRealPoint {
	/** ... */
	ADMReal h, v;
} ADMRealPoint;

/** ... */
typedef struct _t_ADMRealRect {
	/** ... */
	ADMReal left, top, right, bottom;
} ADMRealRect;

/** ... */
typedef struct _t_ADMRealMatrix {
	/** ... */
	ADMReal a, b, c, d, tx, ty;
} ADMRealMatrix;


// Platform Structures

#ifdef MAC_ENV


// ADMBoolean is the same a Macintosh Boolean.
typedef unsigned char ADMBoolean; 

// ADMPortRef is the same as a Macintosh GrafPtr.
#if Platform_Carbon
typedef struct OpaqueGrafPtr* ADMPortRef;
#else
typedef struct GrafPort* ADMPortRef;
#endif

// ADMWindowRef is the same as a Macintosh WindowPtr.
#if Platform_Carbon
typedef struct OpaqueWindowPtr* ADMWindowRef;
#else
typedef struct GrafPort* ADMWindowRef;
#endif

// Set alignment of Macintosh types to match alignment in the MacOS headers
#ifdef MAC_ENV
#pragma options align=mac68k
#endif

// ADMRect is the same size and layout as a Macintosh Rect.
typedef struct _t_ADMRect {
	/** ... */
	short top, left, bottom, right;
} ADMRect;

// ADMPoint is the same size and layout as a Macintosh Point.
typedef struct _t_ADMPoint {
	/** ... */
	short v, h;
} ADMPoint;

#ifdef MAC_ENV
#pragma options align=reset
#endif


#endif


#ifdef WIN_ENV

// ADMBoolean is the same a Windows BOOL.
/** Windows definition */
typedef int ADMBoolean;

// ADMPortRef is the same as a Windows HDC.
/** Windows definition */
typedef void* ADMPortRef;				

// ADMWindowRef is the same as a Windows HWND.
/** Windows definition */
typedef void* ADMWindowRef;			

// ADMRect is the same size and layout as a Windows RECT.
/** Windows definition */
typedef struct _t_ADMRect {
	/** ... */
	long left, top, right, bottom;
} ADMRect;

// ADMPoint is the same size and layout as a Windows POINT.
/** Windows definition */
typedef struct _t_ADMPoint  {
	/** ... */
	long h, v;
} ADMPoint;

#endif

// Set alignment of Macintosh types to match alignment in the MacOS headers
#ifdef MAC_ENV
#pragma options align=mac68k
#endif

// ADMRGBColor is the same as a Macintosh RGBColor on Macintosh and Windows.
/** ... */
typedef struct _t_ADMRGBColor {
	/** ... */
	unsigned short red, green, blue;
} ADMRGBColor;


// AIEvent is the same as a Macintosh EventRecord on Macintosh and Windows.
/** ... */
typedef struct _t_ADMEvent {
	/** ... */
	unsigned short	what;
	/** ... */
	unsigned long	message;
	/** ... */
	unsigned long	when;
	/** ... */
	ADMPoint			where;
	/** ... */
	unsigned short	modifiers;
} ADMEvent;

#ifdef MAC_ENV
#pragma options align=reset
#endif


// This is a generic reference to a resource/plugin file.  If not otherwise stated,
// it is assumed to be equivalent to an SPPluginRef (see "SPPlugs.h")
/** ... */
typedef struct ADMAccess* ADMAccessRef;



#pragma ADM_PRAGMA_IMPORT_END
#pragma ADM_PRAGMA_ALIGN_END

#ifdef __cplusplus
}
#endif


#endif
