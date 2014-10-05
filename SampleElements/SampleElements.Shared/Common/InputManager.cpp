#include "pch.h"
#include "InputManager.h"

namespace InputManager
{
	InputManager^ m_inputManager = ref new InputManager();

	void InputManager::Initialize(CoreWindow^ window)
	{
		window->PointerPressed += ref new TypedEventHandler<CoreWindow ^, PointerEventArgs ^>(this, &InputManager::OnPointerPressed);
		window->PointerReleased += ref new TypedEventHandler<CoreWindow ^, PointerEventArgs ^>(this, &InputManager::OnPointerReleased);
		window->PointerMoved += ref new TypedEventHandler<CoreWindow ^, PointerEventArgs ^>(this, &InputManager::OnPointerMoved);

		m_gestureRecognizer = ref new GestureRecognizer();
		m_gestureRecognizer->GestureSettings = GestureSettings::Tap | GestureSettings::Drag | GestureSettings::DoubleTap | GestureSettings::Hold;

		m_gestureRecognizer->Tapped += ref new TypedEventHandler<GestureRecognizer ^, TappedEventArgs ^>(this, &InputManager::OnTapped);
		m_gestureRecognizer->Dragging += ref new TypedEventHandler<GestureRecognizer ^, DraggingEventArgs ^>(this, &InputManager::OnDragging);
		m_gestureRecognizer->Holding += ref new TypedEventHandler<GestureRecognizer ^, HoldingEventArgs ^>(this, &InputManager::OnHolding);
		
	}

	void InputManager::OnPointerPressed(CoreWindow ^sender, PointerEventArgs ^args)
	{
		m_gestureRecognizer->ProcessDownEvent(args->CurrentPoint);
	}

	void InputManager::OnPointerReleased(CoreWindow ^sender, PointerEventArgs ^args)
	{
		m_gestureRecognizer->ProcessUpEvent(args->CurrentPoint);
	}

	void InputManager::OnPointerMoved(CoreWindow ^sender, PointerEventArgs ^args)
	{
		m_gestureRecognizer->ProcessMoveEvents(args->GetIntermediatePoints());
	}

	void InputManager::OnTapped(GestureRecognizer ^sender, TappedEventArgs ^args)
	{
		if (args->TapCount == 2) // double tap
		{

		}
		else // single tap
		{

		}
	}

	void InputManager::OnDragging(GestureRecognizer ^sender, DraggingEventArgs ^args)
	{

	}

	void InputManager::OnHolding(GestureRecognizer ^sender, HoldingEventArgs ^args)
	{
	}
}