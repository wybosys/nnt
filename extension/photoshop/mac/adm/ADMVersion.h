/*******************************************************************************
*
* ADMVersion.h -- ADM Version Number
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 1996-2003 Adobe Systems Incorporated
* All Rights Reserved
*
* NOTICE: Adobe permits you to use, modify, and distribute this file in
* accordance with the terms of the Adobe license agreement accompanying it.
* If you have received this file from a source other than Adobe, then your use,
* modification, or distribution of it requires the prior written permission of
* Adobe.
*
********************************************************************************/

/** @file ADMVersion.h ADM Version Number */

#ifndef __ADMVERSION_H__
#define __ADMVERSION_H__


// -----------------------------------------------------------------------------
//	The version number is coded as BCD. It is available as symbols for each
//	component, a string, or a single long-int value. Be sure to update all
//	three in sync!

// The following denotes version 3.10:

#define ADMVMajor 0x03
#define ADMVMinor 0x10

// ADMVBuildType of 0x80 denotes a release stage of "final" and has nothing to
// do with the version number. (See the definition of the 'vers' resource in
// MacTypes.r.)

#define ADMVBuildType 0x80

// The separator (a character or string placed between the minor build number and
// the revision number, e.g. the "x" in 3.01x2

#define ADMVSeparator "x"

// The build number is not BCD; it's just a straight number.

#define ADMVBuildNumber 15

// ADMVFull is needed for the windows PiPL file. Here, the entire build number
// is expressed in BCD.

#define ADMVFull 0x0003110L

// The copyright string

#define ADMVCopyright "©2003-2006 Adobe Systems Incorporated"

/**
	ADM version
	
	The format is MAJOR.MINORxBUILD.
*/
#define ADMVString "3.10x15"


#endif	// __ADMVERSION_H__
