#include "Game.h"
#include "Debug.h"
#include "Window.h"
#include <GL/gl3w.h>

namespace Copper
{
	void Game::Run()
	{
		Window = Copper::Window(SetWindowProperties());

		Initialize();

		while (Window.IsOpen())
		{
			Update();

			glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			Render();

			Window.UpdateFrame();
		}
		Cleanup();
	}
}