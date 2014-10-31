/*
 * FPSCounter.cpp
 *
 *  Created on: 31 Oct 2014
 *      Author: garoe
 */

#include "FPSCounter.h"

FPSCounter::FPSCounter() :
		theTimeInterval(1.0) {
	init();
}

FPSCounter::FPSCounter(GLFWwindow* window, const std::string& windowTitle) :
		theTimeInterval(1.0) {
	init();
	setWindow(window, windowTitle);
}

FPSCounter::~FPSCounter() {
}

void FPSCounter::setWindowFPS() {
	if (window == NULL) {
		return;
	}
	// Get the current time in seconds since the program started (non-static, so executed every time)
	double currentTime = glfwGetTime();

	// Calculate and display the FPS every specified time interval
	if ((currentTime - t0Value) > theTimeInterval) {
		// Calculate the FPS as the number of frames divided by the interval in seconds
		fps = (double) fpsFrameCount / (currentTime - t0Value);

		// Convert the fps value into a string using an output stringstream
		std::ostringstream stream;
		stream << fps;
		std::string fpsString = stream.str();

		glfwSetWindowTitle(window,
				(windowTitle + " | FPS: " + fpsString).c_str());

		// Reset the FPS frame counter and set the initial time to be now
		fpsFrameCount = 0;
		t0Value = glfwGetTime();
	} else // FPS calculation time interval hasn't elapsed yet? Simply increment the FPS frame counter
	{
		fpsFrameCount++;
	}
}

void FPSCounter::setWindow(GLFWwindow* window, const std::string& windowTitle) {
	this->window = window;
	this->windowTitle = windowTitle;
}

void FPSCounter::init() {
	t0Value = glfwGetTime(); // Set the initial time to now
	fpsFrameCount = 0;        // Set the initial FPS frame count to 0
	fps = 0.0;           // Set the initial FPS value to 0.0
	window = NULL;
}
