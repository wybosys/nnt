
# include "Core.h"
# include "UcKernel.h"

extern int NNT_MAIN(int, char**);

UC_BEGIN

# ifdef NNT_MSVC

NNT_BEGIN_NS(msvc)

BackgroundWindow::BackgroundWindow()
: cmd(NULL)
{

}

BackgroundWindow::~BackgroundWindow()
{
    if (cmd)
        UNREFERENCED_PARAMETER(cmd);
}

LRESULT CALLBACK UcWindowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
HWND __gs_handle_backgroundwindow = NULL;

int BackgroundWindow::main()
{
    // register bw class.
    HINSTANCE chd = GetModuleHandle(NULL);
    WNDCLASSEX wcx;    
    ZeroMemory(&wcx, sizeof(wcx));
    wcx.cbSize = sizeof(wcx);
    wcx.style = NULL;
    wcx.lpfnWndProc = UcWindowProc;
    wcx.hInstance = chd;
    wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wcx.lpszClassName = _T("NNTBackgroundWindow");
    wcx.hIconSm = (HICON)LoadImage(chd,
        MAKEINTRESOURCE(5),
        IMAGE_ICON, 
        GetSystemMetrics(SM_CXSMICON), 
        GetSystemMetrics(SM_CYSMICON), 
        LR_DEFAULTCOLOR);
    if (RegisterClassEx(&wcx) == FALSE)
    {
# ifdef NNT_DEBUG
        MessageBox(NULL, _T("Failed to register class."), _T("FATAL"), MB_OK);
# endif
        return GetLastError();
    }

    // create the window.
    HWND hwnd = CreateWindowEx(WS_EX_STATICEDGE, wcx.lpszClassName, wcx.lpszClassName, WS_OVERLAPPEDWINDOW, 0, 0, 0, 0, NULL, NULL, chd, NULL);
    if (hwnd == NULL)
    {
# ifdef NNT_DEBUG
        MessageBox(NULL, _T("Failed to create BackgroundWindow."), _T("FATAL"), MB_OK);
# endif
        return GetLastError();
    }

    // pack
    ShowWindow(hwnd, SW_HIDE);
    UpdateWindow(hwnd);
    __gs_handle_backgroundwindow = hwnd;

    // call app.
    if (entry(0, 0) != 0)
    {
        DestroyWindow(hwnd);
        return 0;
    }

    // peek message.
    MSG msg;
    int sta;
    while ((sta = GetMessage(&msg, hwnd, 0, 0)) != 0 &&
        sta != -1)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK UcWindowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

NNT_END_NS

# endif

UC_END
