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

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <boost/pointer_cast.hpp>

#include "rendering/drawables/Chain.h"
#include "rendering/drawables/Drawable.h"
#include "rendering/drawables/Point3DMarker.h"
#include "rendering/FPSCounter.h"
#include "rendering/Renderer.h"
#include "simulation/SimulationController.h"
#include "InputHandler.h"

//TODO A better design is a general controller class that synchronises window,
//simulation and input handling

//Window class is a wrapper around GLFWwindow, it controls what objects
//are rendered and handles the user input. It is a singleton, solo only one
//instance is allowed to exist
class Window {
public:
	// Class is accessed and created via getInstance()
	static Window& getInstance();

	virtual ~Window();

	void createWindow(unsigned int height, unsigned int width,
			const std::string& windowTitle, double maxFps);

	void addDrawable(DrawablePtr drawable);
	void removeDrawable(DrawablePtr drawable);

	void executeMainLoop();

	glm::vec3 getWorldCoordFromScreen(const glm::vec3& screenCoord);

	InputHandler& getInputHandler();

private:
	void init();

	void cleanUp();

	void setCallbacks();

	//The callbacks have to be static functions to work with GLFW
	static void mouseButtonCallback(GLFWwindow *window, int button, int actions,
			int mods);

	static void mousePosCallback(GLFWwindow *window, double xpos, double ypos);

	static void keyCallback(GLFWwindow *window, int key, int scancode,
			int action, int mods);

	Window(void); // private constructor necessary to allow only one instance
	Window(Window const&); // prevent copies
	void operator=(Window const&) {
	}
	; // prevent assignments

private:
	GLFWwindow* window;
	RendererPtr renderer;
	SimulationControllerPtr simController;
	InputHandler inputHandler;

	std::vector<DrawablePtr> toDrawObjects;

	FPSCounter fpsCounter;

	typedef std::vector<DrawablePtr>::iterator DrawableIte;
};

#endif /* WINDOW_H_ */
