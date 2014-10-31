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

// Include GLFW
#include <GLFW/glfw3.h>

class FPSCounter {
public:
	FPSCounter();
	FPSCounter(GLFWwindow* window, const std::string& windowTitle);
	virtual ~FPSCounter();

	void setWindowFPS();

	void setWindow(GLFWwindow* window, const std::string& windowTitle);

private:
	void init();

	GLFWwindow* window;
	std::string windowTitle;

	//Variables for a FPS counter
	double t0Value;
	int fpsFrameCount;
	double fps;
	const double theTimeInterval;
};

#endif /* SRC_FPSCOUNTER_H_ */
