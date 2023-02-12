#pragma once

#include "Window.h"

namespace cu
{
	class Window;

	class Game
	{
	private:
		Window m_Window;
	protected:
		void SetWindow(Window& window);

		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void Cleanup() = 0;
	public:
		void Run();
	};
}