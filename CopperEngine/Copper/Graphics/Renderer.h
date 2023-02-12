#pragma once

#include "Shader.h"
#include "Texture.h"
#include "../System/Vector2.h"
#include "../System/Rect.h"
#include "../System/Angle.h"

namespace cu
{
	class Renderer
	{
	private:
		Shader m_Shader;
		unsigned int m_QuadVAO;
	public:
		Renderer();
		Renderer(Shader& shader);

		void Draw(Texture& texture, Vector2f position, Vector2f size, Angle rotate);
		void Draw(Texture& texture, const Rectf& body, Angle rotate);
	};
}