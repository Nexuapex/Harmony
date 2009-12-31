//
// WHApplication.cpp
// Harmony
//

#include "WHGlue.h"
#include "WHApplication.h"
#include "WHGameWindow.h"

// Mapping from Windows messages to message handlers.
BEGIN_MESSAGE_MAP(WHApplication, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

// The singleton instance of WHApplication.
WHApplication WHApp;

// General constructor. Important initialization happens in InitInstance.
WHApplication::WHApplication() {}

// Allows the program to use standard window visual styles.
bool WHApplication::PrepareCommonControls() {
	INITCOMMONCONTROLSEX controls;

	controls.dwSize = sizeof(controls);
	controls.dwICC = ICC_WIN95_CLASSES;

	return InitCommonControlsEx(&controls) ? true : false;
}

bool WHApplication::PrepareGdiplus() {
	Gdiplus::GdiplusStartupInput options;
	return Gdiplus::GdiplusStartup(&gdiplusToken_, &options, NULL) == Gdiplus::Ok;
}

// Allows the program to use Windows sockets.
bool WHApplication::PrepareSockets() {
	bool success = AfxSocketInit() ? true : false;

	if (!success)
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);

	return success;
}

// All the important initialization happens here.
BOOL WHApplication::InitInstance() {
	// Initialize various subsections of the application.
	PrepareCommonControls();
	PrepareGdiplus();
	CWinApp::InitInstance();
	// PrepareSockets();
	
	// In case we ever need to use the registry.
	SetRegistryKey(_T("Harmony"));

	// The main game window is created here.
	WHGameWindow gameWindow;
	m_pMainWnd = &gameWindow;

	// Show the window.
	gameWindow.DoModal();

	// Shut down GDI+.
	Gdiplus::GdiplusShutdown(gdiplusToken_);

	// Since the dialog has been closed, return FALSE so that we exit the
	// application, rather than start the application's message pump.
	return FALSE;
}
