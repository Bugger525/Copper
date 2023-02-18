#include "Copper/Copper.hpp"
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <GL/gl3w.h>

class DemoGame : public Copper::Game
{
protected:
	Copper::WindowProperties SetWindowProperties() override
	{
		Copper::WindowProperties prop;
		prop.Size = { 800, 600 };
		prop.FullScreen = false;
		prop.Resizable = true;

		return prop;
	}
	void Initialize() override
	{
		Copper::AssetStream stream("Shaders");
		ShaderManager.Add("mainShader", std::make_shared<Copper::Shader>(stream.ReadText("shader.vert"), stream.ReadText("shader.frag")));

		glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(Window.GetWidth()),
			static_cast<float>(Window.GetHeight()), 0.0f, -1.0f, 1.0f);

		auto mainShader = ShaderManager.Load("mainShader");
		mainShader->Use().SetUniform("image", 0);
		glUniformMatrix4fv(glGetUniformLocation(mainShader->GetData(), "projection"), 1, false, &projection[0][0]);

		m_Renderer = cu::Renderer(m_Shader);
	}
	void Update() override
	{
		if (Copper::Keyboard::IsKeyPressed(Copper::Key::Escape))
			Window.Close();
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