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
	private:
		std::string m_Directory;
		bool m_EmptyDir;
		std::map<std::string, ShaderPtr> m_Shaders;
		std::map<std::string, TexturePtr> m_Textures;
	public:
		AssetManager();
		AssetManager(std::string_view directory);

		void SetDirectory(std::string_view directory);

		bool LoadShader(std::string_view name, std::string_view shaderPath, ShaderType type);
		bool LoadShaders(std::string_view name, std::string_view vertexShaderPath, std::string_view fragmentShaderPath);
		ShaderPtr GetShader(std::string_view name);

		bool LoadTexture(std::string_view name, std::string_view filePath);
		TexturePtr GetTexture(std::string_view name);
	};
}