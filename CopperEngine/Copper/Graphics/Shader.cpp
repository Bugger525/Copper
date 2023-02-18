#include "Shader.h"
#include "../System/Debug.h"
#include "../core/AssetManager.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/gl3w.h>

namespace cu::gfx
{
	Shader::Shader() : m_Data(NULL)
	{
	}
	Shader::Shader(std::string_view shaderCode, ShaderType type) : m_Data(NULL)
	{
		unsigned int shader = CompileShader(shaderCode, type);
		int success = 0;
		char infoLog[512]{};

		if (m_Data == NULL)
			m_Data = glCreateProgram();
		glAttachShader(m_Data, shader);
		glLinkProgram(m_Data);
		glGetProgramiv(m_Data, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_Data, 512, NULL, infoLog);
			CU_DBG_CRITICAL("Failed to link program : {}", infoLog);
			return;
		}

		glDeleteShader(shader);
	}
	Shader::Shader(std::string_view vertexShaderCode, std::string_view fragmentShaderCode) : m_Data(NULL)
	{
		auto vertexShader = CompileShader(vertexShaderCode, ShaderType::Vertex);
		auto fragmentShader = CompileShader(fragmentShaderCode, ShaderType::Fragment);
		int success = 0;
		char infoLog[512]{};

		m_Data = glCreateProgram();

		glAttachShader(m_Data, vertexShader);
		glAttachShader(m_Data, fragmentShader);
		glLinkProgram(m_Data);

		glGetProgramiv(m_Data, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_Data, 512, NULL, infoLog);
			CU_DBG_CRITICAL("Failed to link program : {}", infoLog);
			return;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	Shader::~Shader()
	{
		Cleanup();
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
		auto a = glIsProgram(m_Data);
		glUniform1i(glGetUniformLocation(m_Data, name.data()), value);
	}
	void Shader::SetUniform(std::string_view name, float value) const
	{
		glUniform1f(glGetUniformLocation(m_Data, name.data()), value);
	}
	void Shader::SetUniform(std::string_view name, const Matrix<4, 4>& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_Data, name.data()), 1, false, mat.Array.data());
	}
	void Shader::SetUniform(std::string_view name, const Transform& transform) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_Data, name.data()), 1, false, transform.GetData().data());
	}
	void Shader::SetUniform(std::string_view name, const Color& color) const
	{
		glUniform3f(glGetUniformLocation(m_Data, name.data()), color.R, color.G, color.B);
	}
	void Shader::Cleanup()
	{
		if (m_Data)
			glDeleteProgram(m_Data);
	}
	unsigned int Shader::CompileShader(std::string_view shaderCode, ShaderType type)
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
				return NULL;
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
				return NULL;
			}
		}
		return shader;
	}
	bool Shader::IsNull() const
	{
		return !glIsProgram(m_Data);
	}
}