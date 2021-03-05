#include <Future.h>

class ExampleLayer : public Future::Layer
{
public:
	ExampleLayer() : Layer("ExampleLayer") {}

	void OnUpdate() override
	{
		
	}

	void OnEvent(Future::Event& event) override
	{
		FT_TRACE(event);
	}
};

class Sandbox : public Future::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Future::ImGuiLayer());
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