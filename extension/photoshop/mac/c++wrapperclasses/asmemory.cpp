/*
 *        Name:	ASMemory.cpp
 *   $Revision: 3 $
 *      Author:	Dave Lazarony 
 *        Date:	6/28/94
 *     Purpose:	ASMemory.cpp is used to manage memory allocations through SweetPea.
 *				This file declares the new and delete operators for memory allocation within 
 *				a plug-in.
 *
 * Copyright (c) 1986-1996 Adobe Systems Incorporated, All Rights Reserved.
 *
 */

#include "ASTypes.h"
#include "SPBasic.h"
#include <stdlib.h>
#include <string.h>

#ifdef __MWERKS__
#warning *** THIS FILE IS OBSOLETE. Please use PPMemoryViaSP.cpp in PowerPlug instead. ***
#else
#pragma warning // *** THIS FILE IS OBSOLETE. Please use PPMemoryViaSP.cpp in PowerPlug instead. ***
#endif

extern "C" SPBasicSuite *sSPBasic;


//-------------------------------------------------------------------------
//
// operator new -- Allocate memory using SweetPea/PICA.
//
void*
operator new( size_t size )
{
	void* addr = 0;
	
	if ( sSPBasic )
	{
		 ASErr error = sSPBasic->AllocateBlock( size, &addr );
		 if ( error )
		 {
		 	addr = 0;
		 }
		 else
		 {
#ifdef DEBUG
			// Fill memory with easily identifiable garbage.
			const ASByte kGarbage = 0xCC;
			memset( addr, kGarbage, size );
#else
			// Non-debug: Clear memory.
			memset( addr, 0, size );
#endif
		 }
	}
//	else
//		DebugStr("\p new() called without sSPBlocks");
	
	return addr;
}


//-------------------------------------------------------------------------
//
// operator delete -- Release memory.
//
void
operator delete( void* p )
{
	if ( sSPBasic )
	{
		 (void) sSPBasic->FreeBlock( p );
	}
//	else
//		DebugStr("\p delete() called without sSPBlocks");
}
