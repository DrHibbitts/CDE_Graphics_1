/*
 * InputHandler.cpp
 *
 *  Created on: 14 Nov 2014
 *      Author: gdp24
 */

#include "InputHandler.h"

InputHandler::InputHandler() {
	mouse_x = 0;
	mouse_y = 0;
	prev_mouse_x = 0;
	prev_mouse_y = 0;
	renderer = NULL;
	settingGoal = false;
}

InputHandler::~InputHandler() {
	renderer = NULL;
}

void InputHandler::mouseCallback(double mouse_x, double mouse_y, int button,
		int actions, int mods) {
	//Mouse callback example
	if (actions != GLFW_PRESS) {
		return;
	}

	switch (button) {
	case GLFW_MOUSE_BUTTON_1: {
		if (!settingGoal) {
			handleCameraRotation();
		} else {
			handleGoalRotation();
		}
		break;
	}
	case GLFW_MOUSE_BUTTON_2: {
		if (!settingGoal) {
			handleCameraTranslation();
		} else {
			handleGoalTranslation();
		}
		break;
	}
	case GLFW_MOUSE_BUTTON_3: {
		handleRenameZoom();
		break;
	}
	default:
		break;
	}

	prev_mouse_x = mouse_x;
	prev_mouse_y = mouse_y;
}

void InputHandler::keyCallback(int key, int scancode, int action, int mods) {
}

void InputHandler::handleCameraRotation() const {
}

void InputHandler::handleCameraTranslation() const {
}

void InputHandler::handleRenameZoom() const {
}

void InputHandler::handleGoalRotation() const {
}

void InputHandler::handleGoalTranslation() const {
}

void InputHandler::setRenderer(Renderer* renderer) {
	this->renderer = renderer;
}
