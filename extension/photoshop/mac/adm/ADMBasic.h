/*******************************************************************************
*
* ADMBasic.h -- ADM Basic Suite
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
* Started by Dave Lazarony, 09 Mar 1996
*
********************************************************************************/

/** @file ADMBasic.h ADM Basic Suite */

#ifndef __ADMBasic__
#define __ADMBasic__
 
#ifndef __ADMTypes__
#include "ADMTypes.h"
#endif


// -----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

#pragma ADM_PRAGMA_ALIGN_BEGIN
#pragma ADM_PRAGMA_IMPORT_BEGIN

// -----------------------------------------------------------------------------

/**
	Used in file type specifications

	@see ADMPlatformFileTypesSpecification3 ADMPlatformFileTypesSpecification
*/
#define kADMMaxFilterLength (256)

/**
	Return values for various functions

	<b>Note:</b> ADM follows the C language convention in enumerated lists,
	i.e., when an enumerated list starts with an assignment value, subsequent
	entries are given consecutively numbered values. Thus, kADMYesAnswer =1,
	kADMCancelAnswer =2, etc., until the list is exhausted or a new value is
	assigned to an entry.
*/
enum ADMAnswer
{
	/** */
	kADMNoAnswer = 0,
	/** */
	kADMYesAnswer,
	/** */
	kADMCancelAnswer,
	/** */
	kADMDummyAnswer = 0xFFFFFFFF
};

#ifndef __cplusplus 
typedef enum ADMAnswer ADMAnswer; 
#endif

/**
	Choice values for various functions

	<b>Note:</b> ADM follows the C language convention in enumerated lists,
	i.e., when an enumerated list starts with an assignment value, subsequent
	entries are given consecutively numbered values. Thus, kADMRightAnswer =1,
	kADMMiddleAnswer =2, etc., until the list is exhausted or a new value is
	assigned to an entry.
*/
enum ADMChoice
{
	/** */
	kADMLeftAnswer = 0,
	/** */
	kADMRightAnswer,
	/** */
	kADMMiddleAnswer,
	/** */
	kADMDummyChoice = 0xFFFFFFFF
};

#ifndef __cplusplus 
typedef enum ADMChoice ADMChoice; 
#endif

// -----------------------------------------------------------------------------

#ifdef MAC_ENV

	/**
		File type specification

		The documented fields are defined for the Macintosh environment.
		For all other environments, the struct has a single member,
		'filter', which is an array of chars of length kADMMaxFilterLength.
	*/
	struct _t_ADMPlatformFileTypesSpecification
	{
		/** */
		ADMUInt32* types;
		/** */
		ADMInt16 numTypes;
	};

	/**
		File type specification
	*/
	typedef struct _t_ADMPlatformFileTypesSpecification ADMPlatformFileTypesSpecification;

	/**
		File type specification

		The following fields are defined for the Macintosh environment.
		For all other environments, the struct has a single member,
		'filter', which is an array of chars of length kADMMaxFilterLength.
	*/
	struct _t_ADMPlatformFileTypesSpecification3
	{
		/** */
		ADMUInt32* types;
		/** */
		ADMInt16 numTypes;
		/** */
		char filter[kADMMaxFilterLength];
	};

	/**
		File type specification
	*/
	typedef struct _t_ADMPlatformFileTypesSpecification3 ADMPlatformFileTypesSpecification3;

#else

	typedef struct
	{
		char filter[kADMMaxFilterLength];
	}
	ADMPlatformFileTypesSpecification, ADMPlatformFileTypesSpecification3;

#endif


// =============================================================================
//		* ADM Basic Suite
// =============================================================================

/// Basic suite name
#define kADMBasicSuite ("ADM Basic Suite")

/// Basic suite version
#define kADMBasicSuiteVersion8 (8)

// -----------------------------------------------------------------------------

