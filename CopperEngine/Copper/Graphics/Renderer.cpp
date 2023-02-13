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
	void Renderer::Draw(Texture& texture, Vector2f position, Vector2f size, Angle rotate)
	{
		m_Shader->Use();
		Transform model;

		// Move
		model.Translate(position);

		// Rotate
		model.Translate(cu::Vector2f(0.5f * size.X, 0.5f * size.Y)); // Move to center of quad
		// model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
		model.Translate(cu::Vector2f(-0.5f * size.X, -0.5f * size.Y)); // Move back to origin

		// Scale
		model.Scale(size);

		m_Shader->SetUniform("model", model);

		glActiveTexture(GL_TEXTURE0);
		texture.Use();

		glBindVertexArray(m_QuadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
	void Renderer::Draw(Texture& texture, const Rectf& body, Angle rotate)
	{
		m_Shader->Use();
		Transform model;

		// Move
		model.Translate(body.Position);

		// Rotate
		model.Translate(cu::Vector2f(0.5f * body.Size.X, 0.5f * body.Size.Y)); // Move to center of quad
		// model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
		model.Translate(cu::Vector2f(-0.5f * body.Size.X, -0.5f * body.Size.Y)); // Move back to origin

		// Scale
		model.Scale(body.Size);

		m_Shader->SetUniform("model", model);

		glActiveTexture(GL_TEXTURE0);
		texture.Use();

		glBindVertexArray(m_QuadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
}