/*******************************************************************************
*
* ADOBE CONFIDENTIAL
* ------------------
*
* Copyright 2002 Adobe Systems Incorporated
* All Rights Reserved.
*
* NOTICE: All information contained herein is, and remains the property of Adobe
* Systems Incorporated and its suppliers, if any. The intellectual and technical
* concepts contained herein are proprietary to Adobe Systems Incorporated and
* its suppliers and may be covered by U.S. and Foreign Patents, patents in
* process, and are protected by trade secret or copyright law. Dissemination of
* this information or reproduction of this material is strictly forbidden unless
* prior written permission is obtained from Adobe Systems Incorporated.
*
* Started by David Hearst, 05 Jun 2002
*
********************************************************************************/

#ifndef __PlatformConfig__
#define __PlatformConfig__

/*
 * Defines for MPW and THINK C.
 */
#if defined(macintosh) || defined(THINK_C)
#ifndef MAC_ENV
#define MAC_ENV
#endif
#endif

/*
 * Defines for Metrowerks on Macintosh.
 */
#ifdef __MWERKS__

#if defined(__MC68K__) || defined(__POWERPC__)
#ifndef MAC_ENV
#define MAC_ENV
#endif
#endif

#ifdef __MC68K__
#error 68K plugins no longer supported!
#endif

#ifdef __POWERPC__
#ifndef MACPPC_ENV
#define MACPPC_ENV
#endif
#endif

#ifdef __MACH__
#ifndef MAC_MACHO_ENV
#define MAC_MACHO_ENV
#endif	// MAC_MACHO_ENV
#endif	// __MACH__

#endif


/*
 * Defines for Metrowerks on Windows.
 */
#ifdef __MWERKS__
#ifdef __INTEL__
#ifndef WIN_ENV
#define WIN_ENV
#endif
#endif
#endif

/*
 * Defines for Visual C++ on Windows.
 */
#ifdef _WINDOWS
#ifndef WIN_ENV
#define WIN_ENV
#endif
#endif

#endif
