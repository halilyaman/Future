#include "ftpch.h"
#include "Application.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Future
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		FT_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

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

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher Dispatcher(e);
		Dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			if (e.Handled)
			{
				break;
			}
			it--;
			(*it)->OnEvent(e);
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::PopLayer(Layer* layer)
	{
		m_LayerStack.PopLayer(layer);
		layer->OnDetach();
	}

	void Application::PopOverlay(Layer* overlay)
	{
		m_LayerStack.PopOverlay(overlay);
		overlay->OnDetach();
	}
}