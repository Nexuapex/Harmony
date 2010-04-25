//
// WHGameWindow.h
// Harmony
//

#pragma once

#include "game_interface.h"

// The main game window.
class WHGameWindow : public CDialog {
public:
	WHGameWindow();

protected:
	void SetMousePosition(CPoint point);
	void SetInputState(CPoint point, hgame_input_t state, BOOL new_value);

protected:
	virtual BOOL OnInitDialog();
	virtual void OnOK();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT details);
	afx_msg LRESULT OnKickIdle(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnXButtonDown(UINT nFlags, UINT nButton, CPoint point);
	afx_msg void OnXButtonUp(UINT nFlags, UINT nButton, CPoint point);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO * info);
	afx_msg void OnSize(UINT action, int width, int height);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()

protected:
	hgame_ref game_;
	DWORD lastUpdateTime_;
	CClientDC * deviceContext_;
	HGLRC graphicsContext_;
	HICON icon_;
};
