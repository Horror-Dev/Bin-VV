#include"BinApp.h"

void BinApp::initFactory() {
	HRESULT hr{};

	if (hr = D2D1CreateFactory(D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_SINGLE_THREADED,&this->pFactory); !SUCCEEDED(hr))
		throw std::runtime_error("Error Can't init Drawing Factory");
	
	if (hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_ISOLATED, __uuidof(IDWriteFactory),reinterpret_cast<IUnknown**>(&m_pDWriteFactory)); !SUCCEEDED(hr))
		throw std::runtime_error("Error Can't init writing Factory");

	this->pFactory->GetDesktopDpi(&this->dipX, &this->dipY);

}

void BinApp::CreateResources() {
	HRESULT hr{};

	if (hr = this->pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(this->MainHwnd, D2D1::SizeU(this->Width, this->Hieght)), &this->pRT); !SUCCEEDED(hr))
		throw std::runtime_error("Error Can't CreateHwndRenderTarget");

	this->pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &this->pBrush);

}

void BinApp::DrawBackGround() {
	D2D1::ColorF FC = D2D1::ColorF(0.015686f, 0.309804f, 0.607843f);

	const D2D1_GRADIENT_STOP gradientStops[] =
	{
		{ 0.9f, D2D1::ColorF(0.137255f, 0.145098f, 0.149020f) },
		{ 0.1f, D2D1::ColorF(0.254902f, 0.262745f, 0.270588f) },
	};

	ID2D1GradientStopCollection* gSC;

	HRESULT hr = pRT->CreateGradientStopCollection(gradientStops, _countof(gradientStops), &gSC);
	if (!SUCCEEDED(hr)) {
		exit(EXIT_FAILURE);
	}

	const D2D1_SIZE_F size = this->pRT->GetSize();
	const D2D1_POINT_2F start = D2D1::Point2F(0.0f, 0.0f);
	const D2D1_POINT_2F end = D2D1::Point2F(size.width, size.height);

	ID2D1LinearGradientBrush* lgb = nullptr;

	const D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES properties = D2D1::LinearGradientBrushProperties(start, end);
	this->pRT->CreateLinearGradientBrush(properties, gSC, &lgb);

	const D2D1_RECT_F rect = D2D1::RectF(0, 0, size.width, size.height);

	this->pRT->FillRectangle(rect, lgb);
}

void BinApp::ButtonDrawing(const int &nId, PDRAWITEMSTRUCT pDis) {
	D2D1_SIZE_U size = D2D1::SizeU(
		this->Width,
		this->Hieght
	);

	D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
		D2D1_RENDER_TARGET_TYPE_DEFAULT,
		D2D1::PixelFormat(
			DXGI_FORMAT_B8G8R8A8_UNORM,
			D2D1_ALPHA_MODE_PREMULTIPLIED),
		0,
		0,
		D2D1_RENDER_TARGET_USAGE_NONE,
		D2D1_FEATURE_LEVEL_DEFAULT
	);

	HRESULT hr = this->pFactory->CreateDCRenderTarget(&props, &this->m_pDCRT);
	if (!SUCCEEDED(hr)) {
		exit(4);
	}
	hr = this->m_pDCRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &this->pBrush);
	hr = this->m_pDCRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Lime), &this->pSBrush);
	if (!SUCCEEDED(hr)) {
		exit(5);
	}
	hr = this->m_pDCRT->BindDC(pDis->hDC, &pDis->rcItem);
	if (!SUCCEEDED(hr)) {
		exit(6);
	}
	this->m_pDCRT->BeginDraw();
	this->m_pDCRT->Clear(D2D1::ColorF(D2D1::ColorF::Blue, 0.42f));

	switch (nId){
		case static_cast<int>(BinApp::CTL_ID::ID_BUTTON_CLOSE) :
			this->DrawCloseButton(pDis);
			break;
		case static_cast<int>(BinApp::CTL_ID::ID_BUTTON_MINIMIZE) :
				this->DrawMinimizeButton(pDis);
			break;
			case static_cast<int>(BinApp::CTL_ID::ID_BUTTON_TRANSF) :
				this->DrawConvertButton(pDis);
			break;
		default:
				exit(8);
			break;
	}
	this->m_pDCRT->EndDraw();
}

