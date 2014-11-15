/*
 * InputHandler.cpp
 *
 *  Created on: 14 Nov 2014
 *      Author: gdp24
 */

#include "InputHandler.h"

InputHandler::InputHandler() {
	prevMouseX = 0;
	prevMouseY = 0;
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

void InputHandler::translateCamera(const glm::vec3& translation) const {
	renderer->translateCamera(camTransSpeed * translation);
}

void InputHandler::changeZoom() const {
}

void InputHandler::handleGoalRotation() const {
}

void InputHandler::mousePositionCallback(double mouseX, double mouseY) {

	switch (inputState) {
	case translate: {
		translateCamera(glm::vec3(prevMouseX - mouseX, prevMouseY - mouseY, 0));
		break;
	}
	case zoom: {
		translateCamera(glm::vec3(0, 0, prevMouseY - mouseY));
		break;
	}
	default:
		break;
	}

	prevMouseX = mouseX;
	prevMouseY = mouseY;

}

void InputHandler::handleGoalTranslation() const {
}

void InputHandler::setRenderer(Renderer* renderer) {
	this->renderer = renderer;
}
