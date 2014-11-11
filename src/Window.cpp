/*
 * Window.cpp
 *
 *  Created on: 12 Oct 2014
 *      Author: garoe
 */

#include "Window.h"

Window& Window::getInstance() {
	static Window instance; // lazy singleton, instantiated on first use
	return instance;
}

void Window::cleanUp() {
	//Terminate simulation thread
	simController.killSimulation();

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	delete renderer;
	renderer = NULL;
}

Window::Window() : simController(lock){
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
	//Renderer can only be initialised after calling glewInit, so instead of
	//creating an init() method in Renderer is easier to have it as a pointer
	renderer = NULL;
}

Window::~Window() {
	// Close OpenGL window and terminate GLFW
	glDeleteProgram(renderer->getProgramId());
	cleanUp();

	std::cout << "MAIN THREAD MEMORY FREED AND EXIT" << std::endl;
}

void Window::createWindow(unsigned int height, unsigned int width,
		const std::string& windowTitle) {
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

	renderer = new Renderer();

	fpsCounter.setWindow(window, windowTitle);

	setCallbacks();
}

void Window::addDrawable(DrawablePtr drawable) {
	toDrawObjects.push_back(drawable);

	//Check if the object is a chain
	ChainPtr newChain = boost::dynamic_pointer_cast<Chain>(drawable);
	//If it is a chain create a new thread that will run the simulation
	if (newChain) {
		glm::vec3 goal = newChain->getEndEfectorPos();
		updateGoalMarker(goal);
		simController.setGoal(goal);

		simController.startSimulation(newChain);

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
	if (drawable == simController.getChain()) {
		simController.killSimulation();
	}
}

void Window::executeMainLoop() {
	glUseProgram(renderer->getProgramId());

	do {
		renderer->resetScreen();

		//Render all objects
		DrawableIte it;
		for (it = toDrawObjects.begin(); it != toDrawObjects.end(); ++it) {
			if(boost::dynamic_pointer_cast<Chain>(*it)){
				lock.lock();
				(*it)->draw(*renderer);
				lock.unlock();
			} else {
				(*it)->draw(*renderer);
			}
		}

		//Move the square a bit every frame
//		DrawablePtr ob = toDrawObjects[0];
//		SquarePtr sq = boost::static_pointer_cast<Square>(ob);
//		sq->translate(glm::vec3(0.05, 0, 0));

		// Swap buffers
		glfwSwapBuffers(window);

		//Display FPS
		fpsCounter.setWindowFPS();

		//Get user input
		glfwPollEvents();

		//Mouse polling example
		//if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
		//Change angle on mouse click
		//DrawablePtr ob = toDrawObjects[1];
		//ChainPtr ch = boost::static_pointer_cast<Chain>(ob);
		//chain->setJointAngle(2, chain->getJointAngle(2) + 1);
		//}

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
			&& glfwWindowShouldClose(window) == 0);
}

void Window::setCallbacks() {
	glfwSetMouseButtonCallback(window, &mouseCallback);
}

void Window::mouseCallback(GLFWwindow* window, int button, int actions,
		int mods) {
	getInstance().mouseCallbackImpl(window, button, actions, mods);
}

void Window::updateGoalMarker(const glm::vec3& goal) {
	DrawablePtr ob = toDrawObjects[1];
	TrianglePtr tr = boost::static_pointer_cast<Triangle>(ob);
	tr->translate(goal - tr->getCurrentPosition());
}

void Window::mouseCallbackImpl(GLFWwindow* window, int button, int actions,
		int mods) {
	//Mouse callback example
	if (button == GLFW_MOUSE_BUTTON_1) {
		if (actions == GLFW_RELEASE) {
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			glm::vec3 goal = renderer->getWorldCoordFromScreen(
					glm::vec3(xpos, ypos, 0));
			simController.setGoal(goal);

			updateGoalMarker(goal);
			std::cout << "Goal is " << goal.x << ", " << goal.y << ", "
					<< goal.z << std::endl;
		}
	}
}

Window::Window(const Window&): simController(lock) {
	cleanUp();
	init();
}
