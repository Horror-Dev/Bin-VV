#include"BinApp.h"

void BinApp::initFactory() {
	HRESULT hr{};

	if (hr = D2D1CreateFactory(D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_SINGLE_THREADED,&this->pFactory); !SUCCEEDED(hr))
		throw std::runtime_error("Error Can't init Drawing Factory");
	
	if (hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_ISOLATED, __uuidof(IDWriteFactory),reinterpret_cast<IUnknown**>(&m_pDWriteFactory)); !SUCCEEDED(hr))
		throw std::runtime_error("Error Can't init writing Factory");

}

void BinApp::CreateResources() {
	HRESULT hr{};

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

	hr = this->pFactory->CreateDCRenderTarget(&props, &this->m_pDCRT);
	if (!SUCCEEDED(hr)) {
		exit(4);
	}

	hr = this->m_pDCRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &this->pBrush);

	if (!SUCCEEDED(hr)) {
		exit(4);
	}

}

void BinApp::DrawBackGround() {
	D2D1::ColorF F1 = NULL;
	D2D1::ColorF F2 = NULL;

	switch (this->nCTheme)
	{
	case 0:
		F1 = D2D1::ColorF(0.137255f, 0.145098f, 0.149020f);
		F2 = D2D1::ColorF(0.254902f, 0.262745f, 0.270588f);
		break;
	case 1:
		F1 = D2D1::ColorF(0.184314f, 0.501961f, 0.929412f);
		F2 = D2D1::ColorF(0.337255f, 0.800000f, 0.949020f);
		break;
	case 2:
		F1 = D2D1::ColorF(0.262745f, 0.262745f, 0.262745f);
		F2 = D2D1::ColorF(0.F, 0.F, 0.F);
		break;
	}

	
	const D2D1_GRADIENT_STOP gradientStops[] =
	{
		{ 0.9f, D2D1::ColorF(F1) },
		{ 0.1f, D2D1::ColorF(F2) },
	};

	ID2D1GradientStopCollection* gSC;

	HRESULT hr = m_pDCRT->CreateGradientStopCollection(gradientStops, _countof(gradientStops), &gSC);
	if (!SUCCEEDED(hr)) {
		exit(EXIT_FAILURE);
	}

	const D2D1_SIZE_F size = this->m_pDCRT->GetSize();
	const D2D1_POINT_2F start = D2D1::Point2F(0.0f, 0.0f);
	const D2D1_POINT_2F end = D2D1::Point2F(size.width, size.height);

	ID2D1LinearGradientBrush* lgb = nullptr;

	const D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES properties = D2D1::LinearGradientBrushProperties(start, end);
	this->m_pDCRT->CreateLinearGradientBrush(properties, gSC, &lgb);

	const D2D1_RECT_F rect = D2D1::RectF(0, 0, size.width, size.height);

	this->m_pDCRT->FillRectangle(rect, lgb);
}

void BinApp::ButtonDrawing(const int &nId, PDRAWITEMSTRUCT pDis) {
	D2D1_SIZE_U size = D2D1::SizeU(
		this->Width,
		this->Hieght
	);

	HRESULT hr{};


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

	switch (this->nCTheme){
	case 0:
		m_pDCRT->Clear(D2D1::ColorF(0.203922f, 0.211765f, 0.219608f));
		break;
	case 1:
		m_pDCRT->Clear(D2D1::ColorF(0.254902f, 0.603922f, 0.713726f));
		break;
	case 2:
		m_pDCRT->Clear(D2D1::ColorF(0.262745f, 0.262745f, 0.262745f, 0.6f));
		break;
	}
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
	
	switch (this->nCTheme) {
	case 0:
		m_pDCRT->Clear(D2D1::ColorF(0.203922f, 0.211765f, 0.219608f));
		break;
	case 1:
		m_pDCRT->Clear(D2D1::ColorF(0.254902f, 0.603922f, 0.713726f));
		break;
	case 2:
		m_pDCRT->Clear(D2D1::ColorF(0.262745f, 0.262745f, 0.262745f, 0.6f));
		break;
	}

	m_pDCRT->FillEllipse(&this->ellipse, this->pSBrush);
	this->m_pDCRT->EndDraw();
}

void BinApp::DrawConvertButton(PDRAWITEMSTRUCT pDis) {
	m_pDWriteFactory->CreateTextFormat(L"Consolas", nullptr, DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_NORMAL, 20.f, L"", &this->TextButtonFormt);
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

	m_pDWriteFactory->CreateTextFormat(L"Consolas", nullptr, DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_NORMAL, 20.f, L"", &this->m_pTextFormat);
	
	this->m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	this->m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

	const std::wstring text{L"Convert"};
	this->pBrush->SetColor(D2D1::ColorF(0.501961f, 0.501961f, 0.501961f));
	this->m_pDCRT->DrawText(text.c_str(), 9, this->m_pTextFormat, D2D1::RectF(0.0f, 0.0f, static_cast<FLOAT>(pDis->rcItem.right), static_cast<FLOAT>(pDis->rcItem.bottom)), this->pBrush);
	this->m_pDCRT->EndDraw();	
	safeRelease(&this->TextButtonFormt);
}

void BinApp::DrawTitle() {
	m_pDWriteFactory->CreateTextFormat(L"Consolas", nullptr, DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_NORMAL, 20.f, L"", &this->TextFormt);
	ID2D1SolidColorBrush* pbrsh;
	this->m_pDCRT->CreateSolidColorBrush(D2D1::ColorF(1.000000f, 0.843137f, 0.000000f), &pbrsh);
	m_pDCRT->DrawText(this->AppName.c_str(), this->AppName.length(), this->TextFormt, D2D1::RectF(10.f,10.f,10.f + 120.f, 10.f + 100.f), pbrsh);
	safeRelease(&this->TextFormt);
	safeRelease(&pbrsh);
}
