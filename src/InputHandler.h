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
#include "rendering/drawables/Point3DMarker.h"
#include "simulation/SimulationController.h"

class InputHandler {
public:
	InputHandler();
	virtual ~InputHandler();

	void mouseButtonCallback(int button, int actions, int mods);

	void mousePositionCallback(double mouseX, double mouseY);

	void keyCallback(int key, int scancode, int action, int mods);

	void setRenderer(Renderer* renderer);
	void setSimController(SimulationControllerPtr simController);
	void setGoalMarker(Point3DMarkerPtr goalMarker);

	void updateGoalMarker(const glm::vec3& goal);

private:
	Renderer* renderer;
	SimulationControllerPtr simController;
	Point3DMarkerPtr goalMarker;

	double prevMouseX;
	double prevMouseY;

	float camTransSpeed;
	float camRotSpeed;

	enum InputState {
		cameraUpdate, goalUpdate, idle
	};

	InputState inputState;
};

#endif /* SRC_INPUTHANDLER_H_ */
