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
	camTransSpeed = 0.1;
	camRotSpeed = 0.005;
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
			inputState = cameraUpdate;
			break;
		case GLFW_MOUSE_BUTTON_2:
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

	if (action != GLFW_PRESS && action != GLFW_REPEAT) {
		return;
	}

	//TODO Allow diagonal movement
	switch (inputState) {
	case idle:
	case cameraUpdate: {
		// Move forward
		if (key == GLFW_KEY_UP || key == GLFW_KEY_W) {
			renderer->updateCameraPosition(
					renderer->getCamLookAtVector() * camTransSpeed);
		}
		// Move backward
		if (key == GLFW_KEY_DOWN || key == GLFW_KEY_S) {
			renderer->updateCameraPosition(
					-renderer->getCamLookAtVector() * camTransSpeed);
		}
		// Strafe right
		if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_D) {
			renderer->updateCameraPosition(
					renderer->getCamLookAtRightVector() * camTransSpeed);
		}
		// Strafe left
		if (key == GLFW_KEY_LEFT || key == GLFW_KEY_A) {
			renderer->updateCameraPosition(
					-renderer->getCamLookAtRightVector() * camTransSpeed);
		}
		break;
	}

	case goalUpdate: {
		if (key == GLFW_KEY_UP || key == GLFW_KEY_W) {
			goalMarker->translate(
					renderer->getCamLookAtVector() * camTransSpeed);
		}
		// Move backward
		if (key == GLFW_KEY_DOWN || key == GLFW_KEY_S) {
			goalMarker->translate(
					-renderer->getCamLookAtVector() * camTransSpeed);
		}
		// Strafe right
		if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_D) {
			goalMarker->translate(
					renderer->getCamLookAtRightVector() * camTransSpeed);
		}
		// Strafe left
		if (key == GLFW_KEY_LEFT || key == GLFW_KEY_A) {
			goalMarker->translate(
					-renderer->getCamLookAtRightVector() * camTransSpeed);
		}
		break;
	}
	}

	if (key == GLFW_KEY_ENTER) {
		simController->setGoal(goalMarker->getCurrentPosition());

		std::cout << "Goal is " << goalMarker->getCurrentPosition().x << ", "
				<< goalMarker->getCurrentPosition().y << ", "
				<< goalMarker->getCurrentPosition().z << std::endl;
	}
}

void InputHandler::mousePositionCallback(double mouseX, double mouseY) {

	switch (inputState) {
	case cameraUpdate: {
		renderer->updateLookAt(camRotSpeed * (prevMouseX - mouseX),
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

void InputHandler::setRenderer(Renderer* renderer) {
	this->renderer = renderer;
}

void InputHandler::updateGoalMarker(const glm::vec3& goal) {
	if (goalMarker) {
		goalMarker->translate(goal - goalMarker->getCurrentPosition());
	}
}
