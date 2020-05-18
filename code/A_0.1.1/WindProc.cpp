#include"BinApp.h"

// Window Processes 
LRESULT CALLBACK BinApp::WindProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CREATE:
		this->onCreate();
		break;
	case WM_DESTROY:
		this->onClose();
		PostQuitMessage(0);
		return 0;
	case WM_COMMAND:
		this->Command(LOWORD(wParam));
		return 0;
	case WM_MOVE:
		this->onMove();
		break;
	case WM_NCHITTEST:
		SetWindowLong(hwnd, DWL_MSGRESULT, HTCAPTION);
		return HTCAPTION;
	case WM_NCCALCSIZE:
		if (wParam == TRUE)
			SetWindowLong(hwnd, DWL_MSGRESULT, 0);
		return TRUE;
		return FALSE;
	break;
	case WM_PAINT:
	case WM_DISPLAYCHANGE:
		this->Paint(hwnd);
		break;
	case WM_DRAWITEM:
		this->ButtonDrawing(wParam,reinterpret_cast<PDRAWITEMSTRUCT>(lParam));
		return 0;
	case WM_SETCURSOR:
	{
		HWND wind = reinterpret_cast<HWND>(wParam);
		if (wind == this->CloseButtonHwnd || wind == this->MiniMizeButtonHwnd || wind == this->TranslateButtonHwnd)
		{
			SetCursor(LoadCursor(NULL, IDC_HAND));
			return(TRUE);
		}
	}
	break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}