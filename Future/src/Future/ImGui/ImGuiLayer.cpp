#include "ftpch.h"
#include "ImGuiLayer.h"
#include "Future/Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "GLFW/glfw3.h"
#include "Future/Application.h"
#include "Future/Input.h"
#include "Future/KeyCodes.h"

namespace Future
{
	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer"), m_Time(0)
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		// setup imgui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		// setup imgui style
		ImGui::StyleColorsDark();

		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// TEMPORARY: should eventually use Future key codes
		io.KeyMap[ImGuiKey_Tab] = FT_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = FT_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = FT_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = FT_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = FT_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = FT_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = FT_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = FT_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = FT_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = FT_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = FT_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = FT_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = FT_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = FT_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = FT_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = FT_KEY_A;
		io.KeyMap[ImGuiKey_C] = FT_KEY_C;
		io.KeyMap[ImGuiKey_V] = FT_KEY_V;
		io.KeyMap[ImGuiKey_X] = FT_KEY_X;
		io.KeyMap[ImGuiKey_Y] = FT_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = FT_KEY_Z;

		// setup backend
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();

		// set display size for imgui
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		// set delta time for imgui
		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		// Start imgui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		// show demo window
		static bool showDemo = true;
		ImGui::ShowDemoWindow(&showDemo);

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& e)
	{
		EventDispatcher Dispatcher(e);

		Dispatcher.Dispatch<MouseButtonPressedEvent>(FT_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressed));
		Dispatcher.Dispatch<MouseButtonReleasedEvent>(FT_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleased));
		Dispatcher.Dispatch<MouseMovedEvent>(FT_BIND_EVENT_FN(ImGuiLayer::OnMouseMoved));
		Dispatcher.Dispatch<MouseScrolledEvent>(FT_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolled));
		Dispatcher.Dispatch<KeyPressedEvent>(FT_BIND_EVENT_FN(ImGuiLayer::OnKeyPressed));
		Dispatcher.Dispatch<KeyReleasedEvent>(FT_BIND_EVENT_FN(ImGuiLayer::OnKeyReleased));
		Dispatcher.Dispatch<KeyTypedEvent>(FT_BIND_EVENT_FN(ImGuiLayer::OnKeyTyped));
		Dispatcher.Dispatch<WindowResizeEvent>(FT_BIND_EVENT_FN(ImGuiLayer::OnWindowResized));
	}

	bool ImGuiLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleased(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;

		return false;
	}

	bool ImGuiLayer::OnMouseMoved(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolled(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel += e.GetYOffset();
		io.MouseWheelH += e.GetXOffset();

		return false;
	}

	bool ImGuiLayer::OnKeyPressed(KeyPressedEvent& e) 
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;

		io.KeyCtrl = io.KeysDown[FT_KEY_LEFT_CONTROL] || io.KeysDown[FT_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[FT_KEY_LEFT_SHIFT] || io.KeysDown[FT_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[FT_KEY_LEFT_ALT] || io.KeysDown[FT_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[FT_KEY_LEFT_SUPER] || io.KeysDown[FT_KEY_RIGHT_SUPER];

		return false;
	}

	bool ImGuiLayer::OnKeyReleased(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;

		return false;
	}

	bool ImGuiLayer::OnKeyTyped(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		int keyCode = e.GetKeyCode();

		if (keyCode > 0 && keyCode < 0x10000)
		{
			io.AddInputCharacter((unsigned int) keyCode);
		}

		return false;
	}

	bool ImGuiLayer::OnWindowResized(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());

		return false;
	}
}