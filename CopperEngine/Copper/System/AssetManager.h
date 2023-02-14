#pragma once

#include "../Graphics/Shader.h"
#include "../Graphics/Texture.h"
#include <string>
#include <map>
#include <memory>

namespace cu
{
	using ShaderPtr = std::shared_ptr<Shader>;
	using TexturePtr = std::shared_ptr<Texture>;
	class AssetManager
	{
	public:
		AssetManager() = delete;

		static ShaderPtr LoadShader(std::string_view name, std::string_view shaderPath, ShaderType type);
		static ShaderPtr LoadShaders(std::string_view name, std::string_view vertexShaderPath, std::string_view fragmentShaderPath);
		static ShaderPtr GetShader(std::string_view name);

		static TexturePtr LoadTexture(std::string_view name, std::string_view filePath);
		static TexturePtr GetTexture(std::string_view name);
	};
}