#pragma once

#include <Future/Core.h>
#include <Future/Events/Event.h>
#include <Future/Window.h>

namespace Future
{
	class FUTURE_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in client
	Application* CreateApplication();
}



