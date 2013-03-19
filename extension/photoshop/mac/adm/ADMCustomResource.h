/*******************************************************************************
*
* ADMCustomResource.h -- ADM Custom Resource Suite
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 1996-2001,2003 Adobe Systems Incorporated
* All Rights Reserved
*
* NOTICE: Adobe permits you to use, modify, and distribute this file in
* accordance with the terms of the Adobe license agreement accompanying it.
* If you have received this file from a source other than Adobe, then your use,
* modification, or distribution of it requires the prior written permission of
* Adobe.
*
********************************************************************************/

/** @file ADMCustomResource.h ADM Custom Resource Suite */

#ifndef __ADMCustomResource__
#define __ADMCustomResource__

#ifndef __SPPlugins__
#include "SPPlugs.h"
#endif

#ifndef __ADMDialog__
#include "ADMDialog.h"
#endif


#ifndef ASDataStreamRef
typedef struct t_ASDataStream* ASDataStreamRef;
#endif


// -----------------------------------------------------------------------------
//	Predefined resource formats

/** ... */
typedef struct ADMCustomResource* ADMCustomResourceRef;
/** ... */
typedef const char* ADMResourceType;

/** ... */
#define kADMDialogResource 		"ADM Dialog Resource"
/** ... */
#define kADMStringResource 		"ADM String Resource"
/** ... */
#define kADMListResource 		"ADM List Resource"
/** ... */
#define kADMIconResource		"ADM Icon Resource"
/** ... */
#define kASZStringDictionary	"ASZString Dictionary"
/** ... */
#define kADMMixedResource		"ADM Mixed Resource"


// -----------------------------------------------------------------------------
//	Error codes

/** ... */
#define kADMCustomResourceError 		'rErr'
/** ... */
#define kADMCustomResourceExistsError 	'!Unq'
/** ... */
#define kADMStreamUnavailableError 		'noSe'
/** ... */
#define kADMResourceNotFoundError		'r!fd'


// -----------------------------------------------------------------------------
//	SweetPea interface

/** ... */
#define kADMCustomResourceCaller "ADM Resource Caller"

	// for resource parsers
/** ... */
#define kADMReadSelector "ADM Read Resource"
/** ... */
#define kADMReloadSelector "ADM Reload Resource"

	// for composite parsers
/** ... */
#define kADMFindSelector "ADM Find Resource"
/** ... */
#define kADMReadSubResourceSelector "ADM Read Subresource"


/** ... */
typedef struct  
{
	/** ... */
	SPMessageData d;

	/** ... */
	ADMCustomResourceRef resourceRef;
	/** ... */
	ADMResourceType resourceType;
	
	/** ... */
	SPPluginRef resourcePlugin;
	/** ... */
	ADMInt32 resourceID;
	/** ... */
	const char* resourceName;

	/** ... */
	SPErr error;
	/** ... */
	ADMInt32  errorData;
}
ADMCustomResourceBaseMessage;


// -----------------------------------------------------------------------------
//	A composite resource parser can either create the object or
//	return a block of data to be handled by another parser.

/** ... */
typedef ADMErr ADMAPI ADMAllocateBlockProc(ADMInt32 inSize, void** outBlock);

/** ... */
typedef struct 
{

	/** ... */
	ADMCustomResourceRef forCustomResource;
			// For find and read subresource selectors, use this to return
			// the custom resource that can parse the data. If the composite
			// resource actually does the parsing instead of simply returning
			// data, it would return its own ADMCustomResourceRef.
	
	/** ... */
	ADMAllocateBlockProc* allocateBlock;
			// On the read subresource selector, use this function to allocate ...

	/** ... */
	void* returnedBlock;
			// ...this returned block, which contains the resource data.

	/** ... */
	ADMInt32 returnedSize;
			// The returned block is of this size.

}
ADMFoundResourceData;

/** ... */
typedef struct 
{
	/** ... */
	ADMCustomResourceBaseMessage r;
	
	/** ... */
	void* base;
	/** ... */
	void* makeProc;

	/** ... */
	ADMFoundResourceData subResource;
			// For composite resources only.
}
ADMCustomResourceMessage;


// -----------------------------------------------------------------------------
//	Dialog creation interface

/** ... */
#define kADMDialogCanRelayoutOption (1L << 2)

/** ... */
typedef void ADMAPI (*ADMMakeDialogWindowProc)(ADMDialogRef inDialog,
			ADMDialogStyle inDialogStyle, const char* inDialogName);

/** ... */
typedef void ADMAPI (*ADMCenterDialogWindowProc)(ADMDialogRef inDialog);
/** ... */
typedef ADMInt32 ADMAPI (*ADMGetDialogOptionsProc)(ADMDialogRef inDialog);
/** ... */
typedef void ADMAPI (*ADMSetDialogOptionsProc)(ADMDialogRef inDialog, ADMInt32 inOptions);


/** ... */
typedef struct 
{
	/** ... */
	ADMMakeDialogWindowProc makeDialogWindow;
	/** ... */
	ADMCenterDialogWindowProc centerDialogWindow;
	/** ... */
	ADMSetDialogOptionsProc setDialogOptions;
	/** ... */
	ADMGetDialogOptionsProc getDialogOptions;

}
ADMCustomDialogProcs;


/** ... */
typedef struct 
{	
	/** ... */
	ADMCustomResourceBaseMessage r;
	
	/** ... */
	ADMDialogRef createdDialog;
	/** ... */
	const ADMCustomDialogProcs* dialogProcs;

	/** ... */
	ADMFoundResourceData subResource;
			// For composite resources only.

}
ADMCustomDialogMessage;


