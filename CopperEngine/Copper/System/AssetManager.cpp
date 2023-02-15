#include "AssetManager.h"
#include "Debug.h"

#include <fstream>
#include <sstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace cu
{
	std::map<std::string, std::unique_ptr<Shader>> AssetManager::m_Shaders;
	std::map<std::string, std::unique_ptr<Texture>> AssetManager::m_Textures;

	Shader& AssetManager::LoadShader(std::string_view name, std::string_view shaderPath, ShaderType type)
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
			CU_DBG_ERROR("Failed to read shader code: {}", e.what());
			return nullptr;
		}

		m_Shaders[std::string(name)] = std::make_unique<Shader>(shaderCode, type);

		return *m_Shaders[std::string(name)];
	}
	Shader& AssetManager::LoadShaders(std::string_view name, std::string_view vertexShaderPath, std::string_view fragmentShaderPath)
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

		m_Shaders[std::string(name)] = std::make_unique<Shader>(vertexShaderCode, fragmentShaderCode);

		return *m_Shaders[std::string(name)];
	}
	Shader& AssetManager::GetShader(std::string_view name)
	{
		return *m_Shaders.at(std::string(name));
	}
	Texture& AssetManager::LoadTexture(std::string_view name, std::string_view filePath)
	{
		int width, height, nrChannels;

		unsigned char* data = stbi_load(filePath.data(), &width, &height, &nrChannels, STBI_rgb_alpha);

		if (!data)
		{
			CU_DBG_ERROR("Failed to load texture: {}", stbi_failure_reason());
			return nullptr;
		}

		m_Textures[std::string(name)] = std::make_unique<Texture>(width, height, std::span<unsigned char>{data, static_cast<size_t>(width* height* STBI_rgb_alpha)});

		stbi_image_free(data);

		return *m_Textures[std::string(name)];
	}
	Texture& AssetManager::GetTexture(std::string_view name)
	{
		return *m_Textures.at(std::string(name));
	}
}