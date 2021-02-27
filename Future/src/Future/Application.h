#pragma once

#include <Future/Core.h>
#include <Future/Events/Event.h>
#include <Future/Window.h>
#include <Future/Events/ApplicationEvent.h>
#include <Future/LayerStack.h>

namespace Future
{
	class FUTURE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

		bool OnWindowClose(WindowCloseEvent& e);
	};

	// To be defined in client
	Application* CreateApplication();
}



