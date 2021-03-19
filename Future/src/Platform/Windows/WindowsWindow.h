#pragma once

#include <Future/Window.h>
#include <GLFW/glfw3.h>
#include "Platform/OpenGL/OpenGLContext.h"

namespace Future
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; };
		inline unsigned int GetHeight() const override { return m_Data.Height; };

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; };
		void SetVSync(bool enabled) override;
		inline bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const override { return m_Window; };

	private:
		virtual void Init(const WindowProps& props);
		virtual void ShutDown();

	private:
		GLFWwindow* m_Window;
		OpenGLContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width = 0, Height = 0;
			bool VSync = false;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}



