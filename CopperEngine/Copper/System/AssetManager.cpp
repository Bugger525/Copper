#include "AssetManager.h"
#include "Debug.h"

#include <fstream>
#include <sstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace cu
{
	static std::map<std::string, ShaderPtr> m_Shaders;
	static std::map<std::string, TexturePtr> m_Textures;

	ShaderPtr AssetManager::LoadShader(std::string_view name, std::string_view shaderPath, ShaderType type)
	{
		std::string shaderCode;
		try
		{
			std::ifstream shaderFile(shaderPath.data());

			std::stringstream stream;
			stream << shaderFile.rdbuf();

			shaderFile.close();

			shaderCode = stream.str();
		}
		catch (std::ifstream::failure e)
		{
			Debug::Error("Failed to read shader code.");
			return nullptr;
		}

		return m_Shaders[std::string(name)] = std::make_shared<Shader>(shaderCode, type);
	}
	ShaderPtr AssetManager::LoadShaders(std::string_view name, std::string_view vertexShaderPath, std::string_view fragmentShaderPath)
	{
		std::string vertexShaderCode;
		std::string fragmentShaderCode;

		try
		{
			std::ifstream vertexShaderFile(vertexShaderPath.data());
			std::ifstream fragmentShaderFile(fragmentShaderPath.data());

			std::stringstream vStream;
			std::stringstream fStream;

			vStream << vertexShaderFile.rdbuf();
			fStream << fragmentShaderFile.rdbuf();

			vertexShaderFile.close();
			fragmentShaderFile.close();

			vertexShaderCode = vStream.str();
			fragmentShaderCode = fStream.str();
		}
		catch (std::ifstream::failure e)
		{
			Debug::Error("Failed to read shader codes.");
			return nullptr;
		}

		return m_Shaders[std::string(name)] = std::make_shared<Shader>(vertexShaderCode, fragmentShaderCode);
	}
	ShaderPtr AssetManager::GetShader(std::string_view name)
	{
		return m_Shaders.at(std::string(name));
	}
	TexturePtr AssetManager::LoadTexture(std::string_view name, std::string_view filePath)
	{
		int width, height, nrChannels;

		auto data = stbi_load(filePath.data(), &width, &height, &nrChannels, STBI_rgb_alpha);

		if (!data)
		{
			CU_DBG_ERROR("Failed to load texture: {}", stbi_failure_reason());
			return nullptr;
		}

		m_Textures[std::string(name)] = std::make_shared<Texture>(width, height, data);

		stbi_image_free(data);

		return m_Textures[std::string(name)];
	}
	TexturePtr AssetManager::GetTexture(std::string_view name)
	{
		return m_Textures.at(std::string(name));
	}
}