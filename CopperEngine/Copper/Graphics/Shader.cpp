#include "Shader.h"
#include "../System/Debug.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/gl3w.h>

namespace cu
{
	Shader::Shader() : m_Data(NULL)
	{
	}
	Shader::~Shader()
	{
		Cleanup();
	}
	bool Shader::LoadFromFile(std::string_view shaderPath, ShaderType type)
	{
		std::ifstream shaderFile;
		std::string shaderCode;

		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			shaderFile.open(shaderPath.data());

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

		auto cShaderCode = shaderCode.c_str();

		int success = 0;
		char infoLog[512]{};

		unsigned int shader = NULL;

		if (type == ShaderType::Vertex)
		{
			shader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(shader, 1, &cShaderCode, nullptr);
			glCompileShader(shader);

			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 512, NULL, infoLog);
				CU_DBG_CRITICAL("Failed to compile vertex shader : {}", infoLog);
				return false;
			}
		}
		else
		{
			shader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(shader, 1, &cShaderCode, nullptr);
			glCompileShader(shader);

			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 512, NULL, infoLog);
				CU_DBG_CRITICAL("Failed to compile fragment shader : {}", infoLog);
				return false;
			}
		}

		m_Data = glCreateProgram();
		glAttachShader(m_Data, shader);
		glLinkProgram(m_Data);
		glGetProgramiv(m_Data, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_Data, 512, NULL, infoLog);
			CU_DBG_CRITICAL("Failed to link program : {}", infoLog);
			return false;
		}

		glDeleteShader(shader);

		return true;
	}
	bool Shader::LoadFromFile(std::string_view vertexShaderPath, std::string_view fragmentShaderPath)
	{
		std::ifstream vertexShaderFile;
		std::ifstream fragmentShaderFile;

		std::string vertexShaderCode;
		std::string fragmentShaderCode;

		vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			vertexShaderFile.open(vertexShaderPath.data());
			fragmentShaderFile.open(fragmentShaderPath.data());

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

		auto cVertexShaderCode = vertexShaderCode.c_str();
		auto cFragmentShaderCode = fragmentShaderCode.c_str();

		int success = 0;
		char infoLog[512]{};

		unsigned int vertexShader = NULL;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &cVertexShaderCode, nullptr);
		glCompileShader(vertexShader);

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			CU_DBG_CRITICAL("Failed to compile vertex shader : {}", infoLog);
			return false;
		}

		unsigned int fragmentShader = NULL;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &cFragmentShaderCode, nullptr);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			CU_DBG_CRITICAL("Failed to compile fragment shader : {}", infoLog);
			return false;
		}

		m_Data = glCreateProgram();

		glAttachShader(m_Data, vertexShader);
		glAttachShader(m_Data, fragmentShader);
		glLinkProgram(m_Data);

		glGetProgramiv(m_Data, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_Data, 512, NULL, infoLog);
			CU_DBG_CRITICAL("Failed to link program : {}", infoLog);
			return false;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return true;
	}
	bool Shader::LoadFromCode(std::string_view shaderCode, ShaderType type)
	{
		auto cShaderCode = shaderCode.data();

		int success = 0;
		char infoLog[512]{};

		unsigned int shader = NULL;

		if (type == ShaderType::Vertex)
		{
			shader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(shader, 1, &cShaderCode, nullptr);
			glCompileShader(shader);

			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 512, NULL, infoLog);
				CU_DBG_CRITICAL("Failed to compile vertex shader : {}", infoLog);
				return false;
			}
		}
		else
		{
			shader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(shader, 1, &cShaderCode, nullptr);
			glCompileShader(shader);

			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 512, NULL, infoLog);
				CU_DBG_CRITICAL("Failed to compile fragment shader : {}", infoLog);
				return false;
			}
		}

		m_Data = glCreateProgram();
		glAttachShader(m_Data, shader);
		glLinkProgram(m_Data);
		glGetProgramiv(m_Data, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_Data, 512, NULL, infoLog);
			CU_DBG_CRITICAL("Failed to link program : {}", infoLog);
			return false;
		}

		glDeleteShader(shader);

		return true;
	}
	unsigned int Shader::GetData() const
	{
		return m_Data;
	}
	void Shader::Use()
	{
		glUseProgram(m_Data);
	}
	void Shader::SetUniform(std::string_view name, bool value) const
	{
		glUniform1i(glGetUniformLocation(m_Data, name.data()), static_cast<int>(value));
	}
	void Shader::SetUniform(std::string_view name, int value) const
	{
		glUniform1i(glGetUniformLocation(m_Data, name.data()), value);
	}
	void Shader::SetUniform(std::string_view name, float value) const
	{
		glUniform1f(glGetUniformLocation(m_Data, name.data()), value);
	}
	void Shader::SetUniform(std::string_view name, const Matrix<4, 4>& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_Data, name.data()), 1, false, mat.Array);
	}
	void Shader::SetUniform(std::string_view name, const Transform& transform) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_Data, name.data()), 1, false, transform.GetData());
	}
	void Shader::SetUniform(std::string_view name, Color color) const
	{
		glUniform3f(glGetUniformLocation(m_Data, name.data()), color.R, color.G, color.B);
	}
	void Shader::Cleanup()
	{
		glDeleteProgram(m_Data);
	}
}