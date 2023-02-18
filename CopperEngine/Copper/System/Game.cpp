#include "Game.h"
#include "Debug.h"
#include "Window.h"
#include <GL/gl3w.h>

namespace cu::System
{
	void Game::Run()
	{
		m_Window = Window(SetWindowProperties());

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