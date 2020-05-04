#include"BinApp.h"

//Create Window Method
void BinApp::onCreate() {
	try {
		this->CreateNativeControls();
	}
	catch (const std::exception& ex) {
		std::string ErrInfo = ex.what();

		MessageBox(nullptr, std::wstring(begin(ErrInfo), end(ErrInfo)).c_str(), L"Îøèáêà", MB_ICONERROR | MB_OK);
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
	this->pRT->BeginDraw();
	this->DrawBackGround();
	this->DrawTitle();
	this->pRT->EndDraw();
	EndPaint(hwnd, &pt);
}