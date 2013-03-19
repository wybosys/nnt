
#ifndef _VTABLESUPPORT_HPP_
#define _VTABLESUPPORT_HPP_

#ifdef __MWERKS__
#warning *** THIS FILE IS OBSOLETE now that 68K code is no longer supported. ***
#else
#pragma warning // *** THIS FILE IS OBSOLETE now that 68K code is no longer supported. ***
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#pragma PRAGMA_ALIGN_BEGIN
#pragma PRAGMA_IMPORT_BEGIN

///////////////////////////////////////////////////////////////////////
//
// If your plugin has a C++ object attached to it's globals, and if
// the class of that object has virtual functions, those functions
// will not work after the plugin is unloaded and then reloaded.
//
// The following macro (FIXUP_VTABLE) can be used to provide a means
// of restoring the virtual function table of a globally-persistent
// C++ object by calling FixupVTable() prior to the use of any of
// the object's virtual functions after a reload.
//
// Here is how you might use the macro:
//
// class MyGlobals
// {
// public:
//     //
//     [some class definition code skipped];
//     //
//     // pass class name to macro
//     FIXUP_VTABLE(MyGlobals);
//     //
//     // Note: private access at this point
//     //
// protected:
//     //
//     [more class definition code skipped];
// };
//
// //
// // Then, later in the translation:
// //
//
// ASErr
// OnReloadPlugin(SPInterfaceMessage *pMsg)
// {
//     MyGlobals *pGlobals = (MyGlobals *) pMsg->d.globals;
//
//     // don't use any of MyGlobals' virtual functions here
//     [some code skipped];
//
//     // should probably do this early on.
//     MyGlobals::FixupVTable(pGlobals);
//
//     // o.k. to use virtual functions now
//     [more code skipped];
// }
//
///////////////////////////////////////////////////////////////////////

#define FIXUP_VTABLE(CLASSNAME) \
public: \
	static void FixupVTable(CLASSNAME *pThis) {pThis = new(pThis) CLASSNAME((FixupVTableSignature) 0);} \
private: \
	typedef long FixupVTableSignature; \
	CLASSNAME(FixupVTableSignature) {} \
	static void *operator new(size_t uiSize, CLASSNAME *pThis) {return pThis;} \
	//

///////////////////////////////////////////////////////////////////////
//
// If you are using operator new from a base class, you can use the
// following macro so that the compiler can resolve the overloading
// in the scope of your derived class.
//
///////////////////////////////////////////////////////////////////////

#define FIXUP_VTABLE_EX(CLASSNAME, BASECLASS) \
public: \
	void *operator new(size_t uiSize) {return BASECLASS::operator new(uiSize);} \
	FIXUP_VTABLE(CLASSNAME)
	
///////////////////////////////////////////////////////////////////////
//
// If you are using a global operator new, you can use the
// following macro so that the compiler can resolve the overloading
// in the scope of your derived class.
//
///////////////////////////////////////////////////////////////////////

#define FIXUP_VTABLE_EX1(CLASSNAME) \
public: \
	void *operator new(size_t uiSize) {return ::operator new(uiSize);} \
	FIXUP_VTABLE(CLASSNAME)
	
#pragma PRAGMA_IMPORT_END
#pragma PRAGMA_ALIGN_END

#ifdef __cplusplus
}
#endif

#endif // _VTABLESUPPORT_HPP_

