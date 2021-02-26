#include "ftpch.h"
#include "Application.h"

#include <GLFW/glfw3.h>

namespace Future
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		// create window
		m_Window = std::unique_ptr<Window>(Window::Create());

		// create Eventcallback function
		std::function<void(Event&)> EventcallbackFn = BIND_EVENT_FN(OnEvent);

		// set Eventcallback function
		m_Window->SetEventCallback(EventcallbackFn);
	}

	Application::~Application()
	{
		
	}

	void Application::Run()
	{
		while (this->m_Running)
		{
			glClearColor(0.1, 0.3, 0.8, 1.0);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		FT_CORE_INFO("{0}", e);
		EventDispatcher Dispatcher(e);
		Dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}