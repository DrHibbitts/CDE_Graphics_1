/*
 * SimulationHandler.cpp
 *
 *  Created on: 31 Oct 2014
 *      Author: garoe
 */

#include "SimulationController.h"

SimulationController::SimulationController(double epsilon) :
		simSleepTime(20) {
	simulating = false;
	this->epsilon = epsilon;
}

SimulationController::~SimulationController() {
}

void SimulationController::executeSimulationLoop() {
	double stepSize = 0.01;

	while (simulating) {
		//If it didn't move much during a set of iterations stop simulating
		if (glm::length(chain->getEndEfectorPos() - goal) > epsilon) {
			lock.lock();
			simSolver.solveForStep(goal, stepSize);
			lock.unlock();
		}

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

	simSolver.setChain(chain);

	//Run new thread with simulation loop
	simulating = true;
	simulationThread = std::thread(&SimulationController::executeSimulationLoop,
			this);
}

void SimulationController::updateChain() {
	lock.lock();
	simSolver.updateChain();
	lock.unlock();
}
