
# include "wsi/WSIFoundation.h"
# include "qtapp.h"
# include "Classes/AppDelegate.h"

int APIENTRY WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd )
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	::wsiapp::App app;
	return app.execute(0, 0);
}
