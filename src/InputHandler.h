/*
 * InputHandler.h
 *
 *  Created on: 14 Nov 2014
 *      Author: gdp24
 */

#ifndef SRC_INPUTHANDLER_H_
#define SRC_INPUTHANDLER_H_

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include "rendering/Renderer.h"

class Window;

class InputHandler {
public:
	InputHandler(Window* window);
	virtual ~InputHandler();

	void mouseCallback(GLFWwindow *glfwWindow, int button, int actions,
			int mods) const;

	void keyCallback(GLFWwindow *window, int key, int scancode, int action,
			int mods) const;
private:
	void handleWindowRotation() const;
	void handleWindowTranslation() const;
	void handleWindowZoom() const;

	void handleGoalRotation() const;
	void handleGoalTranslation() const;

	Window* window;
	bool settingGoal;
};

#endif /* SRC_INPUTHANDLER_H_ */
