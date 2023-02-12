#pragma once

#include <string>
#include "Transform.h"
#include "Color.h"

namespace cu
{
	enum class ShaderType
	{
		Vertex,
		Fragment
	};
	class Shader
	{
	private:
		unsigned int m_Data;
	public:
		Shader();
		~Shader();

		bool LoadFromFile(std::string_view shaderPath, ShaderType type);
		bool LoadFromFile(std::string_view vertexShaderPath, std::string_view fragmentShaderPath);
		bool LoadFromCode(std::string_view shaderCode, ShaderType type);
		unsigned int GetData() const;
		void Use();

		void SetUniform(std::string_view name, bool value) const;
		void SetUniform(std::string_view name, int value) const;
		void SetUniform(std::string_view name, float value) const;
		void SetUniform(std::string_view name, const Matrix<4, 4>& mat) const;
		void SetUniform(std::string_view name, const Transform& transform) const;
		void SetUniform(std::string_view name, Color color) const;

		void Cleanup();
	};
}