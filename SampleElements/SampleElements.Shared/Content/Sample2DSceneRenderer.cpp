#include "pch.h"
#include "Sample2DSceneRenderer.h"

#include "Common/DirectXHelper.h"

using namespace SampleElements;

Sample2DSceneRenderer::Sample2DSceneRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources) : m_deviceResources(deviceResources)
{
	CreateDeviceDependentResources();
}

void Sample2DSceneRenderer::Update(DX::StepTimer const& timer)
{

}

void Sample2DSceneRenderer::Render()
{
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

	context->DrawRectangle(
		D2D1::RectF(100.0f, 100.0f, 500.0f, 500.0f),
		m_blueBrush.Get(),
		4.0f,
		m_stroke
		);

	DX::ThrowIfFailed(
		context->EndDraw()
		);
}

void Sample2DSceneRenderer::CreateDeviceDependentResources()
{
	DX::ThrowIfFailed(
		m_deviceResources->GetD2DDeviceContext()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue), &m_blueBrush)
		);
}

void Sample2DSceneRenderer::ReleaseDeviceDependentResources()
{
	m_blueBrush.Reset();
}
