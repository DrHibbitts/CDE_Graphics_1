/*
 * SimulationHandler.cpp
 *
 *  Created on: 31 Oct 2014
 *      Author: garoe
 */

#include "SimulationController.h"

SimulationController::SimulationController() {
	simulating = false;
	epsilon = 0.003;
	numIterations = 0;
	maxIterations = 1000;
	simState = idle;
	stepSleepTime = std::chrono::milliseconds(20);
	waitForNewGoal.lock();
}

SimulationController::~SimulationController() {
}

void SimulationController::executeSimulationLoop() {
	double stepSize = 0.01;

	while (simulating) {
		switch (simState) {
		case stepping: {
			//Check distance to goal
			if (glm::length(chain->getEndEfectorPos() - goal) > epsilon) {
				lock.lock();
				simSolver.solveForStep(goal, stepSize);
				lock.unlock();
				numIterations++;
				if (numIterations >= maxIterations) {
					simState = reachedMaxIte;
				}
			} else {
				simState = reachedGoal;
			}
			break;
		}
		case reachedGoal: {
			std::cout << "Goal reached" << std::endl;
			simState = idle;
			//When switching to idle sleep for longer
			waitForNewGoal.lock();
			break;
		}
		case reachedMaxIte: {
			std::cout << "Max iterations reached" << std::endl;
			simState = idle;
			waitForNewGoal.lock();
			break;
		}
		case idle: {
			std::cout << "Waiting for new goal" << std::endl;
			waitForNewGoal.lock();
			break;
		}
		case exitState: {
			std::cout << "Exiting simulation loop" << std::endl;
			break;
		}
		}
		//Sleep the thread a bit, since is way too fast
		std::this_thread::sleep_for(stepSleepTime);
	}

	std::cout << "SIMULATION THREAD EXIT" << std::endl;
}

void SimulationController::killSimulation() {
	//Tell simulation thread to finish
	simState = exitState;
	waitForNewGoal.unlock();
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
	numIterations = 0;
	simState = stepping;
	waitForNewGoal.unlock();
}

void SimulationController::startSimulation(ChainPtr chain) {

	//If thread was running stop it
	killSimulation();

	//Save chain pointer
	this->chain = chain;

	simSolver.setChain(chain);

	//Run new thread with simulation loop
	simulating = true;
	simState = idle;
	waitForNewGoal.lock();

	simulationThread = std::thread(&SimulationController::executeSimulationLoop,
			this);
}

void SimulationController::updateChain() {
	lock.lock();
	simSolver.updateChain();
	lock.unlock();
}
