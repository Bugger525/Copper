#pragma once

#include "Window.h"
#include "../Core/AssetManager.h"
#include "../Graphics/Image.h"

namespace cu::sys
{
	class Game
	{
	private:
		Window m_Window;
	protected:
		virtual const WindowProperties& SetWindowProperties() = 0;
		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void Cleanup() = 0;
	public:
		void Run();
	};
}