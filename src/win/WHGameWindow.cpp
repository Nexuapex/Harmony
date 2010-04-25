//
// WHGameWindow.cpp
// Harmony
//

#include "WHGlue.h"
#include "WHApplication.h"
#include "WHGameWindow.h"

#include "gx_interface.h"

// Mapping from Windows messages to message handlers.
BEGIN_MESSAGE_MAP(WHGameWindow, CDialog)
	ON_WM_CREATE()
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_XBUTTONDOWN()
	ON_WM_XBUTTONUP()
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// General constructor. Important initialization happens in OnInitDialog.
WHGameWindow::WHGameWindow()
	: CDialog(IDD_GAME_WINDOW, NULL)
	, game_(NULL)
	, graphicsContext_(NULL)
{
	icon_ = WHApp.LoadIcon(IDR_HARMONY);
}

// All the important initialization happens here.
BOOL WHGameWindow::OnInitDialog() {
	CDialog::OnInitDialog();

	// Set the window's size.
	int width = 1152, height = 768;
	SetWindowPos(NULL, 0, 0, width, height, SWP_NOMOVE);

	// Resize to account for the client area.
	RECT clientRect;
	GetClientRect(&clientRect);
	width += width - clientRect.right;
	height += height - clientRect.bottom;
	SetWindowPos(NULL, 0, 0, width, height, SWP_NOMOVE);

	// Center the window.
	CenterWindow();

	// Set the big and small icons for the window.
	SetIcon(icon_, TRUE);
	SetIcon(icon_, FALSE);

	// Unless a control gets focus, TRUE must be returned.
	return TRUE;
}

// Called when the user hits return in the window.
void WHGameWindow::OnOK() {}

// Create the window and set up OpenGL.
int WHGameWindow::OnCreate(LPCREATESTRUCT details) {
	// A -1 returns means the window should be destroyed.
	if (CDialog::OnCreate(details) == -1)
		return -1;

	// Get the device context.
	deviceContext_ = new CClientDC(this);

	// Create the pixel format.
	PIXELFORMATDESCRIPTOR pixelFormat;
	memset(&pixelFormat, 0, sizeof(pixelFormat));
	pixelFormat.nSize = sizeof(pixelFormat);
	pixelFormat.nVersion = 1;
	pixelFormat.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pixelFormat.iPixelType = PFD_TYPE_RGBA;
	pixelFormat.cColorBits = 32;
	pixelFormat.cDepthBits = 32;

	// Activate that pixel format.
	int chosenFormat = ChoosePixelFormat(deviceContext_->m_hDC, &pixelFormat);
	if (chosenFormat == 0)
		return -1;
	if (!SetPixelFormat(deviceContext_->m_hDC, chosenFormat, &pixelFormat))
		return -1;

	// Create and activate the OpenGL context.
	graphicsContext_ = wglCreateContext(deviceContext_->m_hDC);
	if (!graphicsContext_)
		return -1;
	if (!wglMakeCurrent(deviceContext_->m_hDC, graphicsContext_))
		return -1;

	// Get the initial time.
	lastUpdateTime_ = timeGetTime();

	// Create the game object.
	game_ = hgame_create();

	return 0;
}

// Called whenever the application isn't doing anything.
LRESULT WHGameWindow::OnKickIdle(WPARAM wParam, LPARAM lParam) {
	(void)wParam;
	(void)lParam;

	if (game_) {
		// For now, the game engine will be updated by the graphics callback.
		DWORD current = timeGetTime();
		float elapsed = (float)(current - lastUpdateTime_);
		hgame_step(game_, elapsed);
		lastUpdateTime_ = current;
		
		// Tell the engine to render the game world.
		if (wglMakeCurrent(deviceContext_->m_hDC, graphicsContext_)) {
			hgx_render(game_, elapsed);
			SwapBuffers(deviceContext_->m_hDC);
		}
		wglMakeCurrent(NULL, NULL);
	}

	return TRUE;
}

// Called to tell the engine about the mouse's location.
void WHGameWindow::SetMousePosition(CPoint point) {
	// Get the current size of the client region.
	RECT bounds;
	GetClientRect(&bounds);

	// Clamp the point to the desired range.
	if (point.x < 0) point.x = 0;
	if (point.y < 0) point.y = 0;
	if (point.x > bounds.right) point.x = bounds.right;
	if (point.y > bounds.bottom) point.y = bounds.bottom;

	// Tell the engine about the new mouse position.
	hgame_mouse_moved(game_, static_cast<unsigned>(point.x), static_cast<unsigned>(point.y));
}

// Called to tell the engine about a boolean input state changing.
void WHGameWindow::SetInputState(CPoint point, hgame_input_t state, BOOL new_value) {
	SetMousePosition(point);
	hgame_input_state_changed(game_, state, new_value);
}

// Handle specific mouse messages.
#pragma region Mouse Message Handlers

