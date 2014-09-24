#pragma once

#include "..\Common\DeviceResources.h"
#include "..\Common\StepTimer.h"
namespace SampleElements
{
	// Render 2D elements
	class Sample2DSceneRenderer
	{
	public:
		Sample2DSceneRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		void CreateDeviceDependentResources();
		void ReleaseDeviceDependentResources();
		void Update(DX::StepTimer const& timer);
		void Render();
	private:
		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_blueBrush;
	};
}
