/*
 * InputHandler.h
 *
 *  Created on: 14 Nov 2014
 *      Author: gdp24
 */

#ifndef SRC_INPUTHANDLER_H_
#define SRC_INPUTHANDLER_H_

#include "rendering/Renderer.h"

class InputHandler {
public:
	InputHandler();
	virtual ~InputHandler();

	void setRenderer(Renderer* renderer);

	void mouseCallback(GLFWwindow *window, int button, int actions,
			int mods);
private:
	Renderer* renderer;
};

#endif /* SRC_INPUTHANDLER_H_ */
