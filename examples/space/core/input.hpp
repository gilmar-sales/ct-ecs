#pragma once

#include <glm/glm.hpp>

#include "keycodes.hpp"
#include "mousecodes.hpp"

class Input {
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
};
