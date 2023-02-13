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
		std::string m_Directory;
		bool m_EmptyDir;
		std::map<std::string, std::shared_ptr<Shader>> m_Shaders;
		std::map<std::string, std::shared_ptr<Texture>> m_Textures;
	public:
		AssetManager();
		AssetManager(std::string_view directory);
		~AssetManager();

		void SetDirectory(std::string_view directory);

		bool LoadShader(std::string_view name, std::string_view shaderPath, ShaderType type);
		bool LoadShaders(std::string_view name, std::string_view vertexShaderPath, std::string_view fragmentShaderPath);
		std::shared_ptr<Shader> GetShader(std::string_view name);

		bool LoadTexture(std::string_view filePath);
		std::shared_ptr<Texture> GetTexture(std::string_view name);
	};
}