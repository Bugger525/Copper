#include "Copper/Copper.hpp"
#include "Copper/System/AssetManager.h"
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <GL/gl3w.h>

class DemoGame : public cu::Game
{
private:
	cu::Window m_Window;
	cu::ShaderPtr m_Shader;
	cu::TexturePtr m_Texture;
	cu::Renderer m_Renderer;
protected:
	void Initialize() override
	{
		m_Window.Create(800, 600, "CopperEngine Demo game");
		this->SetWindow(m_Window);

		m_Shader = cu::AssetManager::LoadShaders("mainShader", "Shaders/shader.vert", "Shaders/shader.frag");
		if (m_Shader == nullptr)
		{
			cu::Debug::Error("Shader fucked!");
			m_Window.Close();
		}

		glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_Window.GetWidth()),
			static_cast<float>(m_Window.GetHeight()), 0.0f, -1.0f, 1.0f);

		m_Shader->Use();
		m_Shader->SetUniform("image", 0);
		glUniformMatrix4fv(glGetUniformLocation(m_Shader->GetData(), "projection"), 1, false, &projection[0][0]);

		m_Renderer = cu::Renderer(m_Shader);

		m_Texture = cu::AssetManager::LoadTexture("platform", "Assets/Platform.png");
		if (m_Texture == nullptr)
		{
			cu::Debug::Error("Texture fucked!");
			m_Window.Close();
		}
	}
	void Update() override
	{
		if (cu::Keyboard::IsKeyPressed(cu::Keys::Escape))
			m_Window.Close();
	}
	void Render() override
	{
		m_Renderer.Draw(m_Texture, cu::Vector2f(500.f, 200.f));
		m_Renderer.Draw(cu::Rectf(500.f, 400.f, 100.f, 100.f), cu::Color::Red);
	}
	void Cleanup() override
	{
	}
};

int main(int argc, char* argv[])
{
	DemoGame().Run();
	return 0;
}