/**
	ADM Basic suite

	The ADM Basic suite provides four types of functions:

	Resource Functions			<br>
	User Interface Functions	<br>
	Utility Functions			<br>
	Contextual Menu Functions

	The suite is acquired as follows:

<pre>
ADMBasicSuite *sADMBasic;
error = sSPBasic->AcquireSuite(kADMBasicSuite, kADMBasicSuiteVersion, &sADMBasic);
if (error) goto error;
</pre>

	@see kADMBasicSuite for the name of the suite.
	@see kADMBasicSuiteVersion8 for the version of the suite.
*/
typedef struct ADMBasicSuite8
{

	// *** This suite is FROZEN.
	// *** It shipped with Illustrator 10.

	/** @name Resource Functions
	*/
	//@{
	/**
		Returns a platform string resource, pointed to by 'outString'.
		
		The returned string is a C style string.

		On the Macintosh, this function reads strings from a ’STR#’ string list
		resource. The strings are converted from Pascal to C strings. Under Windows,
		the function reads a string from a string resource. The inStringID is the
		’STR#’ resource ID. The inStringIndex is the 1-based index of the string
		in the list.The inStringID and inStringIndex values are added together to
		produce the resource ID to be read.

		<b>Note:</b> Because Macintosh string list resources are 1-based, use a
		dummy argument for inStringID.

		<b>Example:</b>

		Assume that

		kMenuStrings < First Mac index is 1 >	<br>
		(kMenuStrings + 1) "My Menu Item"		<br>
		(kMenuStrings + 2) "My Other Menu Item"

		This same code would work on any platform:

<pre>
#define kMaxMenuLen 32
int strLength;
char menuString[kMaxMenuLen]

strLength = sADMBasic->GetIndexString( message->d.plugin, kMenuStrings,
    1, menuString, kMaxMenuLen);
</pre>

		@param inPluginRef		Plug-in reference.
		@param inStringID		The resource ID.
		@param inStringIndex	1-based index of the string in the list.
		@param outString		The returned string.
		@param inMaxLen			Maximum number of characters to be read.

		@return	The number of characters actually read.
	*/
	ADMErr ADMAPI (*GetIndexString)(SPPluginRef inPluginRef, ADMInt32 inStringID,
				ADMInt32 inStringIndex, char* outString, ADMInt32 inMaxLen);

	/**
		Returns a platform string resource, pointed to by 'outString'.

		This is the same as GetIndexString(), but the returned string is a Unicode string.

		@see GetIndexString()
	*/
	ADMErr ADMAPI (*GetIndexStringW)(SPPluginRef inPluginRef, ADMInt32 inStringID,
				ADMInt32 inStringIndex, ADMUnicode* outString, ADMInt32 inMaxLen);
	//@}

	/** @name User Interface Functions
		
		User interface functions control basic user communications such as beeps,
		alerts, and tool tips.

		<b>Note:</b> Tool tips provide information about the ADM item currently pointed
		to by the mouse cursor. A predefined string describing the item appears to the
		right of the item after the mouse is positioned over it for a few seconds. When
		the mouse is moved, the tool tip disappears. The strings to use for a dialog are
		defined with the ADMDialog->LoadToolTips.  For Illustrator and other Adobe tools,
		the tool title is used for the tool tip.

		@see ADMDialog->LoadToolTips()
	*/
	//@{
	/**
		Causes a simple system beep
		
		The platform’s standard beep function is called.

		@param None.

		@return None.
	*/
	void ADMAPI (*Beep)();

	/**
		Informs the user that an error occured.
		
		The text inErrorString is displayed to the user with an OK button.
		The platform’s icon for an error is displayed to the left of the string.

		@param inErrorString	Error string text.

		@return None.

		@see MessageAlert() LightweightErrorAlert() QuestionAlert()
		     SetAlertButtonText() YesNoAlert()
	*/
	void ADMAPI (*ErrorAlert)(const char* inErrorString);

	/**
		Informs the user that an error occured.

		This is the same as ErrorAlert(), but the returned string is a Unicode string.

		@see ErrorAlert()
	*/
	void ADMAPI (*ErrorAlertW)(const ADMUnicode* inErrorString);

	/**
		Displays an informational message to the user.
		
		The text inMessageString is displayed to the user with an OK button.
		The platform’s icon for a message will be displayed to the left of the string.

		@param inMessageString	Message string text.

		@return None.

		@see ErrorAlert() LightweightErrorAlert() QuestionAlert()
	*/
	void ADMAPI (*MessageAlert)(const char* inMessageString);
	
	/**
		Displays an informational message to the user.

		This is the same as MessageAlert(), but the returned string is a Unicode string.

		@see MessageAlert()
	*/
	void ADMAPI (*MessageAlertW)(const ADMUnicode* inMessageString);

	/**
		Asks the user a "yes" or "no" question.
		
		The text inQuestionString is displayed to the user along with Yes, No, and
		Cancel buttons.

		The return value is one of type ADMAnswer.

		@param inQuestionString		Alert string text.

		@return Enumerated value of type ADMAnswer.

  		@see ErrorAlert() LightweightErrorAlert() MessageAlert()
		     SetAlertButtonText() YesNoAlert()
	*/
	ADMAnswer ADMAPI (*QuestionAlert)(const char* inQuestionString);

	/**
		Asks the user a "yes" or "no" question.

		This is the same as QuestionAlert(), but the returned string is a Unicode string.

		@see QuestionAlert()
	*/
	ADMAnswer ADMAPI (*QuestionAlertW)(const ADMUnicode* inQuestionString);

	/**
		Creates a simple "yes" or "no" type alert dialog.
		
		The text inQuestionString is displayed to the user along with Yes, No, and
		Cancel buttons.

		The return value is one of type ADMAnswer.

		@param inQuestionString		Alert string text.
		
		@return Enumerated value of type ADMAnswer.

    	@see ErrorAlert() LightweightErrorAlert() QuestionAlert()
		     MessageAlert() SetAlertButtonText()
	*/
	ADMAnswer ADMAPI (*YesNoAlert)(const char* inQuestionString);

	/**
		Creates a simple "yes" or "no" type alert dialog.

		This is the same as YesNoAlert(), but the returned string is a Unicode string.

		@see YesNoAlert()
	*/
	ADMAnswer ADMAPI (*YesNoAlertW)(const ADMUnicode* inQuestionString);
	//@}

	/** @name Utility Functions
	*/
	//@{
	/**
		Returns the dimensions of the primary screen.
		
		Finds the bounds of the screen containing inPoint. Designed to work with
		both Windows and Mac platforms and supports multiple monitor setups.

		@param inPoint			A point on the screen. Type: ADMPoint
		@param outDimensions	Screen dimensions. Type: ADMRect

		@return true if inPoint is on any screen; false otherwise.
	*/
	ADMBoolean ADMAPI (*GetScreenDimensions)(const ADMPoint* inPoint, ADMRect* outDimensions);
	//@}

	/** @name User Interface Functions
	*/
	//@{
	/**
		Turns ADM tool tips on and off.
		
		When on, ADM tool tips appear next to an ADM Dialog Item (when a tool tip
		string is available for the item).

		@param inEnable		Boolean indicating whether tool tips should be turned on
							(true) or off (false).

		@return None.

		@see HideToolTip() ShowToolTip() AreToolTipsEnabled() AreToolTipsSticky()
	*/
	void ADMAPI (*EnableToolTips)(ADMBoolean inEnable);

	/**
		Determines whether ADM tool tips are currently on or off.

		@param None.

		@return true if tool tips are on; false otherwise.

		@see EnableToolTips() HideToolTip() ShowToolTip() AreToolTipsSticky()
	*/
	ADMBoolean ADMAPI (*AreToolTipsEnabled)();
	//@}

	/** @name Utility Functions
	*/
	//@{
	/**
		Converts between float inValue and C string outText.
		
		If indicated, inUnits is used to scale the value before it is converted.
		inPrecision indicates the maximum number of decimal places that are used in the
		final string. If the units value should be appended to the string, set
		inAlwaysAppendUnits to true.

		Units values and their scale are given in StringToValue() above.

		@param inValue				Floating point value to convert to a C string.
		@param outText				inValue converted to a C string.
		@param inMaxLen				Maximum length for string outText.
		@param inUnits				Used to scale inValue before conversion.
									Type: ADMUnits
		@param inPrecision			Maximum number of decimal places that are used in the
									final string.
		@param inAlwaysAppendUnits	If true, units are appended to string.

		@return None.

		@see StringToValue()
	*/
	void ADMAPI (*ValueToString)(float inValue, char* outText, ADMInt32 inMaxLen,
				ADMUnits inUnits, ADMInt32 inPrecision, ADMBoolean inAlwaysAppendUnits);

	/**
		Converts between float inValue and Unicode string outText.

		This is the same as ValueToString(), but outText is a Unicode string.

		@see ValueToString()
	*/
	void ADMAPI (*ValueToStringW)(float inValue, ADMUnicode* outText, ADMInt32 inMaxLen,
				ADMUnits inUnits, ADMInt32 inPrecision, ADMBoolean inAlwaysAppendUnits);

	/**
		Converts between C string inText and float outValue in points.
		
		If indicated, inUnits is used to scale the result.

		@param inText		Floating point value to convert to a C string.
		@param outValue		inValue converted to a C string.
		@param inUnits		Used to scale inValue after conversion. Type: ADMUnits

		@return true if the conversion was successful; false otherwise.

  		@see ValueToString()
	*/
	ADMBoolean ADMAPI (*StringToValue)(const char* inText, float* outValue, ADMUnits inUnits);

	/**
		Converts between Unicode string inText and float outValue in points.

		This is the same as StringToValue(), but inText is a Unicode string.

		@see StringToValue()
	*/
	ADMBoolean ADMAPI (*StringToValueW)(const ADMUnicode* inText, float* outValue, ADMUnits inUnits);
	//@}

	/** @name User Interface Functions
	*/
	//@{
	/**
		Opens the platform standard open file dialog.
		
		The text inMessage displays at the top of the dialog. inFilter determines
		what information is displayed in the dialog. inStartingDir selects the starting
		directory to be displayed and inStartingFile selects the starting file. The selected
		file is returned in outResult.

		@param inMessage		Text displayed at the top of the dialog.
		@param inFilter			Filter that determines what information is displayed.
								On the Macintosh platform you can list files, types, and/or
								extensions. On the Windows platform you can list files with
								extensions. Type: ADMPlatformFileTypesSpecification3
		@param inStartingDir	Starting directory. Type: SPPlatformFileSpecification
		@param inStartingFile	Starting file.
		@param outResult		File selected by user. Type: SPPlatformFileSpecification

		@return true if file was found and returned; false otherwise.

  		@see StandardPutFileDialog() StandardGetDirectoryDialog()
	*/
	ADMBoolean ADMAPI (*StandardGetFileDialog)(const char* inMessage,
				const ADMPlatformFileTypesSpecification3* inFilter,
				const SPPlatformFileSpecification* inStartingDir,
				const char* inStartingFile, SPPlatformFileSpecification* outResult);

	/**
		Opens the platform standard open file dialog.

		This is the same as StandardGetFileDialog(), but inMessage is a Unicode string.

		@see StandardGetFileDialog()
	*/
	ADMBoolean ADMAPI (*StandardGetFileDialogW)(const ADMUnicode* inMessage,
				const ADMPlatformFileTypesSpecification3* inFilter,
				const SPPlatformFileSpecification* inStartingDir,
				const char* inStartingFile, SPPlatformFileSpecification* outResult);

	/**
		Opens the platform standard open directory dialog.
		
		inStartingDir selects the starting directory. The selected
		directory is returned in outResult.

		@param inMessage		Text displayed at the top of the dialog.
		@param inStartingDir	Starting directory. Type: SPPlatformFileSpecification
		@param outResult		Directory selected by user. Type: SPPlatformFileSpecification

		@return true if directory was found and returned; false otherwise.

    	@see StandardGetFileDialog() StandardPutFileDialog()
	*/
	ADMBoolean ADMAPI (*StandardGetDirectoryDialog)(const char* inMessage,
				const SPPlatformFileSpecification* inStartingDir,
				SPPlatformFileSpecification* outResult);

	/**
		Opens the platform standard open directory dialog.

		This is the same as StandardGetDirectoryDialog(), but inMessage is a Unicode string.

		@see StandardGetDirectoryDialog()
	*/
	ADMBoolean ADMAPI (*StandardGetDirectoryDialogW)(const ADMUnicode* inMessage,
				const SPPlatformFileSpecification* inStartingDir,
				SPPlatformFileSpecification* outResult);

	/**
		Opens the platform standard save file dialog.
		
		The text inMessage displays at the top of the dialog. inFilter determines what
		information is displayed in the dialog. inStartingDir selects the starting directory
		to be displayed and inStartingFile selects the starting file. The selected file is
		returned in outResult.

		@param inMessage		Text displayed at the top of the dialog.
		@param inFilter			Filter that determines what information is displayed.
								On the Macintosh platform you can list files, types, and/or
								extensions. On the Windows platform you can list files with
								extensions. Type: ADMPlatformFileTypesSpecification3
		@param inStartingDir	Starting directory. Type: SPPlatformFileSpecification
		@param inStartingFile	Starting file.
		@param outResult		File selected by user. Type: SPPlatformFileSpecification

		@return true if file was saved; false otherwise.

      	@see StandardGetFileDialog() StandardGetDirectoryDialog()
	*/
	ADMBoolean ADMAPI (*StandardPutFileDialog)(const char* inMessage,
				const ADMPlatformFileTypesSpecification3* inFilter,
				const SPPlatformFileSpecification* inStartingDir,
				const char* inStartingFile, SPPlatformFileSpecification* outResult);

	/**
		Opens the platform standard save file dialog.

		This is the same as StandardPutFileDialog(), but inMessage is a Unicode string.

		@see StandardPutFileDialog()
	*/
	ADMBoolean ADMAPI (*StandardPutFileDialogW)(const ADMUnicode* inMessage,
				const ADMPlatformFileTypesSpecification3* inFilter,
				const SPPlatformFileSpecification* inStartingDir,
				const char* inStartingFile, SPPlatformFileSpecification* outResult);

	/**
		Invokes the standard platform color picker.
		
		Position (0, 0) centers the dialog on the screen.

		@param inWhere	The position argument; determines the location of the dialog.
						Type: ADMPoint
		@param inColor	Allows for setting of initial "picked" color values.
						Type: ADMRGBColor
		@param outColor	Returns the selected color. Type: ADMRGBColor

		@return true if the new color should be used; false otherwise.

  		@see ADMColorToRGBColor()
	*/
	ADMBoolean ADMAPI (*ChooseColor)(ADMPoint inWhere, const ADMRGBColor* inColor,
				ADMRGBColor* outColor);
	//@}

	/** @name Utility Functions
	*/
	//@{
	/**
		Sets the units being used by the application.

		ADM provides a system for storing 11 distinct unit preferences that may be used for
		various purposes within an application or plug-in. The first argument to
		SetAppUnits(), inAppUnits, is used to specify which unit preference is being set
		(#1-11), while the second argument, inActualUnits, is used to set the units for that
		particular unit preference. The sADMBasic->GetAppUnits() function takes only
		an inAppUnits argument and returns theinActualUnits .

		As an example of how to use these functions, an application might use app unit #1 as
		the default units for most measurements and app unit #2 as the default units for
		typographic measurements. At any one time, app units #1 may be inches and app
		units #2 may be points, or app units #1 may be centimeters, and app units #2 may be
		millimeters. In the application, a field with a typographic measurement may set itself to
		app units #2, and display in the real units that are currently assigned to app units #2.

		@param inAppUnits		Unit preference. One of 11 enumerated values of type ADMUnits
		@param inActualUnits	Units for the inAppUnits unit preference. Type: ADMUnits

		@return None.

		@see GetAppUnits()
	*/
	void ADMAPI (*SetAppUnits)(ADMUnits inAppUnits, ADMUnits inActualUnits);

	/**
		Returns the units currently being used by the host application.

		Unit examples include points, picas, inches, etc.) for inAppUnits.
		inAppUnits can be one of 11 enumerated values of type ADMUnits.

		ADM provides a system for storing 11 distinct unit preferences that may be used
		for various purposes within an application or plug-in. The first argument to
		sADMBasic->SetAppUnits(), inAppUnits, is used to specify which unit preference is
		being set (#1-11), while the second argument, inActualUnits, is used to set the
		units for that particular unit preference. The GetAppUnits() function takes only an
		inAppUnits argument.

		@param inAppUnits	Unit preference (#1-11) for which inActualUnits (see
							sADMBasic->SetAppUnits()) is being requested. One of 11
							enumerated values of type ADMUnits.

		@return The inActualUnits (see sADMBasic->SetAppUnits()) units currently being used
		        by the application for inAppUnits. Must be one of the enumerated values of
				type ADMUnits, as defined in ADMTypes.h.

  		@see SetAppUnits()
	*/
	ADMUnits ADMAPI (*GetAppUnits)(ADMUnits inAppUnits);
	
	/**
		Sets whether numbers entered without a units specifier are in points (72 pts./in.).
		
		Useful for applications that do not default to the use of points. For example,
		Illustrator (2D drawing oriented) does use point measurements, but Premiere
		(time-based oriented) does not.

		@param inPoints		If true, points will be the default unit of measurement in the
							application. If false, they will not be.

		@return None.

  		@see GetNumbersArePoints()
	*/
	void ADMAPI (*SetNumbersArePoints)(ADMBoolean inPoints);

	/**
		Determines whether numbers entered without a units specifier are in points
		(72 pts./in.).
		
		This function is useful for applications that do not default to the use of points.
		For example, Illustrator (2D drawing-oriented) does use point measurements, while
		Premiere (time-based oriented) does not.

		@param None.

		@return true if numbers entered without a units specifier are in points;
		        false otherwise.

  		@see SetNumbersArePoints()
	*/
	ADMBoolean ADMAPI (*GetNumbersArePoints)();

	/**
		Sets the small and large increments for spinner, slider, and scroll bar cursor
		movement.

		@param inUnits				Units for which the incremental values are being set
									(e.g., kADMPixelUnits). Type: ADMUnits
		@param inSmallIncrement		Small increment for inUnits.
		@param inLargeIncrement		Large increment for inUnits.

		@return None.

  		@see GetDefaultIncrements()
	*/
	void ADMAPI (*SetDefaultIncrements)(ADMUnits inUnits, float inSmallIncrement,
				float inLargeIncrement);

	/**
		Obtains the default cursor movement increments set by sADMBasic->SetDefaultIncrements().

		@param inUnits				Units for which the incremental values are being retrieved
									(e.g., kADMPixelUnits). Type: ADMUnits
		@param outSmallIncrement	Small increment for inUnits.
		@param outLargeIncrement	Large increment for inUnits.

		@return None.

  		@see SetDefaultIncrements()
	*/
	void ADMAPI (*GetDefaultIncrements)(ADMUnits inUnits, float* outSmallIncrement,
				float* outLargeIncrement);
	//@}

	/** @name User Interface Functions
	*/
	//@{
	/**
		For Adobe in-house use only
		
		Third-party plug-in developers should use the PluginAboutBox() function.
		
		This function is used to create a simple fixed-sized, three-line,
		title-less About box for a plug-in. The first two lines are user-defined; the
		third line contains appropriate copyright notice similar to:
		©1997-98, Adobe Systems, Inc.

		@param inPlugin Plug-in reference.
		@param inText1	First user-defined line of text.
		@param inText2	Second user-defined line of text.

		@return None.

		@see PluginAboutBox()
	*/
	void ADMAPI (*AboutBox)(SPPluginRef inPlugin, const char* inText1, const char* inText2);

	/**
		For Adobe in-house use only

		Third-party plug-in developers should use the PluginAboutBoxW() function.

		This is the same as the AboutBox() function, but the text lines are Unicode strings.

		@see AboutBox() PluginAboutBoxW()
	*/
	void ADMAPI (*AboutBoxW)(SPPluginRef inPlugin, const ADMUnicode* inText1, const ADMUnicode* inText2);

	/**
		Determine whether ADM tool tips are currently in a "sticky" state.
		
		A "sticky" state means that a tool tip is already visible, so no delay
		is needed before displaying the next tip (if the user moves the cursor,
		requiring display of another tip).

		@param inDialog		Reference to an instance of a dialog.

		@return true if tool tips are sticky; false otherwise.

		@see EnableToolTips() HideToolTip() ShowToolTip() AreToolTipsEnabled()
	*/
	ADMBoolean ADMAPI (*AreToolTipsSticky)(ADMDialogRef inDialog);

	/**
		Gets the tool tips delay time and pop-up duration parameters.
		
		The default popup delay setting is .5 seconds; the default popdown delay setting
		is 5 seconds.

		<b>Note:</b> Currently there is no function that can be used to set these parameters.

		@param outPopupDelay	Returns the amount of time before a tool tips is displayed.
		@param outPopdownDelay	Returns the amount of time a tool tip remains displayed.

		@return None.
	*/
	void ADMAPI (*GetToolTipDelays)(ADMInt32* outPopupDelay, ADMInt32* outPopdownDelay);
	//@}

	/** @name Utility Functions
	*/
	//@{
	/**
		Returns the dimensions of the primary screen minus the system menus, task bars, etc.

		@param outDimensions	Workspace dimensions. Type: ADMRect

		@return true if dimensions successfully returned; false otherwise.
	*/
	ADMBoolean ADMAPI (*GetWorkspaceBounds)(ADMRect* outDimensions);

	/**
		Returns the dimensions of the host application screen boundaries.
		
		The boundaries are the inset of a standard application window. This is the
		area is available for use in placing a plug-in dialog screen.

		@param outDimensions	Dimensions of the host application screen boundaries.
								Type: ADMRect
	
		@return true if the dimensions are successfully obtained; false otherwise.
	*/
	ADMBoolean ADMAPI (*GetPaletteLayoutBounds)(ADMRect* outDimensions);
	//@}

	/** @name Resource Functions
	*/
	//@{
	/**
		Sets the cursor to a given platform-specific cursor resource
		
		This is a cross-platform cursor setting mechanism, but the resource
		type is different for Macintosh (‘CURS’) and Windows (CURSOR).

		@param inPluginRef	Plug-in reference.
		@param inCursorID	Cursor resource ID.

		@return None.
	*/
	void ADMAPI (*SetPlatformCursor)(SPPluginRef inPluginRef, ADMInt32 inCursorID);
	//@}

	/** @name User Interface Functions
	*/
	//@{
	/**
		Displays an informational message to the user that describes the plug-in.
		
		The text inTitle is displayed in the title bar and the text inText is
		displayed in the dialog. The box grows vertically to hold the text.

		@param inTitle	Text displayed in the title bar of the dialog.
		@param inText	Text displayed in the dialog.

		@return None.

  		@see AboutBox()
	*/
	void ADMAPI (*PluginAboutBox)(const char* inTitle, const char* inText);

	/**
		Displays an informational message to the user that describes the plug-in.

		This is the same as PluginAboutBox(), but the strings are Unicode strings.

		@see PluginAboutBox()
	*/
	void ADMAPI (*PluginAboutBoxW)(const ADMUnicode* inTitle, const ADMUnicode* inText);

	/**
		Sets the text labels for the buttons of an QuestionAlert() or YesNoAlert() dialog.
		
		This should be called before sADMBasic->QuestionAlert() or sADMBasic->YesNoAlert()
		is called.

		<b>Note:</b> Default values are reset automatically after the alert is called.
		The sequence is: set alert, call the alert, automatic reset, set the alert,
		call the alert, automatic reset, and so on.

		@param inLeftChoice		Text for left button. Default: Yes.
		@param inMiddleChoice	Text for middle button. Default: No.
		@param inRightChoice	Text for right button. Default: Cancel.

		@return See sADMBasic->QuestionAlert() or sADMBasic->YesNoAlert().

		@see QuestionAlert() YesNoAlert()
*/
	void ADMAPI (*SetAlertButtonText)(const char* inLeftChoice, const char* inMiddleChoice,
				const char* inRightChoice);

	/**
		Sets the text labels for the buttons of an QuestionAlert() or YesNoAlert() dialog.

		This is the same as SetAlertButtonText(), but the strings are Unicode strings.

		@see SetAlertButtonText()
	*/
	void ADMAPI (*SetAlertButtonTextW)(const ADMUnicode* inLeftChoice, const ADMUnicode* inMiddleChoice,
				const ADMUnicode* inRightChoice);

	/**
		Shows an ADM tool tip at the position inWhere using the text value inTip.
		
		The tip disappears after 5 seconds unless sADMBasic->HideToolTip() is called.

		@param inWhere	Position where the tool tip is to be displayed.
						Type: ADMPoint
		@param inTip	Tool tip text.

		@see EnableToolTips() HideToolTip() AreToolTipsEnabled() AreToolTipsSticky()
	*/
	void ADMAPI (*ShowToolTip)(const ADMPoint* inWhere, const char* inTip);

	/**
		Shows an ADM tool tip at the position inWhere using the text value inTip.

		This is the same as ShowToolTip(), but the strings are Unicode strings.

		@see ShowToolTip()
	*/
	void ADMAPI (*ShowToolTipW)(const ADMPoint* inWhere, const ADMUnicode* inTip);

	/**
		Hides a tool tip displayed by the ShowToolTip() function.
		
		This function does not affect the standard tool tip behavior.

		@param None.

		@return None.

		@see EnableToolTips() ShowToolTip() AreToolTipsEnabled() AreToolTipsSticky()
	*/
	void ADMAPI (*HideToolTip)();
	//@}

	/** @name Contextual Menu Functions

		These functions are used to create pop-up contextual menus. Contextual menus can
		be used to display a menu when the cursor is over a particular location and a
		combination of mouse states or modifier keys can be used to select an option. For
		example, pressing and holding the mouse down in an Internet browser window opens
		a pop-up menu with Back and Forward options. Most likely, these functions will be
		used by the host application rather than a plug-in. Contextual menus must be
		destroyed when done.
	*/
	//@{
	/**
		Creates a contextual menu.
		
		This function allows the creation of a list without an associated item. The list
		reference returned in outMenu can be initialized with the standard functions
		in the ADM List and ADM Entry suites.

		@param outMenu	The new contextual menu.

		@return 0 if operation was successful; otherwise, the error code indicates the
		        error that occurred.

		@see DestroyMenu() DisplayMenu()
	*/
	ADMErr ADMAPI (*CreateMenu)(ADMListRef* outMenu);

	/**
		Displays inMenu over inDialog at inDialogPoint.

		@param inMenu			Contextual menu to display.
		@param inDialog			Dialog over which to display inMenu.
		@param inDialogPoint	Point within inDialog at which to display inMenu.
								Type: ADMPoint

		@return 0 if operation was successful; otherwise, the error code indicates
		        the error that occurred.

		@see CreateMenu() DestroyMenu()
	*/
	ADMErr ADMAPI (*DisplayMenu)(ADMListRef inMenu, ADMDialogRef inDialog, ADMPoint inDialogPoint);

	/**
		Destroys the referenced contextual menu.

		@param inMenu	The contextual menu to destroy.

		@return 0 if operation was successful; otherwise, the error code indicates
		        the error that occurred.

		@see CreateMenu() DisplayMenu()
	*/
	ADMErr ADMAPI (*DestroyMenu)(ADMListRef inMenu);
	//@}

	/** @name Utility Functions
	*/
	//@{
	/**
		Retrieves relavant information about why a dialog failed to load.
		
		A dialog can be loaded using sADMDialog->Create(), sADMDialog->Modal(),
		or sADMDialog->CreateGroupInDialog().

		@param outError Type of error.
		@param outErrorData Data associated with outError (e.g., dialog reference).

		@return true if valid error was returned; false otherwise.

		@see ADMDialog->Create() ADMDialog->Modal() ADMDialog->CreateGroupInDialog()
	*/
	ADMBoolean ADMAPI (*GetLastADMError)(ADMInt32* outError, ADMInt32* outErrorData);

	/**
		Converts an ADM standard color to an RGB value.

		@param inADMColor	ADM color for conversion. Type: ADMColor
		@param outRGBColor	ADM color converted to RGB value.
							Type: ADMRGBColor

		@return true if the conversion was successful; false otherwise.

		@see ChooseColor()
	*/
	ADMBoolean ADMAPI (*ADMColorToRGBColor)(ADMColor inADMColor, ADMRGBColor* outRGBColor);

	/**
		Sets the application’s frames-per-second (FPS).

		@param inFPS	FPS value.

		@return None.

		@see GetAppFPS()
	*/
	void ADMAPI (*SetAppFPS)(float inFPS);

	/**
		Returns the application’s frames-per-second (FPS) value.

		param None.

		@return FPS value.

		@see SetAppFPS()
	*/
	float ADMAPI (*GetAppFPS)();
	//@}

	/** @name User Interface Functions
	*/
	//@{
	/**
		A lightweight version of ErrorAlert().
		
		This function indicates an error with a text message and a beep.

		@param inErrorString	Error string text.

		@return None.

		@see ErrorAlert() MessageAlert() QuestionAlert()
		     SetAlertButtonText() YesNoAlert()
	*/
	void ADMAPI (*LightweightErrorAlert)(const char* inErrorString);

	/**
		A lightweight version of ErrorAlert().

		This is the same as LightweightErrorAlert(), but inErrorString is a Unicode string.

		@see LightweightErrorAlert()
	*/
	void ADMAPI (*LightweightErrorAlertW)(const ADMUnicode* inErrorString);
	//@}

	/** @name Utility Functions
	*/
	//@{
	/**
		No documentation available yet.
	*/
	ADMBoolean ADMAPI (*LookUpZString)(SPPluginRef inPluginRef,
				const char* inString, char* outString, ADMUInt32* ioBufferSize);
	//@}
}
ADMBasicSuite8;

// -----------------------------------------------------------------------------
//	Old versions of suites

#ifndef __ADMBasicOld__
#ifdef MAC_ENV
#include "ADMBasicOld.h"
#else
#include ".\Legacy\ADMBasicOld.h"
#endif
#endif

// -----------------------------------------------------------------------------

#pragma ADM_PRAGMA_IMPORT_END
#pragma ADM_PRAGMA_ALIGN_END

#ifdef __cplusplus
}
#endif

// -----------------------------------------------------------------------------

#endif	// __ADMBasic__
