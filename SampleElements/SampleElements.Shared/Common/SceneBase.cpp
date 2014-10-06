#include "pch.h"
#include "SceneBase.h"

#include "Common/DirectXHelper.h"
#include "Common/BitmapHelper.h"

using namespace Base;
using namespace BitmapHelper;
using namespace DX;

SceneBase::SceneBase(const std::shared_ptr<DeviceResources>& deviceResources) : m_deviceResources(deviceResources)
{
}

void SceneBase::Update(StepTimer const& timer)
{
}

void SceneBase::Render()
{
	ID2D1DeviceContext* context = m_deviceResources->GetD2DDeviceContext();

	context->BeginDraw();
	context->Clear(D2D1::ColorF(D2D1::ColorF::CornflowerBlue));

	auto m_bitmapSize = m_pBackground->GetSize();

	context->DrawBitmap(
		m_pBackground.Get(),
		D2D1::RectF(0.0f, 0.0f, m_bitmapSize.width, m_bitmapSize.height)
		);

	ThrowIfFailed(
		context->EndDraw()
		);
}

void SceneBase::CreateDeviceDependentResources()
{
}

void SceneBase::ReleaseDeviceDependentResources()
{
}
