
# include "nnt/Foundation+NNT.h"
# include "qtapp.h"
# include "Classes/AppDelegate.h"

int APIENTRY WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd )
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	::nntapp::App app;
	return app.execute(0, 0);
}
