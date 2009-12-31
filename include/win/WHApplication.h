//
// WHApplication.h
// Harmony
//

#pragma once

//
// Primary header for the Windows platform layer of Harmony.
//

#ifndef __AFXWIN_H__
#error "Include 'WHGlue.h' before including this file"
#endif

#include "WHResources.h"

// The main application class of the game.
class WHApplication : public CWinApp {
public:
	WHApplication();
	virtual BOOL InitInstance();

private:
	bool PrepareCommonControls();
	bool PrepareGdiplus();
	bool PrepareSockets();

private:
	ULONG_PTR gdiplusToken_;

protected:
	DECLARE_MESSAGE_MAP()
};

// The singleton instance of WHApplication.
extern WHApplication WHApp;
