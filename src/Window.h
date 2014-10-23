/*
 * Window.h
 *
 *  Created on: 12 Oct 2014
 *      Author: garoe
 */

#ifndef WINDOW_H_
#define WINDOW_H_

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include <boost/pointer_cast.hpp>

#include "Renderer.h"
#include "Drawable.h"

class Window {
public:
	static Window& getInstance(); // Singleton is accessed via getInstance()

	virtual ~Window();

	void createWindow(unsigned int height, unsigned int width,
			const std::string& windowTitle);

	void addDrawable(DrawablePtr drawable);
	void removeDrawable(DrawablePtr drawable);

	void runLoop();

	//May return null pointer
	GLFWwindow* getWindow() const;
	Renderer* getRenderer() const;

private:
	void init();

	void cleanUp();

	void setCallbacks();

	static void mouseCallback(GLFWwindow *window, int button, int actions,
			int mods);

	void setWindowFPS();

	Window(void); // private constructor necessary to allow only 1 instance
	Window(Window const&); // prevent copies
	void operator=(Window const&) {
	}
	; // prevent assignments

private:
	GLFWwindow* window;
	Renderer* renderer;
	std::vector<DrawablePtr> toDrawObjects;
	std::string windowTitle;

	double t0Value; // Set the initial time to now
	int fpsFrameCount;        // Set the initial FPS frame count to 0
	double fps;           // Set the initial FPS value to 0.0
	const double theTimeInterval;

	typedef std::vector<DrawablePtr>::iterator DrawableIte;
};

#endif /* WINDOW_H_ */
