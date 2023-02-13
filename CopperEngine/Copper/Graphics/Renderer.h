#pragma once

#include "Shader.h"
#include "Texture.h"
#include "../System/Vector2.h"
#include "../System/Rect.h"
#include "../System/Angle.h"
#include <memory>

namespace cu
{
	class Renderer
	{
	private:
		std::shared_ptr<Shader> m_Shader;
		unsigned int m_QuadVAO;
	public:
		Renderer();
		Renderer(std::shared_ptr<Shader> shader);

		void Draw(std::shared_ptr<Texture> texture, Vector2f position, Vector2f size, Angle rotate);
		void Draw(std::shared_ptr<Texture> texture, const Rectf& body, Angle rotate);
	};
}