void BinApp::FreeResources() {
	safeRelease(&this->pSBrush);
	safeRelease(&this->pBrush);
	safeRelease(&this->pRT);
	safeRelease(&this->m_pDCRT);
	safeRelease(&this->pFactory);
	safeRelease(&this->TextFormt);
	safeRelease(&this->TextButtonFormt);
}

void BinApp::DrawCloseButton(PDRAWITEMSTRUCT pDis) {

	if (pDis->itemState & ODS_SELECTED) {
		this->pSBrush->SetColor(D2D1::ColorF(0.741176f, 0.000000f, 0.000000f));
	}
	else {
		this->pSBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Red));
	}

	D2D1_SIZE_F size = this->m_pDCRT->GetSize();
	const float x = size.width / 2;
	const float y = size.height / 2;
	const float radius = min(x, y);
	ellipse = D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius);
	m_pDCRT->Clear(D2D1::ColorF(0.203922f, 0.211765f, 0.219608f));
	m_pDCRT->FillEllipse(&this->ellipse, this->pSBrush);
}

void BinApp::DrawMinimizeButton(PDRAWITEMSTRUCT pDis) {

	if (pDis->itemState & ODS_SELECTED) {

		this->pSBrush->SetColor(D2D1::ColorF(0.043137f, 0.400000f, 0.137255f));
	}
	else {

		this->pSBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Lime));
	}

	D2D1_SIZE_F size = this->m_pDCRT->GetSize();
	const float x = size.width / 2;
	const float y = size.height / 2;
	const float radius = min(x, y);
	ellipse = D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius);
	m_pDCRT->Clear(D2D1::ColorF(0.203922f, 0.211765f, 0.219608f));
	m_pDCRT->FillEllipse(&this->ellipse, this->pSBrush);
	this->m_pDCRT->EndDraw();
}

void BinApp::DrawConvertButton(PDRAWITEMSTRUCT pDis) {
	m_pDWriteFactory->CreateTextFormat(L"Consolas", nullptr, DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_NORMAL, pixelToDipY(20.f), L"", &this->TextButtonFormt);
	m_pDCRT->Clear(D2D1::ColorF(D2D1::ColorF::Lime));
	if (pDis->itemState & ODS_SELECTED) {
		this->pSBrush->SetColor(D2D1::ColorF(0.043137f, 0.400000f, 0.137255f));
	}
	else {
		this->pSBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Lime));
	}
	this->m_pDCRT->FillRectangle(D2D1::RectF(0.f, 0.f, 1800.f, 110.f),this->pSBrush);
	if (pDis->itemState & ODS_SELECTED) {
		this->pSBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
		this->m_pDCRT->DrawRectangle(D2D1::RectF(5.f, 5.f, 145.f, 34.f), this->pSBrush);
	}
	const std::wstring text{L"Перевести"};
	this->pBrush->SetColor(D2D1::ColorF(0.501961f, 0.501961f, 0.501961f));
	this->m_pDCRT->DrawText(text.c_str(), text.length(), this->TextButtonFormt, D2D1::RectF(20.f, 80.f, 130.f, 4.f),this->pBrush);
	this->m_pDCRT->EndDraw();	
	safeRelease(&this->TextButtonFormt);
}

void BinApp::DrawTitle() {
	m_pDWriteFactory->CreateTextFormat(L"Consolas", nullptr, DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_NORMAL, pixelToDipY(20.f), L"", &this->TextFormt);
	ID2D1SolidColorBrush* pbrsh;
	this->pRT->CreateSolidColorBrush(D2D1::ColorF(1.000000f, 0.843137f, 0.000000f), &pbrsh);
	//this->pBrush->SetColor(D2D1::ColorF(1.000000f, 0.843137f, 0.000000f));
	pRT->DrawText(this->AppName.c_str(), this->AppName.length(), this->TextFormt, D2D1::RectF(this->pixelToDipX(10.f),this->pixelToDipY(10.f),this->pixelToDipX(10.f) + this->pixelToDipX(120.f), this->pixelToDipY(10.f) + this->pixelToDipY(100.f)), pbrsh);
	safeRelease(&this->TextFormt);
	safeRelease(&pbrsh);
}
