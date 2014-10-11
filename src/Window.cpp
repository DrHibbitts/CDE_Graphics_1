/*
 * Window.cpp
 *
 *  Created on: 12 Oct 2014
 *      Author: garoe
 */

#include "Window.h"

Window::Window()
{
	init();
}

Window::Window(unsigned int height, unsigned int width,
		const std::string& windowTitle)
{
	init();
	createWindow(height, width, windowTitle);
}

void Window::init()
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf( stderr, "Failed to initialize GLFW\n");
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = NULL;
	renderer = NULL;
}

Window::~Window()
{
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	delete renderer;
}

bool Window::createWindow(unsigned int height, unsigned int width,
		const std::string& windowTitle)
{
	// Open a window and create its OpenGL context
	window = glfwCreateWindow(height, width, windowTitle.c_str(), NULL, NULL);
	if (window == NULL)
	{
		fprintf( stderr,
				"Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		return false;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	renderer = new Renderer();
	return true;
}

void Window::addDrawable(DrawablePtr drawable)
{
	toDrawObjects.push_back(drawable);
}

void Window::removeDrawable(DrawablePtr drawable)
{
	DrawableIte it = toDrawObjects.begin();
	for (it = toDrawObjects.begin(); it != toDrawObjects.end(); ++it)
	{
		if (it->get() == drawable.get())
		{
			toDrawObjects.erase(it);
			break;
		}
	}
}

void Window::runLoop()
{
	do
	{
		renderer->resetScreen();
		DrawableIte it;
		for (it = toDrawObjects.begin(); it != toDrawObjects.end(); ++it)
		{
			(*it)->draw(*renderer);
		}

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
			&& glfwWindowShouldClose(window) == 0);
}

GLFWwindow* Window::getWindow() const
{
	return window;
}

Renderer* Window::getRenderer() const
{
	return renderer;
}
