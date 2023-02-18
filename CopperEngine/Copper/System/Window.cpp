#include "Window.h"
#include "../System/Debug.h"
#include "../Input/Keyboard.h"

#include <iostream>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 1;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

static void APIENTRY GLFWDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam)
{
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return; // ignore these non-significant error codes

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         CU_DBG_CRITICAL("({}) {}", id, message); break;
	case GL_DEBUG_SEVERITY_MEDIUM:       CU_DBG_ERROR("({}) {}", id, message);    break;
	case GL_DEBUG_SEVERITY_LOW:          CU_DBG_WARN("({}) {}", id, message);     break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: CU_DBG_INFO("({}) {}", id, message);     break;
	}
}

namespace cu::sys
{
	Window::Window()
		: m_PosX(0), m_PosY(0), m_Width(800), m_Height(600), m_Title("CopperEngine app"), m_Fullscreen(false), m_Resizable(true), m_Window(nullptr), m_Monitor(nullptr)
	{
	}
	Window::Window(const WindowProperties& prop) : m_PosX(prop.Position.X), m_PosY(prop.Position.Y), m_Width(prop.Size.X), m_Height(prop.Size.Y), m_Title(prop.Title), m_Fullscreen(false), m_Resizable(true), m_Window(nullptr), m_Monitor(nullptr)
	{
		if (!glfwInit())
		{
			Debug::Critical("Failed to init GLFW.");
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

		m_Monitor = glfwGetPrimaryMonitor();

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.data(), nullptr, nullptr);

		glfwSetWindowPos(m_Window, m_PosX, m_PosY);
		if (m_Window == nullptr)
		{
			Debug::Critical("Failed to create GLFW window.");
			return;
		}
		glfwMakeContextCurrent(m_Window);
		glfwFocusWindow(m_Window);

		glfwSetWindowUserPointer(m_Window, this);
		glfwSetFramebufferSizeCallback(m_Window, GLFWFrameBufferSizeCallback);

		Keyboard::Initialize(m_Window);

		if (gl3wInit() != GL3W_OK)
		{
			Debug::Critical("Failed to initialize GL3W.");
			return;
		}

		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD dwMode = 0;
		GetConsoleMode(hOut, &dwMode);
		dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		SetConsoleMode(hOut, dwMode);

		int flags;
		glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
		{
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(GLFWDebugOutput, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		}
		return;
	}
	Window::~Window()
	{
		Cleanup();
	}
	unsigned int Window::GetPosX() const
	{
		return m_PosX;
	}
	unsigned int Window::GetPosY() const
	{
		return m_PosY;
	}

	void Window::SetPosX(unsigned int x)
	{
		m_PosX = x;
		glfwSetWindowPos(m_Window, m_PosX, m_PosY);
	}
	void Window::SetPosY(unsigned int y)
	{
		m_PosY = y;
		glfwSetWindowPos(m_Window, m_PosX, m_PosY);
	}
	void Window::SetPosition(unsigned int x, unsigned int y)
	{
		m_PosX = x;
		m_PosY = y;
		glfwSetWindowPos(m_Window, m_PosX, m_PosY);
	}
	unsigned int Window::GetWidth() const
	{
		return m_Width;
	}
	unsigned int Window::GetHeight() const
	{
		return m_Height;
	}
	void Window::SetWidth(unsigned int width)
	{
		m_Width = width;
		glfwSetWindowSize(m_Window, m_Width, m_Height);
	}
	void Window::SetHeight(unsigned int height)
	{
		m_Height = height;
		glfwSetWindowSize(m_Window, m_Width, m_Height);
	}
	void Window::SetSize(unsigned int width, unsigned int height)
	{
		m_Width = width;
		m_Height = height;
		glfwSetWindowSize(m_Window, m_Width, m_Height);
	}
	std::string_view Window::GetTitle() const
	{
		return m_Title;
	}
	void Window::SetTitle(std::string_view title)
	{
		m_Title = title;
		glfwSetWindowTitle(m_Window, m_Title.data());
	}
	void Window::SetFullscreen(bool flag)
	{
		if (m_Fullscreen == flag) return;

		m_Fullscreen = flag;
		if (m_Fullscreen)
		{
			const GLFWvidmode* mode = glfwGetVideoMode(m_Monitor);
			glfwSetWindowMonitor(m_Window, m_Monitor, 0, 0, mode->width, mode->height, 0);
		}
		else
		{
			glfwSetWindowMonitor(m_Window, nullptr, m_PosX, m_PosY, m_Width, m_Height, 0);
			SetResizable(true);
		}
	}
	void Window::SetResizable(bool flag)
	{
		if (m_Resizable == flag) return;

		m_Resizable = flag;
		if (m_Resizable)
			glfwSetWindowAttrib(m_Window, GLFW_RESIZABLE, GLFW_TRUE);
		else
			glfwSetWindowAttrib(m_Window, GLFW_RESIZABLE, GLFW_FALSE);
	}
	void Window::Close()
	{
		glfwSetWindowShouldClose(m_Window, true);
	}
	bool Window::IsOpen() const
	{
		return !glfwWindowShouldClose(m_Window);
	}
	void Window::UpdateFrame() const
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}
	void Window::Cleanup()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}
	void Window::GLFWFrameBufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		auto& self = *static_cast<Window*>(glfwGetWindowUserPointer(window));
		if (!self.m_Fullscreen)
		{
			self.m_Width = width;
			self.m_Height = height;
		}
		glViewport(0, 0, width, height);
	}
}