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
	camTransSpeed = 0.01;
	camRotSpeed = 0.02;
	inputState = idle;
}

InputHandler::~InputHandler() {
	renderer = NULL;
}

void InputHandler::mouseButtonCallback(int button, int actions, int mods) {
	//Mouse callback example
	switch (actions) {
	case GLFW_PRESS: {

		switch (button) {
		case GLFW_MOUSE_BUTTON_1:
			inputState = translate;
			break;
		case GLFW_MOUSE_BUTTON_2:
			inputState = rotate;
			break;
		case GLFW_MOUSE_BUTTON_3:
			inputState = zoom;
			break;
		default:
			break;
		}

		break;
	}
	case GLFW_RELEASE: {
		inputState = idle;
		break;
	}
	default:
		break;
	}
}

void InputHandler::keyCallback(int key, int scancode, int action, int mods) {

	if (action != GLFW_PRESS) {
		return;
	}

	switch (key) {
	case GLFW_KEY_UP: {
		break;
	}
	default:
		break;
	}
}

void InputHandler::rotateCamera() const {
}

void InputHandler::translateCamera() const {
	glm::vec3 offset((prev_mouse_x - mouse_x) * camTransSpeed,
			(prev_mouse_y - mouse_y) * camTransSpeed, 0);
	renderer->translateCamera(offset);
}

void InputHandler::changeZoom() const {
}

void InputHandler::handleGoalRotation() const {
}

void InputHandler::mousePositionCallback(double mouse_x, double mouse_y) {
	prev_mouse_x = this->mouse_x;
	prev_mouse_y = this->mouse_y;

	this->mouse_x = mouse_x;
	this->mouse_y = mouse_y;

	switch (inputState) {
	case translate: {
		translateCamera();
		break;
	}
	default:
		break;
	}

}

void InputHandler::handleGoalTranslation() const {
}

void InputHandler::setRenderer(Renderer* renderer) {
	this->renderer = renderer;
}
