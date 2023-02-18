#pragma once

#include <string>
#include "WindowProperties.h"

struct GLFWwindow;
struct GLFWmonitor;

namespace Copper
{
	class Window
	{
	private:
		unsigned int m_PosX, m_PosY;
		unsigned int m_Width, m_Height;
		std::string m_Title;

		bool m_Fullscreen;
		bool m_Resizable;

		GLFWwindow* m_Window;
		GLFWmonitor* m_Monitor;
	public:
		Window();
		Window(const WindowProperties& prop);
		~Window();

		unsigned int GetPosX() const;
		unsigned int GetPosY() const;
		void SetPosX(unsigned int x);
		void SetPosY(unsigned int y);
		void SetPosition(unsigned int x, unsigned int y);

		unsigned int GetWidth() const;
		unsigned int GetHeight() const;
		void SetWidth(unsigned int width);
		void SetHeight(unsigned int height);
		void SetSize(unsigned int width, unsigned int height);

		std::string_view GetTitle() const;
		void SetTitle(std::string_view title);

		void SetFullscreen(bool flag);
		void SetResizable(bool flag);

		void Close();
		bool IsOpen() const;
		void UpdateFrame() const;
		void Cleanup();
	private:
		static void GLFWFrameBufferSizeCallback(GLFWwindow* window, int width, int height);
	};
}