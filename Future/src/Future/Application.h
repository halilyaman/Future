#pragma once

#include "Core.h"

namespace Future
{
	class FUTURE_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	// To be defined in client
	Application* CreateApplication();
}



