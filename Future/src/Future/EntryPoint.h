#pragma once

#ifdef FT_PLATFORM_WINDOWS

extern Future::Application* Future::CreateApplication();

int main(int* argc, char** argv)
{
	Future::Log::Init();
	
	FT_CORE_WARN("Initialized Log!");
	FT_INFO("Hello!");

	auto app = Future::CreateApplication();
	app->Run();
	delete app;
}

#endif