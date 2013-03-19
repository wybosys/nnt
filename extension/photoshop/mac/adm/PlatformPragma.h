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

#ifndef __PlatformPragma__
#define __PlatformPragma__

#ifndef __PlatformConfig__
#include "PlatformConfig.h"
#endif


#ifdef MAC_ENV

#ifdef MACPPC_ENV

// Old definitions
#define	PRAGMA_ALIGN_BEGIN			options align=mac68k
#define PRAGMA_ALIGN_END			options align=reset
#define PRAGMA_IMPORT_BEGIN			import on
#define PRAGMA_IMPORT_END			import off

// Definitions for ADM headers
#ifdef MAC_MACHO_ENV

/* jsbache: 2004-2-12. Use 68K alignment everywhere.
The problem is that Acrobat redefines ADMTypes to be equal to ASTypes
As ASTypes are 68K aligned we cannot have a different alignment for ADMTypes.
We may want to revisit this when everything has been integrated into the Acrobat tress
*/
//#define	ADM_PRAGMA_ALIGN_BEGIN		options align=power
#define	ADM_PRAGMA_ALIGN_BEGIN		options align=mac68k

#else
#define	ADM_PRAGMA_ALIGN_BEGIN		options align=mac68k
#endif	// MAC_MACHO_ENV

#define ADM_PRAGMA_ALIGN_END		options align=reset
#define ADM_PRAGMA_IMPORT_BEGIN		import on
#define ADM_PRAGMA_IMPORT_END		import off
#endif

#ifdef MAC68K_ENV
#error 68K plugins no longer supported!
#endif

#endif

#ifdef WIN_ENV

// Old definitions
#define	PRAGMA_ALIGN_BEGIN			pack(push, 4)			
#define PRAGMA_ALIGN_END			pack(pop)
#define PRAGMA_IMPORT_BEGIN			
#define PRAGMA_IMPORT_END		

// Definitions for ADM headers
#define	ADM_PRAGMA_ALIGN_BEGIN		pack(push, 4)
#define ADM_PRAGMA_ALIGN_END		pack(pop)
#define ADM_PRAGMA_IMPORT_BEGIN			
#define ADM_PRAGMA_IMPORT_END		
#endif


#endif
