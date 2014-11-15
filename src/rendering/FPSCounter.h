/*
 * FPSCounter.h
 *
 *  Created on: 31 Oct 2014
 *      Author: garoe
 */

#ifndef SRC_FPSCOUNTER_H_
#define SRC_FPSCOUNTER_H_

#include <string>
#include <sstream>
#include <thread>
#include <chrono>

// Include GLFW
#include <GLFW/glfw3.h>

class FPSCounter {
public:
	FPSCounter(double maxFps = 60);
	FPSCounter(GLFWwindow* window, const std::string& windowTitle,
			double maxFps = 60);
	virtual ~FPSCounter();

	void setWindowFPS();

	void setWindow(GLFWwindow* window, const std::string& windowTitle,
			double maxFps);

	void sleepForFixedFPS();

private:
	void init();

	GLFWwindow* window;
	std::string windowTitle;

	double timePerFrame;
	double currentTime;
	double prevTime;
	std::chrono::seconds sleepTime;

	//Variables for a FPS counter
	double t0Value;
	int fpsFrameCount;
	double fps;
	const double theTimeInterval;
};

#endif /* SRC_FPSCOUNTER_H_ */
