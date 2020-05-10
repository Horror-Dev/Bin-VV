#include"BinApp.h"

//Create Window Method
void BinApp::onCreate() {
	GetClientRect(this->MainHwnd, &this->m_rWindowRect);
	try {
		this->CreateNativeControls();
	}
	catch (const std::exception& ex) {
		std::string ErrInfo = ex.what();

		MessageBox(nullptr, std::wstring(begin(ErrInfo), end(ErrInfo)).c_str(), L"Îøèáêà", MB_ICONERROR | MB_OK);
		ExitProcess(EXIT_FAILURE);
	}

	HICON hIcon1 = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
	SendMessage(this->MainHwnd, WM_SETICON, 1, (LPARAM)hIcon1);

}

// Close Window Method
void BinApp::onClose() {
	this->FreeResources();
}

void BinApp::Command(const int& nId, WPARAM wParam, LPARAM lParam) {
	if (HIWORD(wParam) == CBN_SELCHANGE){
		int ItemIndex = SendMessage(this->hWndComboBox, (UINT)CB_GETCURSEL,
			(WPARAM)0, (LPARAM)0);
	}
	switch (nId){
		case  static_cast<int>(BinApp::CTL_ID::ID_BUTTON_TRANSF) :
			this->onTransfButton(lParam);
		break;
		case static_cast<int>(BinApp::CTL_ID::ID_BUTTON_CLOSE) :
			this->onCloseButton();
		break;
		case static_cast<int>(BinApp::CTL_ID::ID_BUTTON_MINIMIZE) :
			this->onMinimizeButton();
		break;
		case static_cast<int>(BinApp::CTL_ID::ID_COMBOBOX) :
			
			break;
	}
}


void BinApp::Paint(HWND hwnd) {
	PAINTSTRUCT pt;
	BeginPaint(hwnd, &pt);
	 this->m_pDCRT->BindDC(pt.hdc, &this->m_rWindowRect);
	this->m_pDCRT->BeginDraw();
	this->DrawBackGround();
	this->DrawTitle();
	this->m_pDCRT->EndDraw();
	EndPaint(hwnd, &pt);
}

LRESULT CALLBACK BinApp::StaticProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam) {
	if (Message == WM_PAINT){
		RECT rc;
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);
		SetBkMode(hdc, TRANSPARENT);
		wchar_t text[5]{L"===>"};
		DrawText(hdc, text, 5, &rc, DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);
		return 0;
	}
}

void BinApp::onMove() {

}