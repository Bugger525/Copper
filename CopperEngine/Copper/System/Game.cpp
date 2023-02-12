#include "Game.h"
#include "Debug.h"
#include "Window.h"
#include <GL/gl3w.h>

namespace cu
{
	void Game::SetWindow(Window& window)
	{
		m_Window = window;
	}
	void Game::Run()
	{
		Initialize();

		while (m_Window.IsOpen())
		{
			Update();

			glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			Render();

			m_Window.UpdateFrame();
		}
		Cleanup();
	}
}