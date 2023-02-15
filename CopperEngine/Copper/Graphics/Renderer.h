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

		void Draw(std::shared_ptr<Texture> texture, const Vector2f& position, const Vector2f& size = Vector2f::Zero, const Angle& rotate = Angle(0.f));
		void Draw(const Rectf& rect, const Color& color = Color::White, const Angle& rotate = Angle(0.f));
	};
}