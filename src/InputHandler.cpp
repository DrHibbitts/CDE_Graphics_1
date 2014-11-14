/*
 * InputHandler.cpp
 *
 *  Created on: 14 Nov 2014
 *      Author: gdp24
 */

#include "InputHandler.h"

InputHandler::InputHandler(Window* window) {
	this->window = window;
	settingGoal = false;
}

InputHandler::~InputHandler() {
}

void InputHandler::mouseCallback(GLFWwindow* glfwWindow, int button,
		int actions, int mods) const {
	//Mouse callback example
	switch (button) {
	case GLFW_MOUSE_BUTTON_1: {
		if (!settingGoal) {
			handleWindowRotation();
		} else {
			handleGoalRotation();
		}
		break;
	}
	case GLFW_MOUSE_BUTTON_2: {
		if (!settingGoal) {
			handleWindowTranslation();
		} else {
			handleGoalTranslation();
		}
		break;
	}
	case GLFW_MOUSE_BUTTON_3: {
		handleWindowZoom();
		break;
	}
	default:
		break;
	}
}

void InputHandler::keyCallback(GLFWwindow* glfwWindow, int button, int actions,
		int mods) const {
}

void InputHandler::handleWindowRotation() const {
}

void InputHandler::handleWindowTranslation() const {
}

void InputHandler::handleWindowZoom() const {
}

void InputHandler::handleGoalRotation() const {
}

void InputHandler::handleGoalTranslation() const {
}
