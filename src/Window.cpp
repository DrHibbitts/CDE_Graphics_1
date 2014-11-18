/*
 * Window.cpp
 *
 *  Created on: 12 Oct 2014
 *      Author: garoe
 */
#define UNUSED(expr) (void)(expr);

#include "Window.h"

Window& Window::getInstance() {
	static Window instance; // lazy singleton, instantiated on first use
	return instance;
}

void Window::cleanUp() {
	//Terminate simulation thread
	simController->killSimulation();

	// Close OpenGL window, terminate GLFW and free the window* memory
	glfwTerminate();
}

Window::Window() :
		simController(new SimulationController()) {
	init();
}

void Window::init() {
	// Initialise GLFW
	if (!glfwInit()) {
		fprintf( stderr, "Failed to initialize GLFW\n");
	}

	//Set OpenGL version
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Window is required to be a pointer by GLFW
	window = NULL;
}

Window::~Window() {
	// Close OpenGL window and terminate GLFW
	glDeleteProgram(renderer->getProgramId());
	cleanUp();

	std::cout << "MAIN THREAD EXIT" << std::endl;
}

void Window::createWindow(unsigned int height, unsigned int width,
		const std::string& windowTitle, double maxFps) {
	//If this is not a first call close the previous windows and free the memory
	cleanUp();
	init();

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(height, width, windowTitle.c_str(), NULL, NULL);
	if (window == NULL) {
		fprintf( stderr,
				"Failed to open GLFW window. Try switching from Intel GPU to a Nvidia or AMD GPU.\n");
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(window);

	// Initialise GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialise GLEW\n");
		exit(-1);
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	//Renderer can only be initialised after calling glewInit, so instead of
	//creating an init() method in Renderer is easier to have it as a pointer
	//Also it is better to pass a pointer to InputHandler
	renderer = RendererPtr(new Renderer());

	fpsCounter.setWindow(window, windowTitle, maxFps);

	inputHandler.setRenderer(renderer);
	inputHandler.setSimController(simController);

	setCallbacks();
}

void Window::addDrawable(DrawablePtr drawable) {
	toDrawObjects.push_back(drawable);

	//Check if the object is a chain
	ChainPtr newChain = boost::dynamic_pointer_cast<Chain>(drawable);
	//If it is a chain create a new thread that will run the simulation
	if (newChain) {
		glm::vec3 goal = newChain->getEndEfectorPos();
		inputHandler.updateGoalMarker(goal);
		simController->setGoal(goal);

		simController->startSimulation(newChain);

	}
}

void Window::removeDrawable(DrawablePtr drawable) {
	DrawableIte it = toDrawObjects.begin();
	for (it = toDrawObjects.begin(); it != toDrawObjects.end(); ++it) {
		if (it->get() == drawable.get()) {
			toDrawObjects.erase(it);
			break;
		}
	}

	//Check if the object is a chain
	if (drawable == simController->getChain()) {
		simController->killSimulation();
	}
}

void Window::executeMainLoop() {
	glUseProgram(renderer->getProgramId());

	do {
		renderer->resetScreen();

		//Render all objects
		DrawableIte it;
		for (it = toDrawObjects.begin(); it != toDrawObjects.end(); ++it) {
			if (boost::dynamic_pointer_cast<Chain>(*it)) {
				simController->updateChain();
				(*it)->draw(*renderer);
			} else {
				(*it)->draw(*renderer);
			}
		}

		//Draw for this frame
		glfwSwapBuffers(window);

		//Get user input
		glfwPollEvents();

		//Make sure we are not running faster than the max FPS
		fpsCounter.sleepForFixedFPS();

		//Display FPS
		fpsCounter.setWindowFPS();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
			&& glfwWindowShouldClose(window) == 0);
}

void Window::setCallbacks() {
	glfwSetMouseButtonCallback(window, &mouseButtonCallback);
	glfwSetKeyCallback(window, &keyCallback);
	glfwSetCursorPosCallback(window, &mousePosCallback);
}

glm::vec3 Window::getWorldCoordFromScreen(const glm::vec3& screenCoord) {
	return renderer->getWorldCoordFromScreen(screenCoord);
}

void Window::keyCallback(GLFWwindow *window, int key, int scancode, int action,
		int mods) {
	UNUSED(window);
	getInstance().inputHandler.keyCallback(key, scancode, action, mods);
}

void Window::mouseButtonCallback(GLFWwindow* window, int button, int actions,
		int mods) {
	UNUSED(window);
	getInstance().inputHandler.mouseButtonCallback(button, actions, mods);
}

void Window::mousePosCallback(GLFWwindow *window, double xpos, double ypos) {
	UNUSED(window);
	getInstance().inputHandler.mousePositionCallback(xpos, ypos);
}

Window::Window(const Window&) :
		simController(new SimulationController()) {
	cleanUp();
	init();
}

InputHandler& Window::getInputHandler() {
	return inputHandler;
}
