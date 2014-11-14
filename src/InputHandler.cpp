/*
 * InputHandler.cpp
 *
 *  Created on: 14 Nov 2014
 *      Author: gdp24
 */

#include "InputHandler.h"

InputHandler::InputHandler() {
	renderer = NULL;
}

InputHandler::~InputHandler() {
	// TODO Auto-generated destructor stub
}

void InputHandler::setRenderer(Renderer* renderer) {
	this->renderer = renderer;
}

void InputHandler::mouseCallback(GLFWwindow* window, int button, int actions,
		int mods) {
}
