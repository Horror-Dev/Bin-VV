#include"BinApp.h"

void BinApp::onCloseButton() {
	SendMessage(this->MainHwnd, WM_DESTROY, 0, 0);
}

void BinApp::onMinimizeButton() {
	SendMessage(this->MainHwnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
}

void BinApp::onTransfButton() {
	try {
		std::wstring text{};
		text.resize(MAX_PATH);
		GetWindowText(this->EditHWND, &text[0], MAX_PATH);
		text.erase(remove(begin(text), end(text), 0), end(text));
		if (text.empty()) {
			MessageBox(this->MainHwnd, L"Ведите число", L"Информация", MB_ICONINFORMATION | MB_OK);
			return;
		}

		std::string binVal = std::bitset<16>(std::stoi(text)).to_string();
		text = std::wstring(begin(binVal), end(binVal));

		SetWindowText(this->EditHWND, text.c_str());
	}
	catch (...) {
		MessageBox(this->MainHwnd, L"число превышает 2 байта", L"Внимание", MB_ICONINFORMATION | MB_OK);
	}
}