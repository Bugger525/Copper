#include "AssetManager.h"
#include "Debug.h"

#include <fstream>
#include <sstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace cu
{
	AssetManager::AssetManager() : m_EmptyDir(true)
	{
	}
	AssetManager::AssetManager(std::string_view directory) : m_EmptyDir(true)
	{
		if (directory.length() <= 0)
			return;
		m_Directory = directory;
		m_EmptyDir = false;
	}
	void AssetManager::SetDirectory(std::string_view directory)
	{
		m_Directory = directory;
		if (m_EmptyDir)
			m_EmptyDir = false;
	}

	bool AssetManager::LoadShader(std::string_view name, std::string_view shaderPath, ShaderType type)
	{
		std::string shaderCode;

		std::string path;
		if (!m_EmptyDir)
		{
			path += m_Directory;
			path += "/";
			path += shaderPath;
		}
		else
		{
			path = shaderPath;
		}

		try
		{
			std::ifstream shaderFile(path);

			std::stringstream stream;
			stream << shaderFile.rdbuf();

			shaderFile.close();

			shaderCode = stream.str();
		}
		catch (std::ifstream::failure e)
		{
			Debug::Error("Failed to read shader code.");
			return false;
		}

		m_Shaders[std::string(name)] = std::make_shared<Shader>(shaderCode, type);

		return true;
	}

	bool AssetManager::LoadShaders(std::string_view name, std::string_view vertexShaderPath, std::string_view fragmentShaderPath)
	{
		std::string vertexShaderCode;
		std::string fragmentShaderCode;

		std::string vPath;
		std::string fPath;

		if (!m_EmptyDir)
		{
			vPath += m_Directory;
			vPath += "/";
			vPath += vertexShaderPath;

			fPath += m_Directory;
			fPath += "/";
			fPath += fragmentShaderPath;
		}
		else
		{
			vPath = vertexShaderPath;
			fPath = fragmentShaderPath;
		}

		try
		{
			std::ifstream vertexShaderFile(vPath);
			std::ifstream fragmentShaderFile(fPath);

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
			return false;
		}
		m_Shaders[std::string(name)] = std::make_shared<Shader>(vertexShaderCode, fragmentShaderCode);
		return true;
	}

	ShaderPtr AssetManager::GetShader(std::string_view name)
	{
		return m_Shaders.at(std::string(name));
	}

	bool AssetManager::LoadTexture(std::string_view name, std::string_view filePath)
	{
		int width, height, nrChannels;

		std::string path;

		if (!m_EmptyDir)
		{
			path += m_Directory;
			path += "/";
			path += filePath;
		}
		else
		{
			path = filePath;
		}

		auto data = stbi_load(path.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);

		if (!data)
		{
			CU_DBG_ERROR("Failed to load texture: {}", stbi_failure_reason());
			return false;
		}
		m_Textures[std::string(name)] = std::make_shared<Texture>(width, height, data);
		stbi_image_free(data);
		return true;
	}

	TexturePtr AssetManager::GetTexture(std::string_view name)
	{
		return m_Textures.at(std::string(name));
	}
}