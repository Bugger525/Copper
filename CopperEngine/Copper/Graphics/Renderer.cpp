#include "Renderer.h"
#include "Transform.h"
#include "../System/Debug.h"
#include <GL/gl3w.h>

namespace cu
{
	Renderer::Renderer() : m_QuadVAO(NULL)
	{
	}
	Renderer::Renderer(std::shared_ptr<Shader> shader) : m_Shader(shader)
	{
		unsigned int VBO;
		float vertices[] = {
			// pos      // tex
			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,

			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f
		};

		glGenVertexArrays(1, &m_QuadVAO);
		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindVertexArray(m_QuadVAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	void Renderer::Draw(std::shared_ptr<Texture> texture, const Vector2f& position, const Vector2f& scale, const Angle& rotate)
	{
		m_Shader->Use();
		m_Shader->SetUniform("tex", true);
		Transform model;

		// Move
		model.Translate(position);

		// Rotate
		if (rotate.ToDegrees() != 0.f)
		{
			model.Translate(cu::Vector2f(0.5f * scale.X, 0.5f * scale.Y)); // Move to center of quad
			// model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
			model.Translate(cu::Vector2f(-0.5f * scale.X, -0.5f * scale.Y)); // Move back to origin
		}

		// Scale
		if (scale == Vector2f::Zero)
			model.Scale(Vector2f(texture->GetWidth(), texture->GetHeight()));
		else
			model.Scale(scale);

		m_Shader->SetUniform("model", model);

		glActiveTexture(GL_TEXTURE0);
		texture->Use();

		glBindVertexArray(m_QuadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
	void Renderer::Draw(const Rectf& rect, const Color& color, const Angle& rotate)
	{
		m_Shader->Use();
		m_Shader->SetUniform("tex", false);
		Transform model;

		// Move
		model.Translate(rect.Position);

		// Rotate
		model.Translate(cu::Vector2f(0.5f * rect.Size.X, 0.5f * rect.Size.Y)); // Move to center of quad
		// model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
		model.Translate(cu::Vector2f(-0.5f * rect.Size.X, -0.5f * rect.Size.Y)); // Move back to origin

		// Scale
		model.Scale(rect.Size);

		m_Shader->SetUniform("model", model);
		m_Shader->SetUniform("spriteColor", color);

		glBindVertexArray(m_QuadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
}