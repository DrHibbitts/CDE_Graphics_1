#include <GL/glew.h>

//Force radians to avoid pragma deprecated warnings
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "Window.h"
#include "rendering/drawables/Triangle.h"
#include "rendering/drawables/Line.h"
#include "rendering/drawables/Square.h"
#include "rendering/drawables/Axis.h"
#include "rendering/drawables/Chain.h"
#include "rendering/drawables/Line.h"
#include "rendering/drawables/Point3DMarker.h"

int main(void) {
	//Only one Window is allowed in the application, singleton pattern
	//Create a window of: width, height, title
	Window& window = Window::getInstance();
	window.createWindow(1024, 768,
			std::string("Inverse kinematics course work"), 60.0);

	//All objects to be drawn have to be created with their pointers
	//Create 3D axis object
	AxisPtr axis(new Axis());

	//Once an object is added to the window, it will be rendered
	window.addDrawable(axis);

	Point3DMarkerPtr goalMarker(new Point3DMarker());
	goalMarker->setUniformColor(glm::vec3(0, 1, 1));

	// Add the marker to inputHandler before adding the Chain to Window
	// If not, the marker wont get initialised to chain initial position
	window.getInputHandler().setGoalMarker(goalMarker);
	window.addDrawable(goalMarker);

	//Create a chain object
	ChainPtr chain(new Chain());

	// Set minimum and maximum angles, MinZ, MaxZ, MinY, MaxY
	chain->setAngleConstrains(-180, 180, -180, 180);

	//Add several bones with different lengths and joints rotations
	//Bone of length 1
	chain->addBone(1);
	//Change the angle of joint 0 to Z degrees and Y degrees
	chain->setJointAngles(0, 0, 0);
	chain->setBoneStiffness(0, 10);

	chain->addBone(0.5);
	chain->setJointAngles(1, 0, 0);
	chain->setBoneStiffness(1, 1);

	chain->addBone(2);
	chain->setJointAngles(2, 0, 0);
	chain->setBoneStiffness(2, 1);

	chain->addBone(1);
	chain->setJointAngles(3, 0, 0);
	chain->setBoneStiffness(3, 1);

	chain->addBone(1);
	chain->setJointAngles(4, 0, 0);
	chain->setBoneStiffness(4, 1);

	//Draw chain
	window.addDrawable(chain);

	//This only changes the light marker, to change the position go to
	//the renderer class
	glm::vec3 lightPosition(3, 3, -1);

	Point3DMarkerPtr lightMarker(new Point3DMarker());
	lightMarker->setUniformColor(glm::vec3(0.9, 0.9, 0.9));
	lightMarker->translate(lightPosition);

	window.addDrawable(lightMarker);

	//Start the rendering, simulation and input handling loop
	window.executeMainLoop();

	return 0;
}
