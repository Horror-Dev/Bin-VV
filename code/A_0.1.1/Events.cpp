#include"BinApp.h"

//Create Window Method
void BinApp::onCreate() {
	GetClientRect(this->MainHwnd, &this->m_rWindowRect);

	try {
		this->CreateNativeControls();
	}
	catch (const std::exception& ex) {
		std::string ErrInfo = ex.what();

		MessageBox(nullptr, std::wstring(begin(ErrInfo), end(ErrInfo)).c_str(), L"Error", MB_ICONERROR | MB_OK);
		ExitProcess(EXIT_FAILURE);
	}
}

// Close Window Method
void BinApp::onClose() {
	this->FreeResources();
}

void BinApp::Command(const int& nId) {
	switch (nId){
		case  static_cast<int>(BinApp::CTL_ID::ID_BUTTON_TRANSF) :
			this->onTransfButton();
		break;
		case static_cast<int>(BinApp::CTL_ID::ID_BUTTON_CLOSE) :
			this->onCloseButton();
		break;
		case static_cast<int>(BinApp::CTL_ID::ID_BUTTON_MINIMIZE) :
			this->onMinimizeButton();
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

void BinApp::onMove() {

}