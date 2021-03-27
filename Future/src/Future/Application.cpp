#include "ftpch.h"
#include "Application.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Future
{
	Application* Application::s_Instance = nullptr;

	void setupTriangle()
	{
		float vertices[] =
		{
			 0.0f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f
		};

		unsigned int vbo;
		glGenBuffers(1, &vbo);
		FT_CORE_TRACE("Created buffer object (unbounded)");
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		FT_CORE_TRACE("Bound buffer object");
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		FT_CORE_TRACE("Set data to currently bound buffer object");

		const char* vertexShaderSource =
			"#version 330 core\n"
			"layout (location = 0) in vec3 pos;\n"
			"void main()\n"
			"{\n"
			"	gl_Position = vec4(pos, 1.0);\n"
			"}\n";

		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		FT_CORE_TRACE("Created vertex shader");
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		FT_CORE_TRACE("Set source code of vertex shader");
		glCompileShader(vertexShader);
		FT_CORE_TRACE("Compiled vertex shader");

		int vertexCompiled;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexCompiled);
		if (!vertexCompiled)
		{
			int logLength = 0;
			glGetShaderInfoLog(vertexShader, 512, &logLength, infoLog);
			std::stringstream ss;
			ss << "VERTEX SHADER COMPILE ERROR: " << infoLog;
			FT_CORE_ERROR(ss.str());
		}
		else
		{
			FT_CORE_TRACE("Vertex shader compiled successfully");
		}

		const char* fragmentShaderSource =
			"#version 330 core\n"
			"out vec4 color;\n"
			"void main()\n"
			"{\n"
			"	color = vec4(0.0f, 0.5f, 0.5f, 1.0f);\n"
			"}\n";

		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		FT_CORE_TRACE("Created fragment shader");
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		FT_CORE_TRACE("Set source code of fragment shader");
		glCompileShader(fragmentShader);
		FT_CORE_TRACE("Compiled fragment shader");

		int fragmentCompiled;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentCompiled);
		if (!fragmentCompiled)
		{
			int logLength = 0;
			glGetShaderInfoLog(fragmentShader, 512, &logLength, infoLog);
			std::stringstream ss;
			ss << "FRAGMENT SHADER COMPILE ERROR: " << infoLog;
			FT_CORE_ERROR(ss.str());
		}
		else
		{
			FT_CORE_TRACE("Fragment shader compiled successfully");
		}

		unsigned int triangleShaderProgram;
		triangleShaderProgram = glCreateProgram();
		FT_CORE_TRACE("Created Triangle Shader Program");
		glAttachShader(triangleShaderProgram, vertexShader);
		glAttachShader(triangleShaderProgram, fragmentShader);
		FT_CORE_TRACE("Attached vertex and fragment shaders to the Triangle Shader Program");
		glLinkProgram(triangleShaderProgram);

		int programLinked;
		glGetProgramiv(triangleShaderProgram, GL_LINK_STATUS, &programLinked);
		if (!programLinked)
		{
			int logLength = 0;
			glGetProgramInfoLog(triangleShaderProgram, 512, &logLength, infoLog);
			std::stringstream ss;
			ss << "SHADERS LINK ERROR: " << infoLog;
			FT_CORE_ERROR(ss.str());
		}
		else
		{
			FT_CORE_TRACE("Triangle Shader Program linked successfully");
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
		}

		glUseProgram(triangleShaderProgram);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
	}

	Application::Application()
	{
		FT_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		// create window
		m_Window = std::unique_ptr<Window>(Window::Create());

		// create Eventcallback function
		std::function<void(Event&)> EventcallbackFn = FT_BIND_EVENT_FN(Application::OnEvent);

		// set Eventcallback function
		m_Window->SetEventCallback(EventcallbackFn);

		// add ImGuiLayer to the layer stack
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		setupTriangle();
	}

	Application::~Application()
	{
		
	}

	void Application::Run()
	{
		while (this->m_Running)
		{
			glClearColor(0.2f, 0.0f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glDrawArrays(GL_TRIANGLES, 0, 3);

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			// render ImGui for all layers
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher Dispatcher(e);
		Dispatcher.Dispatch<WindowCloseEvent>(FT_BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			if (e.Handled)
			{
				break;
			}
			it--;
			(*it)->OnEvent(e);
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::PopLayer(Layer* layer)
	{
		m_LayerStack.PopLayer(layer);
	}

	void Application::PopOverlay(Layer* overlay)
	{
		m_LayerStack.PopOverlay(overlay);
	}
}