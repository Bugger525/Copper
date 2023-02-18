#pragma once

#include "Window.h"
#include "../core/AssetManager.h"
#include "../Graphics/Image.h"

namespace cu::System
{
	class Game
	{
	private:
		Window m_Window;

		core::AssetManager m_ImageManager;
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