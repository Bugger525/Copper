#include "AssetManager.h"
#include "Debug.h"

#include <fstream>
#include <sstream>
#include <iostream>

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
	AssetManager::~AssetManager()
	{
		//for (auto it = m_Shaders.begin(); it != m_Shaders.end(); ++it)
		//	delete it->second;
		//for (auto it = m_Textures.begin(); it != m_Textures.end(); ++it)
		//	delete it->second;
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
		path += m_Directory;
		path += "/";
		path += shaderPath;

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
		vPath += m_Directory;
		vPath += "/";
		vPath += vertexShaderPath;

		std::string fPath;
		fPath += m_Directory;
		fPath += "/";
		fPath += fragmentShaderPath;

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

	std::shared_ptr<Shader> AssetManager::GetShader(std::string_view name)
	{
		return m_Shaders.at(std::string(name));
	}

	bool AssetManager::LoadTexture(std::string_view filePath)
	{
		return false;
	}

	std::shared_ptr<Texture> AssetManager::GetTexture(std::string_view name)
	{
		return m_Textures.at(std::string(name));
	}
}