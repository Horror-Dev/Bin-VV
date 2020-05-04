#include "BinApp.h"

BinApp::BinApp(){

	using std::string;
	using std::wstring;

	this->LoadSettingFromFile();

	try{
		this->initObjMainWindow();
		this->initFactory();
		this->CreateResources();
	}
	catch (const std::exception& ex){
		string ErrInfo = ex.what();

		MessageBox(nullptr,wstring(begin(ErrInfo), end(ErrInfo)).c_str(),L"Îøèáêà", MB_ICONERROR | MB_OK);
		ExitProcess(EXIT_FAILURE);
	}
}

int BinApp::run() {
	ShowWindow(this->MainHwnd, SW_SHOW);
	UpdateWindow(this->MainHwnd);
	MSG _msg{};
	while (GetMessage(&_msg, nullptr, 0, 0)) {
		TranslateMessage(&_msg);
		DispatchMessage(&_msg);
	}
	return _msg.wParam;
}

BinApp::~BinApp(){
	this->FreeResources();
}

void BinApp::initObjMainWindow() {
	using std::runtime_error;

	WNDCLASSEX _wc{ sizeof(WNDCLASSEX) };

	_wc.hInstance = nullptr;
	_wc.lpszClassName = this->AppName.c_str();
	_wc.lpfnWndProc = BinApp::ApplicationProc;
	_wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	_wc.hIcon = LoadIcon(nullptr, IDI_ERROR);
	_wc.hIconSm = LoadIcon(nullptr, IDI_ERROR);
	_wc.hbrBackground = /*reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH))*/nullptr;
	_wc.cbClsExtra = 0;
	_wc.cbWndExtra = 0;
	_wc.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&_wc))
		throw runtime_error("Error, can't register main Class");

	RECT windRect{ 0,0,this->Width,this->Hieght };
	AdjustWindowRect(&windRect, WS_CAPTION | WS_POPUP, false);

	if (this->MainHwnd = CreateWindowEx(0, this->AppName.c_str(), this->AppName.c_str(), WS_CAPTION | WS_POPUP, (GetSystemMetrics(SM_CXSCREEN) - windRect.right) / 2, (GetSystemMetrics(SM_CYSCREEN) - windRect.bottom) / 2, windRect.right, windRect.bottom, nullptr, nullptr, nullptr, this); !this->MainHwnd)
		throw runtime_error("Error can't Create main window");
}

void BinApp::CreateNativeControls() {
	if (this->CloseButtonHwnd = CreateWindowEx(0, L"BUTTON", L"X", BS_PUSHBUTTON | BS_OWNERDRAW | WS_VISIBLE | WS_CHILD , 340, 10, 10, 10, this->MainHwnd, reinterpret_cast<HMENU>(BinApp::CTL_ID::ID_BUTTON_CLOSE), nullptr, nullptr); !this->CloseButtonHwnd)
		throw std::runtime_error("Error, Can't Create button");

	if (this->TranslateButtonHwnd = CreateWindowEx(0, L"BUTTON", L"Convert", BS_PUSHBUTTON | BS_OWNERDRAW | WS_VISIBLE | WS_CHILD, 100, 140, 150, 40, this->MainHwnd, reinterpret_cast<HMENU>(BinApp::CTL_ID::ID_BUTTON_TRANSF), nullptr, nullptr); !this->TranslateButtonHwnd)
		throw std::runtime_error("Error, Can't Create Tr button");

	if (this->MiniMizeButtonHwnd = CreateWindowEx(0, L"BUTTON", L"_", BS_PUSHBUTTON | BS_OWNERDRAW | WS_VISIBLE | WS_CHILD, 320, 10, 10, 10, this->MainHwnd, reinterpret_cast<HMENU>(BinApp::CTL_ID::ID_BUTTON_MINIMIZE), nullptr, nullptr); !this->MiniMizeButtonHwnd)
		throw std::runtime_error("Error, can't Create Minize Button");
	
	if (this->EditHWND = CreateWindowEx(0, L"EDIT", NULL, WS_VISIBLE | WS_CHILD, 100, 100, 150, 20, this->MainHwnd, reinterpret_cast<HMENU>(BinApp::CTL_ID::ID_EDIT), nullptr, nullptr); !this->EditHWND)
		throw std::runtime_error("Error, can't create Edit");

	HFONT hFont = CreateFont(18, 0, 0, 0, FW_REGULAR, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"Consolas");
	SendMessage(this->EditHWND, WM_SETFONT, reinterpret_cast<WPARAM>(hFont), TRUE);
}

LRESULT CALLBACK BinApp::ApplicationProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	BinApp* pApp;
	if (uMsg == WM_NCCREATE){
		pApp = static_cast<BinApp*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
		SetLastError(0);
		if (!SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pApp))){
			if (GetLastError() != 0)
				return false;
		}
	}
	else{
		pApp = reinterpret_cast<BinApp*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	if (pApp){
		pApp->MainHwnd = hwnd;
		return pApp->WindProc(hwnd, uMsg, wParam, lParam);
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void BinApp::LoadSettingFromFile() {
	std::string FileName = "St.txt";
	std::ofstream fl;
	std::ifstream fl1;
	fl1.open(FileName);
	if (!fl1.is_open()) {
		fl1.close();
		fl.open(FileName);
		fl << "Theme = Black";
		fl.close();
	}

	std::string config_str;
	std::ifstream inf;

	inf.open(FileName);
	getline(inf, config_str, '\0');
	inf.close();

	std::string w;
	std::istringstream iss(config_str);
	std::vector<std::string> words;
	while (iss >> w) words.push_back(w);

	const int libWordsSize = 1;
	const std::string libWords[libWordsSize] = { "Theme" };

	const int ThemesCount = 2;
	const std::string Themes[ThemesCount] = { "Black","Skyes" };

	std::string tmpWord;

	bool finded = false;

	for (int i = 0; i < words.max_size(); i++){
		std::string tmpstr = words[i];
		if (finded == true) {
			break;
		}

		if (words[i] == "Theme") {
			int nint = i + 2;
			for (int j = 0; j < ThemesCount; j++){
				if (words[nint] == Themes[j]) {
					this->nCTheme = j;
					finded = true;
					break;
				}
			}
		}
		else if (words[i] == "Theme=") {
			int nint = i;
			nint++;
			for (int j = 0; j < ThemesCount; j++) {
				if (words[nint] == Themes[j]) {
					this->nCTheme = j;
					finded = true;
					break;
				}
			}
		}
	}

}