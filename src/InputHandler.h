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


class InputHandler {
public:
	InputHandler();
	virtual ~InputHandler();

	void mouseCallback(double mouse_x, double mouse_y, int button, int actions,
			int mods);

	void keyCallback(int key, int scancode, int action, int mods);

	void setRenderer(Renderer* renderer);

private:
	void handleCameraRotation() const;
	void handleCameraTranslation() const;
	void handleRenameZoom() const;

	void handleGoalRotation() const;
	void handleGoalTranslation() const;

	double mouse_x;
	double mouse_y;
	double prev_mouse_x;
	double prev_mouse_y;

	Renderer* renderer;
	bool settingGoal;
};

#endif /* SRC_INPUTHANDLER_H_ */
