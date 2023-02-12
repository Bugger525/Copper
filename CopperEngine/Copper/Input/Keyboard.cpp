#include "Keyboard.h"
#include <map>
#include "GLFW/glfw3.h"

using KeyState = std::pair<bool, bool>;

static std::map<int, KeyState> KeyMap{};
static bool Initialized = false;

static void GLFWKeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mode)
{
	if (action == GLFW_REPEAT)
	{
		KeyMap[key].first = true;
		KeyMap[key].second = true;
		return;
	}

	KeyMap[key].second = KeyMap[key].first;
	KeyMap[key].first = action != GLFW_RELEASE;
}

namespace cu
{
	void Keyboard::Initialize(GLFWwindow* window)
	{
		if (Initialized) return;

		glfwSetKeyCallback(window, GLFWKeyCallback);

		Initialized = true;
	}
	bool Keyboard::IsKeyHeld(Keys key)
	{
		int code = static_cast<int>(key);

		auto it = KeyMap.find(code);
		if (it != KeyMap.end())
		{
			auto& state = KeyMap.at(code);
			return state.first && state.second;
		}
		else
			return false;
	}
	bool Keyboard::IsKeyPressed(Keys key)
	{
		int code = static_cast<int>(key);

		auto it = KeyMap.find(code);
		if (it != KeyMap.end())
		{
			auto& state = KeyMap.at(code);
			return state.first && !state.second;
		}
		else
			return false;
	}
	bool Keyboard::IsKeyReleased(Keys key)
	{
		int code = static_cast<int>(key);

		auto it = KeyMap.find(code);
		if (it != KeyMap.end())
		{
			auto& state = KeyMap.at(code);
			return !state.first && state.second;
		}
		else
			return false;
	}
}