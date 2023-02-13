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

	cu::AssetManager m_ShadersManager;
	cu::AssetManager m_ImagesManager;
protected:
	void Initialize() override
	{
		m_Window.Create(800, 600, "CopperEngine Demo game");
		this->SetWindow(m_Window);

		m_ShadersManager = cu::AssetManager("Shaders");
		m_ShadersManager.LoadShaders("mainShader", "shader.vert", "shader.frag");

		m_Shader = m_ShadersManager.GetShader("mainShader");

		glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_Window.GetWidth()),
			static_cast<float>(m_Window.GetHeight()), 0.0f, -1.0f, 1.0f);

		m_Shader->Use();
		m_Shader->SetUniform("image", 0);
		glUniformMatrix4fv(glGetUniformLocation(m_Shader->GetData(), "projection"), 1, false, &projection[0][0]);

		m_Renderer = cu::Renderer(m_Shader);

		m_ImagesManager = cu::AssetManager("Assets");
		m_ImagesManager.LoadTexture("platform", "Platform.png");

		m_Texture = m_ImagesManager.GetTexture("platform");
	}
	void Update() override
	{
		if (cu::Keyboard::IsKeyPressed(cu::Keys::Escape))
			m_Window.Close();
	}
	void Render() override
	{
		m_Renderer.Draw(m_Texture, cu::Rectf(100.f, 100.f, 200.f, 200.f), cu::Angle::Degrees(45.f));
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