#include <Future.h>

class Sandbox : public Future::Application
{
public:
	Sandbox()
	{
		
	}

	~Sandbox()
	{

	}
};

Future::Application* Future::CreateApplication()
{
	Sandbox* sandbox = new Sandbox();

	return sandbox;
}