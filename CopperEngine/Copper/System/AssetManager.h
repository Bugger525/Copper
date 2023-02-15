#pragma once

#include "../Graphics/Shader.h"
#include "../Graphics/Texture.h"
#include <string>
#include <map>
#include <memory>

namespace cu
{
	class AssetManager
	{
	private:
		static std::map<std::string, std::unique_ptr<Shader>> m_Shaders;
		static std::map<std::string, std::unique_ptr<Texture>> m_Textures;
	public:
		AssetManager() = delete;

		static Shader& LoadShader(std::string_view name, std::string_view shaderPath, ShaderType type);
		static Shader& LoadShaders(std::string_view name, std::string_view vertexShaderPath, std::string_view fragmentShaderPath);
		static Shader& GetShader(std::string_view name);

		static Texture& LoadTexture(std::string_view name, std::string_view filePath);
		static Texture& GetTexture(std::string_view name);
	};
}