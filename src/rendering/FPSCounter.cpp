/*
 * FPSCounter.cpp
 *
 *  Created on: 31 Oct 2014
 *      Author: garoe
 */

#include "FPSCounter.h"

FPSCounter::FPSCounter(double maxFps) :
		theTimeInterval(1.0) {
	timePerFrame = 1 / maxFps;
	init();
}

FPSCounter::FPSCounter(GLFWwindow* window, const std::string& windowTitle,
		double maxFps) :
		theTimeInterval(1.0) {
	timePerFrame = 1 / maxFps;
	init();
	setWindow(window, windowTitle, maxFps);
}

FPSCounter::~FPSCounter() {
}

void FPSCounter::setWindowFPS() {
	if (window == NULL) {
		return;
	}
	// Get the current time in seconds since the program started (non-static, so executed every time)
	currentTime = glfwGetTime();

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

void FPSCounter::setWindow(GLFWwindow* window, const std::string& windowTitle,
		double maxFps) {
	this->window = window;
	this->windowTitle = windowTitle;
	timePerFrame = 1 / maxFps;
}

void FPSCounter::init() {
	t0Value = glfwGetTime(); // Set the initial time to now
	fpsFrameCount = 0;        // Set the initial FPS frame count to 0
	fps = 0.0;           // Set the initial FPS value to 0.0
	currentTime = t0Value;
	prevTime = t0Value;

	window = NULL;
}

void FPSCounter::sleepForFixedFPS() {
	//Cap the frame rate at maxFPS, so if there is still time left after the
	//rendering is done. Then, sleep the current frame for the extra time
	if (currentTime - prevTime < timePerFrame) {
		//Get extra time in milliseconds
		int duration = (timePerFrame - (currentTime - prevTime)) * 1000;
		std::this_thread::sleep_for(std::chrono::milliseconds(duration));
	}
	//Update the previous time to be and the end of this frame
	prevTime = glfwGetTime();
}
