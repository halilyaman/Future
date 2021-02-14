#pragma once

#ifdef FT_PLATFORM_WINDOWS

extern Future::Application* Future::CreateApplication();

int main(int* argc, char** argv)
{
	auto app = Future::CreateApplication();
	app->Run();
	delete app;
}

#endif