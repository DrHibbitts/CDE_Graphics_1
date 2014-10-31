/*
 * Window.h
 *
 *  Created on: 12 Oct 2014
 *      Author: garoe
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <boost/pointer_cast.hpp>

#include "Renderer.h"
#include "Drawable.h"
#include "SimulationSolver.h"

#include "Chain.h"

//Window class is a wrapper around GLFWwindow, it controls what objects
//are rendered and handles the user input. It is a singleton, solo only one
//instance is allowed to exist
class Window {
public:
	// Class is accessed and created via getInstance()
	static Window& getInstance();

	virtual ~Window();

	void createWindow(unsigned int height, unsigned int width,
			const std::string& windowTitle);

	void addDrawable(DrawablePtr drawable);
	void removeDrawable(DrawablePtr drawable);

	void executeMainLoop();

private:
	void init();

	void cleanUp();

	void setCallbacks();

	//The callback has to be a static function according to GLFW
	static void mouseCallback(GLFWwindow *window, int button, int actions,
			int mods);

	void mouseCallbackImpl(GLFWwindow *window, int button, int actions,
			int mods);

	void executeSimulationLoop();

	void killSimulation();

	void setWindowFPS();

	Window(void); // private constructor necessary to allow only one instance
	Window(Window const&); // prevent copies
	void operator=(Window const&) {
	}
	; // prevent assignments

private:
	GLFWwindow* window;
	Renderer* renderer;
	std::vector<DrawablePtr> toDrawObjects;
	std::string windowTitle;

	ChainPtr chain;
	SimulationSolver simSolver;
	std::thread simulationThread;
	bool continueSimulation;
	glm::vec3 goal;
	std::chrono::milliseconds simSleepTime;

	//Variables for a FPS counter
	double t0Value;
	int fpsFrameCount;
	double fps;
	const double theTimeInterval;

	typedef std::vector<DrawablePtr>::iterator DrawableIte;
};

#endif /* WINDOW_H_ */
