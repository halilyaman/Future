#include "ftpch.h"
#include "OpenGLContext.h"

#include "glad/glad.h"

namespace Future
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
	{
		FT_CORE_ASSERT(windowHandle, "Window handle is null!");
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		// initialize Glad
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		FT_CORE_ASSERT(status, "Failed to initialize Glad!");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}