#include "pch.h"
#include "Sample2DSceneRenderer.h"

#include "Common/DirectXHelper.h"
#include "Common/BitmapHelper.h"

using namespace DX;
using namespace SampleElements;
using namespace BitmapHelper;

Sample2DSceneRenderer::Sample2DSceneRenderer(const std::shared_ptr<DeviceResources>& deviceResources) : SceneBase(deviceResources), m_deviceResources(deviceResources)
{
	CreateDeviceDependentResources();
}

void Sample2DSceneRenderer::Update(StepTimer const& timer)
{
	padding += 1.0f;
}

void Sample2DSceneRenderer::Render()
{
	SceneBase::Render();
	ID2D1DeviceContext* context = m_deviceResources->GetD2DDeviceContext();

	// Dash array for dashStyle D2D1_DASH_STYLE_CUSTOM
	float dashes[] = { 1.0f, 2.0f, 2.0f, 3.0f, 2.0f, 2.0f };
	ID2D1StrokeStyle* m_stroke;
	m_deviceResources->GetD2DFactory()->CreateStrokeStyle(
		D2D1::StrokeStyleProperties(
		D2D1_CAP_STYLE_FLAT,
		D2D1_CAP_STYLE_FLAT,
		D2D1_CAP_STYLE_ROUND,
		D2D1_LINE_JOIN_MITER,
		10.0f,
		D2D1_DASH_STYLE_CUSTOM,
		0.0f),
		dashes,
		ARRAYSIZE(dashes),
		&m_stroke
		);

	context->BeginDraw();
	//context->Clear(D2D1::ColorF(D2D1::ColorF::CornflowerBlue));

	auto m_bitmapSize = m_pBitmap->GetSize();

	context->DrawBitmap(
		m_pBitmap.Get(),
		D2D1::RectF(200.0f, padding, m_bitmapSize.width + 200.0f, m_bitmapSize.height + padding)
		);

	context->DrawRectangle(
		D2D1::RectF(100.0f, 100.0f, 500.0f, 500.0f),
		m_pBlueBrush.Get(),
		4.0f,
		m_stroke
		);

	context->FillRectangle(
		D2D1::RectF(600.0f, 400.0f, 900.0f, 700.0f),
		m_pLinearGradientBrush.Get()
		);

	context->DrawLine(
		D2D1::Point2F(200, 300),
		D2D1::Point2F(800, 500),
		m_pBlueBrush.Get(),
		10.0f,
		m_stroke
		);

	DX::ThrowIfFailed(
		context->EndDraw()
		);
}

void Sample2DSceneRenderer::CreateDeviceDependentResources()
{
	ID2D1DeviceContext* context = m_deviceResources->GetD2DDeviceContext();

	DX::ThrowIfFailed(
		context->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue), &m_pBlueBrush)
		);
	// Create an array of gradient stops to put in the gradient stop
	// collection that will be used in the gradient brush.
	ID2D1GradientStopCollection *pGradientStops = NULL;

	D2D1_GRADIENT_STOP gradientStops[2];
	gradientStops[0].color = D2D1::ColorF(D2D1::ColorF::Yellow, 1);
	gradientStops[0].position = 0.0f;
	gradientStops[1].color = D2D1::ColorF(D2D1::ColorF::ForestGreen, 1);
	gradientStops[1].position = 1.0f;
	// Create the ID2D1GradientStopCollection from a previously
	// declared array of D2D1_GRADIENT_STOP structs.
	context->CreateGradientStopCollection(
		gradientStops,
		2,
		D2D1_GAMMA_2_2,
		D2D1_EXTEND_MODE_CLAMP,
		&pGradientStops
		);

	DX::ThrowIfFailed(
		context->CreateLinearGradientBrush(
		D2D1::LinearGradientBrushProperties(D2D1::Point2F(600, 400), D2D1::Point2F(900, 700)),
		pGradientStops,
		&m_pLinearGradientBrush
		)
		);

	DX::ThrowIfFailed(LoadBitmapFromFile(m_deviceResources.get(), L"Images/drop.png", &m_pBitmap));
	DX::ThrowIfFailed(LoadBitmapFromFile(m_deviceResources.get(), L"Images/bg.jpg", &m_pBackground));

	padding = 0;
}

void Sample2DSceneRenderer::ReleaseDeviceDependentResources()
{
	m_pBlueBrush.Reset();
}
