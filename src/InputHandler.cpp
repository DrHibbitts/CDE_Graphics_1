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

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f),
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);
	float speed = 3.0f;
	// Up vector
	glm::vec3 up = glm::cross( right, direction );

	// Move forward
	if (key == GLFW_KEY_UP || key == GLFW_KEY_W){
		position += direction * speed;
	}
	// Move backward
	if (key == GLFW_KEY_DOWN || key == GLFW_KEY_S ){
		position -= direction * speed;
	}
	// Strafe right
	if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_D ){
		position += right * speed;
	}
	// Strafe left
	if (key == GLFW_KEY_LEFT || key == GLFW_KEY_A ){
		position -= right * speed;
	}

	renderer->setCameraLookAt(position, position+direction, up);
}

void InputHandler::rotateCamera(float angle) const {
	if(rotAxis == rotX){
		renderer->rotateXCamera(angle * camRotSpeed);
	} else if (rotAxis == rotY) {
		renderer->rotateYCamera(angle * camRotSpeed);
	} else if (rotAxis == rotZ) {
		renderer->rotateZCamera(angle * camRotSpeed);
	}
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
	case translate:{
		horizontalAngle += mouseSpeed * (prevMouseX - mouseX);
		verticalAngle += mouseSpeed * (prevMouseY - mouseY);

		// Direction : Spherical coordinates to Cartesian coordinates conversion
		glm::vec3 direction(
			cos(verticalAngle) * sin(horizontalAngle),
			sin(verticalAngle),
			cos(verticalAngle) * cos(horizontalAngle)
		);

		// Right vector
		glm::vec3 right = glm::vec3(
			sin(horizontalAngle - 3.14f/2.0f),
			0,
			cos(horizontalAngle - 3.14f/2.0f)
		);

		glm::vec3 up = glm::cross( right, direction );

		renderer->setCameraLookAt(position, position+direction, up);
		break;
	}
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
