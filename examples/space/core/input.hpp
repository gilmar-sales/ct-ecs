#pragma once

#include <glm/glm.hpp>

#include "keycodes.hpp"
#include "mousecodes.hpp"

static KeyCode keys[GLFW_KEY_LAST];

class Input
{
public:
	static bool GetKeyDown(KeyCode key);
	static bool GetKeyUp(KeyCode key);
	static bool IsKeyPressed(KeyCode key);

	static bool IsMouseButtonPressed(MouseCode button);
	static glm::vec2 GetMousePosition();
	static float GetMouseX();
	static float GetMouseY();
};
