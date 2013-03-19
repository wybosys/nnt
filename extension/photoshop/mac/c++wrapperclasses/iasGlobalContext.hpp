#ifndef __IASGlobalContext_hpp__
#define __IASGlobalContext_hpp__

/*
 *        Name:	IASGlobalContext.hpp
 *   $Revision: 1 $
 *      Author:	Dave Lazarony 
 *        Date:	4/12/96					  
 *     Purpose:	Creates a Global Context for setting up globals in Mac 68K Code Resources.
 *
 *				Declare a IASMain68KContext in the main() of the Code Resource.
 *
 *				Declare a IASCallback68KContext in each callback routine.
 *
 *				NOTE:  suite entry points are callback routines.
 *
 * Copyright (c) 1986-1996 Adobe Systems Incorporated, All Rights Reserved.
 *
 */

#ifdef __MWERKS__
#warning *** THIS FILE IS OBSOLETE now that 68K code is no longer supported. ***
#else
#pragma warning // *** THIS FILE IS OBSOLETE now that 68K code is no longer supported. ***
#endif

#ifndef __ASTypes__
#include "ASTypes.h"
#endif

#ifdef MAC68K_ENV

	#include "A4Stuff.h"
	
	class IASGlobalContext
	{
	private:
		long saveA4;
		
	public:
		IASGlobalContext()
		{
			saveA4 = SetCurrentA4();		// Save A4 away and set A4 to point to the code resources globals.
		}
		
		~IASGlobalContext() 
		{
			SetA4(saveA4);					// Set A4 back.
		}
	};

#else

	class IASGlobalContext
	{
	public:
		IASGlobalContext() {}
		~IASGlobalContext() {}
	};

#endif

#endif