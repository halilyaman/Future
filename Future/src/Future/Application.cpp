#include "Application.h"

#include "Future/Events/ApplicationEvent.h"
#include "Future/Log.h"

namespace Future
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);

		if (e.IsInCategory(EventCategoryApplication))
		{
			FT_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			FT_TRACE(e);
		}

		while (true);
	}
}