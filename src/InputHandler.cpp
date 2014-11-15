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
	camRotSpeed = 0.002;
	inputState = idle;
	rotAxis = rotX;
	mouseSpeed = 0.005;

	// Initial horizontal angle : toward Z
	horizontalAngle = 0.0f;
	// Initial vertical angle : none
	verticalAngle = 0.0f;
	position = glm::vec3(0, 0, -13);
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

	float speed = 3.0f;

	// Move forward
	if (key == GLFW_KEY_UP || key == GLFW_KEY_W) {
		renderer->updateCameraPosition(renderer->getCamLookAtVector() * speed);
	}
	// Move backward
	if (key == GLFW_KEY_DOWN || key == GLFW_KEY_S) {
		renderer->updateCameraPosition(-renderer->getCamLookAtVector() * speed);
	}
	// Strafe right
	if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_D) {
		renderer->updateCameraPosition(
				renderer->getCamLookAtRightVector() * speed);
	}
	// Strafe left
	if (key == GLFW_KEY_LEFT || key == GLFW_KEY_A) {
		renderer->updateCameraPosition(
				-renderer->getCamLookAtRightVector() * speed);
	}
}

void InputHandler::handleGoalRotation() const {
}

void InputHandler::mousePositionCallback(double mouseX, double mouseY) {

	switch (inputState) {
	case translate:
		renderer->updateLookAt(mouseSpeed * (prevMouseX - mouseX),
				mouseSpeed * (prevMouseY - mouseY));
		break;
	case rotate:
		break;
	case zoom:
		break;
	case idle:
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