/** ... */
typedef void ADMAPI (*ADMSetIconImageProc)(ADMIconRef inIcon, ADMImageRef inImage);
/** ... */
typedef ADMItemRef ADMAPI (*ADMGetIconItemProc)(ADMIconRef inIcon);

/** ... */
typedef struct 
{
	/** ... */
	ADMSetIconImageProc setImage;
	/** ... */
	ADMGetIconItemProc getItem;
}
ADMCustomIconProcs;


/** ... */
typedef struct 
{	
	/** ... */
	ADMCustomResourceBaseMessage r;
	
	/** ... */
	ADMIconRef createdIcon;
	/** ... */
	const ADMCustomIconProcs* iconProcs;

	/** ... */
	ADMFoundResourceData subResource;
			// For composite resources only.

}
ADMCustomIconMessage;


/** ... */
typedef ADMBoolean ADMAPI (*ADMListTypeProc)();

/** ... */
typedef struct 
{
	/** ... */
	ADMListTypeProc isHierarchical;
}
ADMCustomListProcs;


/** ... */
typedef struct 
{	
	/** ... */
	ADMCustomResourceBaseMessage r;
	
	/** ... */
	ADMListRef createdList;		// may be ADMHierarchyListRef,  use iHierarchical() function to determine cast/suite to use
	/** ... */
	const ADMCustomListProcs* listProcs;

	/** ... */
	ADMFoundResourceData subResource;
			// For composite resources only.

}
ADMCustomListMessage;


// Custom resource options

/** ... */
#define kADMCompositeResourceFile (1L << 0)			// atomic resources readers have priority
/** ... */
#define kADMUseLanguageCodeForFileSearch (1L << 1)	// for language specific 

/** ... */
typedef struct  
{
	/** ... */
	const char* name;
	/** ... */
	ADMInt32 version;
	/** ... */
	ADMInt32 kind;
	/** ... */
	const char* extension;
	/** ... */
	ADMInt32 options;
}
ADMCustomResourceInfo;


/** ... */
typedef struct
{
	/** ... */
	SPPluginRef resourcePlugin;
				// if != NULL, then it is in the resource

	/** ... */
	SPPlatformFileSpecification resourceFile;
				// else use this file data fork

	/** ... */
	void* resourceData;
				// else was a part of a composite resource and this is the data

	/** ... */
	ADMInt32 resourceSize;

}
ADMResourceLocationInfo;


// =============================================================================
//		* ADM Custom Resource Suite
// =============================================================================

/** ... */
#define kADMCustomResourceSuite			"ADM Custom Resource Suite"
/** ... */
#define kADMCustomResourceSuiteVersion3	3

// -----------------------------------------------------------------------------

/** ... */
typedef struct ADMCustomResourceSuite3
{
	// *** This suite is FROZEN.
	// *** It shipped with Illustrator 10.

		// FIX_ME [scouten 08/04/99]: These function names would make more sense
		// if all instances of "CustomResource" were replaced with "ResourceFormat."
		// A future version of this suite will do that.

	/** ... */
	ADMErr ADMAPI (*AddCustomResource)(SPPluginRef inPlugin, ADMResourceType inType,
				const ADMCustomResourceInfo* inResInfo,
				ADMCustomResourceRef* outFormat);

	/** ... */
	ADMErr ADMAPI (*RemoveCustomResource)(ADMResourceType inType, const char* inName,
				ADMInt32 inVersion);

	/** ... */
	ADMErr ADMAPI (*OpenResourceStream)(ADMCustomResourceRef inFormat, SPPluginRef inPlugin,
				ADMInt32 inResID, const char* inResName, ASDataStreamRef* outResStream);

	/** ... */
	ADMErr ADMAPI (*CloseResourceStream)(ASDataStreamRef inResStream);
	
	/** ... */
	ADMErr ADMAPI (*FindAResource)(SPPluginRef inPlugin, ADMResourceType inType,
				ADMInt32 inResID, const char* inResName, ADMResourceLocationInfo* outLocation);

	/** ... */
	ADMErr ADMAPI (*CountCustomResources)(ADMInt32* outCount);
	/** ... */
	ADMErr ADMAPI (*GetNthCustomResource)(ADMInt32 inIndex, ADMCustomResourceRef* outFormat);
	
	/** ... */
	ADMErr ADMAPI (*GetResourcePlugin)(ADMCustomResourceRef inFormat, SPPluginRef* outPlugin);
	/** ... */
	ADMErr ADMAPI (*GetResourceInfo)(ADMCustomResourceRef inFormat, ADMCustomResourceInfo* outInfo);
	/** ... */
	ADMErr ADMAPI (*GetResourceType)(ADMCustomResourceRef inFormat, ADMResourceType* outType);

	/** ... */
	ADMErr ADMAPI (*FindCustomResource)(ADMResourceType inResType,
				const ADMCustomResourceInfo* inResInfo,	ADMCustomResourceRef *outResource);

	/** ... */
	ADMErr ADMAPI (*RegisterResourceData)(const char* inCustomResourceName,
										ADMInt32 inCustomResourceVersion,
										SPPluginRef inPluginRef, ADMInt32 inID,
										const char* inData, ADMInt32 inDataSize);

	/** ... */
	ADMErr ADMAPI (*UnregisterResourceData)(const char* inCustomResourceName,
										  ADMInt32 inCustomResourceVersion,
										  SPPluginRef inPluginRef, ADMInt32 inID);
}
ADMCustomResourceSuite3;


// -----------------------------------------------------------------------------
//	Old versions of suites

#ifndef __ADMCustomResourceOld__
#ifdef MAC_ENV
#include "ADMCustomResourceOld.h"
#else
#include ".\Legacy\ADMCustomResourceOld.h"
#endif
#endif


#endif	// __ADMCustomResource__
