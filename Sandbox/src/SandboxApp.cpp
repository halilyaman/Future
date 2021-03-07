#include <Future.h>

class ExampleLayer : public Future::Layer
{
public:
	ExampleLayer() : Layer("ExampleLayer") {}

	void OnUpdate() override
	{
		if (Future::Input::IsKeyPressed(FT_KEY_TAB))
		{
			FT_TRACE("Tab key is pressed (poll)");
		}
	}

	void OnEvent(Future::Event& e) override
	{
		if (e.GetEventType() == Future::EventType::KeyPressed)
		{
			Future::KeyPressedEvent& keyPressedEvent = (Future::KeyPressedEvent&)e;

			if (keyPressedEvent.GetKeyCode() == FT_KEY_TAB)
			{
				FT_TRACE("Tab key is pressed (event)");
			}

		}
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