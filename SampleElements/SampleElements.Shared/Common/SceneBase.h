#pragma once

#include "Common\DeviceResources.h"
#include "Common\StepTimer.h"

namespace Base
{
	class SceneBase
	{
	public:
		virtual void CreateDeviceDependentResources();
		virtual void ReleaseDeviceDependentResources();
		virtual void Update(DX::StepTimer const& timer);
		virtual void Render();
	protected:
		SceneBase(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;
		Microsoft::WRL::ComPtr<ID2D1Bitmap> m_pBackground;
	};

}