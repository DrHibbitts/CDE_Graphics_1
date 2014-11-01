/*
 * SimulationHandler.cpp
 *
 *  Created on: 31 Oct 2014
 *      Author: garoe
 */

#include "SimulationController.h"

SimulationController::SimulationController() :
		simSleepTime(20) {
	simulating = false;
}

SimulationController::~SimulationController() {
}

void SimulationController::executeSimulationLoop() {

	while (simulating) {

		simSolver.solveForStep(chain, goal);

		//Sleep the thread a bit, since is way too fast
		std::this_thread::sleep_for(simSleepTime);
	}

	std::cout << "SIMULATION THREAD EXIT" << std::endl;
}

void SimulationController::killSimulation() {
	//Tell simulation thread to finish
	simulating = false;
	if (simulationThread.joinable()) {
		//Wait for the simulation thread to finish
		simulationThread.join();
	}

	//Delete chain pointer
	chain.reset();
}

const ChainPtr SimulationController::getChain() const {
	return chain;
}

const glm::vec3& SimulationController::getGoal() const {
	return goal;
}

void SimulationController::setGoal(const glm::vec3& goal) {
	this->goal = goal;
}

void SimulationController::startSimulation(ChainPtr chain) {

	//If thread was running stop it
	killSimulation();

	//Save chain pointer
	this->chain = chain;

	//Run new thread with simulation loop
	simulating = true;
	simulationThread = std::thread(&SimulationController::executeSimulationLoop,
			this);
}
