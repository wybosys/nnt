/*******************************************************************************
*
* ADMNotifier.h -- ADM Notifier Suite
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
* Started by Dave Lazarony, 06 Mar 1996
*
********************************************************************************/

/** @file ADMNotifier.h ADM Notifier Suite */

#ifndef __ADMNotifier__
#define __ADMNotifier__

#ifndef __ADMTypes__
#include "ADMTypes.h"
#endif


// -----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

#pragma ADM_PRAGMA_ALIGN_BEGIN
#pragma ADM_PRAGMA_IMPORT_BEGIN

// Mac OS headers #define GetItem, but we want to use it as a name.
#ifdef GetItem
#undef GetItem
#endif


// -----------------------------------------------------------------------------
//	Notifier type constants

/** ... */
#define kADMUserChangedNotifier "ADM User Changed Notifier"
/** ... */
#define kADMIntermediateChangedNotifier "ADM Intermediate Changed Notifier"
/** ... */
#define kADMBoundsChangedNotifier "ADM Bounds Changed Notifier"
/** ... */
#define kADMEntryTextChangedNotifier "ADM Entry Text Changed Notifier"
/** ... */
#define kADMCloseHitNotifier "ADM Close Hit Notifier"
/** ... */
#define kADMZoomHitNotifier "ADM Zoom Hit Notifier"
/** ... */
#define kADMCycleNotifier "ADM Cycle Notifier"
/** ... */
#define kADMCollapseNotifier "ADM Collapse Notifier"
/** ... */
#define kADMExpandNotifier "ADM Expand Notifier"
/** ... */
#define kADMContextMenuChangedNotifier "ADM Context Menu Changed Notifier"
/** ... */
#define kADMWindowShowNotifier "ADM Show Window Notifier"
/** ... */
#define kADMWindowHideNotifier "ADM Hide Window Notifier"
/** ... */
#define kADMGroupShowNotifier "ADM Show Group Notifier"
/** ... */
#define kADMGroupHideNotifier "ADM Hide Group Notifier"
/** ... */
#define kADMWindowActivateNotifier "ADM Activate Window Notifier"
/** ... */
#define	kADMWindowDeactivateNotifier "ADM Deactivate Window Notifier"
/** ... */
#define kADMNumberOutOfBoundsNotifier "ADM Number Out Of Bounds Notifier"
/** ... */
#define kADMWindowDragMovedNotifier "ADM Window Moved By Drag"

	// text item notifiers
/** ... */
#define	kADMPreClipboardCutNotifier "ADM Pre Clipboard Cut Notifier"
/** ... */
#define	kADMPostClipboardCutNotifier "ADM Post Clipboard Cut Notifier"
/** ... */
#define	kADMPreClipboardCopyNotifier "ADM Pre Clipboard Copy Notifier"
/** ... */
#define	kADMPostClipboardCopyNotifier "ADM Post Clipboard Copy Notifier"
/** ... */
#define	kADMPreClipboardPasteNotifier "ADM Pre Clipboard Paste Notifier"
/** ... */
#define	kADMPostClipboardPasteNotifier "ADM Post Clipboard Paste Notifier"
/** ... */
#define	kADMPreClipboardClearNotifier "ADM Pre Clipboard Clear Notifier"
/** ... */
#define	kADMPostClipboardClearNotifier "ADM Post Clipboard Clear Notifier"
/** ... */
#define kADMPreTextSelectionChangedNotifier "ADM Pre Selection Change Notification"
/** ... */
#define kADMTextSelectionChangedNotifier "ADM Text Selection Change Notification"

// [cpaduan] 12/04/00: new notifiers for undo/redo
/** ... */
#define	kADMPreClipboardRedoNotifier "ADM Pre Clipboard Redo Notifier"
/** ... */
#define	kADMPostClipboardRedoNotifier "ADM Post Clipboard Redo Notifier"
/** ... */
#define	kADMPreClipboardUndoNotifier "ADM Pre Clipboard Undo Notifier"
/** ... */
#define	kADMPostClipboardUndoNotifier "ADM Post Clipboard Undo Notifier"


// =============================================================================
//		* ADM Notifier Suite
// =============================================================================

/** ... */
#define kADMNotifierSuite "ADM Notifier Suite"
/** ... */
#define kADMNotifierSuiteVersion2 2

// -----------------------------------------------------------------------------

/** ... */
typedef struct ADMNotifierSuite2
{

	// *** This suite is FROZEN.
	// *** It shipped with Photoshop 5.5 and ImageReady 2.0.

	// notifier context

	/** ... */
	ADMItemRef ADMAPI (*GetItem)(ADMNotifierRef inNotifier);
	/** ... */
	ADMDialogRef ADMAPI (*GetDialog)(ADMNotifierRef inNotifier);

	// notifier type
	
	/** ... */
	ADMBoolean ADMAPI (*IsNotifierType)(ADMNotifierRef inNotifier, const char* inNotifierType);
	/** ... */
	void ADMAPI (*GetNotifierType)(ADMNotifierRef inNotifier, char* outNotifierType,
				ADMUInt32 inMaxLength);

	// notifier flags

	/** ... */
	void ADMAPI (*SkipNextClipboardOperation)(ADMNotifierRef inNotifier, ADMBoolean inSkip);
		
}
ADMNotifierSuite2;


// -----------------------------------------------------------------------------
//	Old versions of suites

#ifndef __ADMNotifierOld__
#ifdef MAC_ENV
#include "ADMNotifierOld.h"
#else
#include ".\Legacy\ADMNotifierOld.h"
#endif
#endif

// -----------------------------------------------------------------------------

#pragma ADM_PRAGMA_IMPORT_END
#pragma ADM_PRAGMA_ALIGN_END

#ifdef __cplusplus
}
#endif

// -----------------------------------------------------------------------------

#endif	// __ADMNotifier__
