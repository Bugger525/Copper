#pragma once

#include "Window.h"
#include "../Core/AssetManager.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Texture.h"

namespace Copper
{
	class Game
	{
	protected:
		Window Window;

		AssetManager<Shader> ShaderManager;
		AssetManager<Texture> TextureManager;
		AssetManager<Image> ImageManager;

		virtual WindowProperties SetWindowProperties() = 0;
		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void Cleanup() = 0;
	public:
		void Run();
	};
}