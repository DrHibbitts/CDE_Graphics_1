/*
 * InputHandler.cpp
 *
 *  Created on: 14 Nov 2014
 *      Author: gdp24
 */

#define UNUSED(expr) (void)(expr);

#include "InputHandler.h"

InputHandler::InputHandler() {
	prevMouseX = 0;
	prevMouseY = 0;
	renderer = NULL;
	camTransSpeed = 0.1;
	camRotSpeed = 0.005;
	inputState = idle;
}

InputHandler::~InputHandler() {
}

void InputHandler::mouseButtonCallback(int button, int actions, int mods) {
	UNUSED(mods);
	switch (actions) {
	case GLFW_PRESS: {

		switch (button) {
		case GLFW_MOUSE_BUTTON_1:
			//Left click move camera
			inputState = cameraUpdate;
			break;
		case GLFW_MOUSE_BUTTON_2:
			//Right click move goal marker
			inputState = goalUpdate;
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
	UNUSED(mods);
	UNUSED(scancode);
	if (action != GLFW_PRESS && action != GLFW_REPEAT) {
		return;
	}

	glm::vec3 offset;
	getOffsetFromKey(key, offset);

	switch (inputState) {
	case idle:
	case cameraUpdate: {
		renderer->updateCameraPosition(offset);
		break;
	}

	case goalUpdate: {
		goalMarker->translate(offset);
		break;
	}
	}

	//If user press enter, send goal position to simulation controller
	if (key == GLFW_KEY_ENTER) {
		offset = goalMarker->getCurrentPosition();
		simController->setGoal(offset);

		std::cout << "Goal is " << offset.x << ", " << offset.y << ", "
				<< offset.z << std::endl;
	}
}

void InputHandler::mousePositionCallback(double mouseX, double mouseY) {

	switch (inputState) {
	case cameraUpdate: {
		//Rotate camera orientation
		renderer->updateCameraOrientation(camRotSpeed * (prevMouseX - mouseX),
				camRotSpeed * (prevMouseY - mouseY));
		break;
	}
	case goalUpdate:
		break;
	case idle:
		break;
	}

	prevMouseX = mouseX;
	prevMouseY = mouseY;

}

void InputHandler::setSimController(SimulationControllerPtr simController) {
	this->simController = simController;
}

void InputHandler::setGoalMarker(Point3DMarkerPtr goalMarker) {
	this->goalMarker = goalMarker;
}

void InputHandler::setRenderer(RendererPtr renderer) {
	this->renderer = renderer;
}

void InputHandler::updateGoalMarker(const glm::vec3& goal) {
	if (goalMarker) {
		goalMarker->translate(goal - goalMarker->getCurrentPosition());
	}
}

void InputHandler::getOffsetFromKey(int key, glm::vec3& offset) {
	//Move forward
	if (key == GLFW_KEY_UP || key == GLFW_KEY_W) {
		offset = renderer->getCamLookAtVector() * camTransSpeed;
	}
	// Move backward
	if (key == GLFW_KEY_DOWN || key == GLFW_KEY_S) {
		offset = -renderer->getCamLookAtVector() * camTransSpeed;
	}
	// Strafe right
	if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_D) {
		offset = renderer->getCamLookAtRightVector() * camTransSpeed;
	}
	// Strafe left
	if (key == GLFW_KEY_LEFT || key == GLFW_KEY_A) {
		offset = -renderer->getCamLookAtRightVector() * camTransSpeed;
	}
}
