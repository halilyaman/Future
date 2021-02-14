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
	return new Sandbox();
}