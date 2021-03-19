#include <Future.h>
#include "imgui/imgui.h"

class ExampleLayer : public Future::Layer
{
public:
	ExampleLayer() : Layer("ExampleLayer1") {}

	virtual void OnUpdate() override
	{
	}

	virtual void OnEvent(Future::Event& e) override
	{
		if (e.GetEventType() == Future::EventType::KeyPressed)
		{
			Future::KeyPressedEvent& keyPressedEvent = (Future::KeyPressedEvent&)e;

			if (keyPressedEvent.GetKeyCode() == FT_KEY_TAB)
			{
				FT_TRACE("{0}: Tab key is pressed (event)", this->GetName());
				keyPressedEvent.Handled = true;
			}
		}
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("ExampleLayer1");
		ImGui::Text("Test");
		ImGui::End();
	}
};

class ExampleLayer2 : public Future::Layer
{
public:
	ExampleLayer2() : Layer("ExampleLayer2") {}

	virtual void OnUpdate() override
	{
	}

	virtual void OnEvent(Future::Event& e) override
	{
		if (e.GetEventType() == Future::EventType::KeyPressed)
		{
			Future::KeyPressedEvent& keyPressedEvent = (Future::KeyPressedEvent&)e;

			if (keyPressedEvent.GetKeyCode() == FT_KEY_TAB)
			{
				FT_TRACE("{0}: Tab key is pressed (event)", this->GetName());
				keyPressedEvent.Handled = true;
			}

		}
	}

	virtual void OnImGuiRender() override
	{
	}
};

class Sandbox : public Future::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushLayer(new ExampleLayer2());
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