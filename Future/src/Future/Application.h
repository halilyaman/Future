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

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

		bool OnWindowClose(WindowCloseEvent& e);
	private:
		static Application* s_Instance;
	};

	// To be defined in client
	Application* CreateApplication();
}



