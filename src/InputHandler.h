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
	void rotateCamera(float angle) const;
	void translateCamera(const glm::vec3& translation) const;
	void changeZoom() const;

	void handleGoalRotation() const;
	void handleGoalTranslation() const;

	double prevMouseX;
	double prevMouseY;

	float camTransSpeed;
	float camRotSpeed;
	float mouseSpeed;

	enum InputState {
		translate, rotate, zoom, idle
	};

	enum RotAxis {
		rotX, rotY, rotZ
	};

	InputState inputState;
	RotAxis rotAxis;

	// Initial horizontal angle : toward -Z
	float horizontalAngle;
	// Initial vertical angle : none
	float verticalAngle;
	glm::vec3 position;

	Renderer* renderer;
	bool settingGoal;
};

#endif /* SRC_INPUTHANDLER_H_ */
