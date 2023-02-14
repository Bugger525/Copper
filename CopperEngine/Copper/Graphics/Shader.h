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
		Shader(std::string_view shaderCode, ShaderType type);
		Shader(std::string_view vertexShaderCode, std::string_view fragmentShaderCode);
		~Shader();

		void Init(std::string_view vertexShaderCode, std::string_view fragmentShaderCode);

		unsigned int GetData() const;
		void Use();

		void SetUniform(std::string_view name, bool value) const;
		void SetUniform(std::string_view name, int value) const;
		void SetUniform(std::string_view name, float value) const;
		void SetUniform(std::string_view name, const Matrix<4, 4>& mat) const;
		void SetUniform(std::string_view name, const Transform& transform) const;
		void SetUniform(std::string_view name, const Color& color) const;

		void Cleanup();
	private:
	};
}