#include "ftpch.h"
#include "Application.h"

#include <GLFW/glfw3.h>

namespace Future
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
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
}