void WHGameWindow::OnMouseMove(UINT nFlags, CPoint point) {
	(void)nFlags;
	SetMousePosition(point);
}

void WHGameWindow::OnLButtonDown(UINT nFlags, CPoint point) {
	(void)nFlags;
	SetInputState(point, hgame_input_mouse1, true);
}

void WHGameWindow::OnLButtonUp(UINT nFlags, CPoint point) {
	(void)nFlags;
	SetInputState(point, hgame_input_mouse1, false);
}

void WHGameWindow::OnRButtonDown(UINT nFlags, CPoint point) {
	(void)nFlags;
	SetInputState(point, hgame_input_mouse2, true);
}

void WHGameWindow::OnRButtonUp(UINT nFlags, CPoint point) {
	(void)nFlags;
	SetInputState(point, hgame_input_mouse2, false);
}

void WHGameWindow::OnMButtonDown(UINT nFlags, CPoint point) {
	(void)nFlags;
	SetInputState(point, hgame_input_mouse3, true);
}

void WHGameWindow::OnMButtonUp(UINT nFlags, CPoint point) {
	(void)nFlags;
	SetInputState(point, hgame_input_mouse3, false);
}

void WHGameWindow::OnXButtonDown(UINT nFlags, UINT nButton, CPoint point) {
	(void)nFlags;
	switch (nButton) {
		case XBUTTON1:
			SetInputState(point, hgame_input_mouse4, true);
			break;
		case XBUTTON2:
			SetInputState(point, hgame_input_mouse5, true);
			break;
	}
}

void WHGameWindow::OnXButtonUp(UINT nFlags, UINT nButton, CPoint point) {
	(void)nFlags;
	switch (nButton) {
		case XBUTTON1:
			SetInputState(point, hgame_input_mouse4, false);
			break;
		case XBUTTON2:
			SetInputState(point, hgame_input_mouse5, false);
			break;
	}
}

#pragma endregion

// Provide information about the maximized size of the window.
void WHGameWindow::OnGetMinMaxInfo(MINMAXINFO * info) {
	info->ptMaxPosition.x = 0;
	info->ptMaxPosition.y = 0;
	info->ptMaxSize.x = GetSystemMetrics(SM_CXSCREEN);
	info->ptMaxSize.y = GetSystemMetrics(SM_CYSCREEN);
	info->ptMaxTrackSize.x = info->ptMaxSize.x;
	info->ptMaxTrackSize.y = info->ptMaxSize.y;
}

// The window was resized, maximized, or minimized.
void WHGameWindow::OnSize(UINT action, int width, int height) {
	// Pass on the message.
	CDialog::OnSize(action, width, height);

	// Change the window style depending on if the window is maximized.
	switch (action) {
		case SIZE_MAXIMIZED:
			if (GetStyle() & WS_OVERLAPPEDWINDOW) {
				MONITORINFO screen;
				screen.cbSize = sizeof(screen);
				if (GetMonitorInfo(MonitorFromWindow(GetSafeHwnd(), MONITOR_DEFAULTTOPRIMARY), &screen)) {
					// ModifyStyle(WS_OVERLAPPEDWINDOW, 0, 0);
					width = screen.rcMonitor.right - screen.rcMonitor.left;
					height = screen.rcMonitor.bottom - screen.rcMonitor.top;
					SetWindowPos(&wndTop, screen.rcMonitor.left, screen.rcMonitor.top,
						width, height, SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
				}
			}
			break;
		case SIZE_MINIMIZED:
		case SIZE_RESTORED:
			if (!(GetStyle() & WS_OVERLAPPEDWINDOW)) {
				// ModifyStyle(0, WS_OVERLAPPEDWINDOW, 0);
				SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE
					| SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
			}
			break;
	}

	// Tell the engine that our view bounds changed.
	if (wglMakeCurrent(deviceContext_->m_hDC, graphicsContext_))
		hgx_reshape(game_, width, height);
	wglMakeCurrent(NULL, NULL);
}

// Draw the minimized icon if the window is minimized.
void WHGameWindow::OnPaint() {
	if (IsIconic()) {
		CPaintDC context(this);

		// Erase the background.
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(context.GetSafeHdc()), 0);

		// Calculate the centered position.
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - GetSystemMetrics(SM_CXICON) + 1) / 2;
		int y = (rect.Height() - GetSystemMetrics(SM_CYICON) + 1) / 2;

		// Draw the icon.
		context.DrawIcon(x, y, icon_);
	} else {
		CDialog::OnPaint();
	}
}

// Returns the cursor to display while the user drags the minimized window.
HCURSOR WHGameWindow::OnQueryDragIcon() {
	return static_cast<HCURSOR>(icon_);
}

// Time to destroy stuff.
void WHGameWindow::OnDestroy() {
	wglDeleteContext(graphicsContext_);
	graphicsContext_ = NULL;
	delete deviceContext_;
	deviceContext_ = NULL;
}
