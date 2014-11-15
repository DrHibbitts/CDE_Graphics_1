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

	void mouseButtonCallback(int button, int actions, int mods);

	void mousePositionCallback(double mouseX, double mouseY);

	void keyCallback(int key, int scancode, int action, int mods);

	void setRenderer(Renderer* renderer);

private:
	void rotateCamera() const;
	void translateCamera(const glm::vec3& translation) const;
	void changeZoom() const;

	void handleGoalRotation() const;
	void handleGoalTranslation() const;

	double prevMouseX;
	double prevMouseY;

	float camTransSpeed;
	float camRotSpeed;

	enum InputState {
		translate, rotate, zoom, idle
	};

	InputState inputState;

	Renderer* renderer;
	bool settingGoal;
};

#endif /* SRC_INPUTHANDLER_H_ */
