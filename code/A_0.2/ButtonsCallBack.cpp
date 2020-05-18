#include"BinApp.h"

void BinApp::onCloseButton() {
	SendMessage(this->MainHwnd, WM_DESTROY, 0, 0);
}

void BinApp::onMinimizeButton() {
	SendMessage(this->MainHwnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
}

void BinApp::onTransfButton(LPARAM lParam) {
	try {

		int ItemIndex = SendMessage(this->hWndComboBox, (UINT)CB_GETCURSEL,
			(WPARAM)0, (LPARAM)0);
		TCHAR  ListItem[256];
		(TCHAR)SendMessage(this->hWndComboBox, (UINT)CB_GETLBTEXT,
			(WPARAM)ItemIndex, (LPARAM)ListItem);

		std::wstring test = ListItem;
		std::string tmp2(test.begin(), test.end());

		int NumSystem = atoi(tmp2.c_str());

		int ItemIndex2 = SendMessage(this->hWndComboBox2, (UINT)CB_GETCURSEL,
			(WPARAM)0, (LPARAM)0);
		TCHAR  ListItem2[256];
		(TCHAR)SendMessage(this->hWndComboBox2, (UINT)CB_GETLBTEXT,
			(WPARAM)ItemIndex2, (LPARAM)ListItem2);

		std::wstring test2 = ListItem2;
		std::string tmp3(test2.begin(), test2.end());

		int Num2System = atoi(tmp3.c_str());

		std::wstring text{};
		text.resize(MAX_PATH);
		GetWindowText(this->EditHWND, &text[0], MAX_PATH);
		text.erase(remove(begin(text), end(text), 0), end(text));
		if (text.empty()) {
			MessageBox(this->MainHwnd, L"Please enter number!", L"information", MB_ICONINFORMATION | MB_OK);
			return;
		}
		text = Convert(text, NumSystem, Num2System);
		SetWindowText(this->EditHWND, text.c_str());
	}
	catch (...) {
		MessageBox(this->MainHwnd, L"the number exceeds 2 bytes", L"warning", MB_ICONINFORMATION | MB_OK);
	}
}

std::wstring BinApp::Convert(std::wstring Number, int NumberSystem, int Number2System) {
	std::string tmpNumber(Number.begin(), Number.end());
	Converter tmpConverter(tmpNumber, NumberSystem);
	tmpNumber = tmpConverter.convertTo(Number2System);
	return  std::wstring(begin(tmpNumber), end(tmpNumber));
}