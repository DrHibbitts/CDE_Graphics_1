/*
 * SimulationHandler.cpp
 *
 *  Created on: 31 Oct 2014
 *      Author: garoe
 */

#include "SimulationController.h"

SimulationController::SimulationController() {
	simulating = false;
	epsilon = 0.01;
	numIterations = 0;
	maxIterations = 750;
	simState = idle;
	stepSleepTime = std::chrono::milliseconds(20);
	waitForNewGoal.lock();
	realGoal = true;
	stepSize = 0.4;
}

SimulationController::~SimulationController() {
}

void SimulationController::executeSimulationLoop() {
	while (simulating) {
		stateLock.lock();
		switch (simState) {
		case stepping: {
			stateLock.unlock();

			chainDataLock.lock();
			double distToGoal = glm::length(
					simSolver.getChain().getEndEfectorPos() - goal);
			chainDataLock.unlock();

			stateLock.lock();
			//Check distance to goal
			if (distToGoal > epsilon) {
			stateLock.unlock();

				chainDataLock.lock();
				simSolver.solveForStep(stepSize);
				chainDataLock.unlock();

				stateLock.lock();
				numIterations++;
				if (numIterations >= maxIterations) {
					simState = reachedMaxIte;
				}
				stateLock.unlock();
			} else {
				simState = reachedGoal;
				stateLock.unlock();
			}
			break;
		}
		case reachedGoal: {
			simState = idle;
			if (realGoal) {
				stateLock.unlock();
				std::cout << "Goal reached" << std::endl;
			} else {
				realGoal = true;
				stateLock.unlock();
				std::cout << "Goal out of reach" << std::endl;
			}
			std::cout << "Waiting for new goal" << std::endl;
			waitForNewGoal.lock();
			break;
		}
		case reachedMaxIte: {
			simState = idle;
			stateLock.unlock();
			std::cout << "Max iterations reached" << std::endl;
			std::cout << "Waiting for new goal" << std::endl;
			waitForNewGoal.lock();
			break;
		}
		case idle: {
			stateLock.unlock();
			std::cout << "Waiting for new goal" << std::endl;
			waitForNewGoal.lock();
			break;
		}
		case exitState: {
			stateLock.unlock();
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
	setSimState(exitState);
	waitForNewGoal.unlock();
	simulating = false;
	if (simulationThread.joinable()) {
		//Wait for the simulation thread to finish
		simulationThread.join();
	}
}

const glm::vec3& SimulationController::getGoal() const {
	return goal;
}

void SimulationController::setGoal(const glm::vec3& goal) {
	float goalDistance = glm::length(goal);
	stateLock.lock();
	if (!renderChain
			|| goalDistance < simSolver.getChain().getMaximumRadius()) {
		this->goal = goal;
		epsilon = 0.01;
	} else {
		//Out of reach goals can cause instabilities, set the goal to be within
		//reach and with high error threshold
		this->goal = (float) (0.99 * simSolver.getChain().getMaximumRadius())
				* glm::normalize(goal);
		realGoal = false;
		epsilon = 0.2;
	}

	numIterations = 0;
	if (simState != stepping) {
		waitForNewGoal.unlock();
	}

	simState = stepping;

	stateLock.unlock();

	chainDataLock.lock();
	simSolver.setGoal(this->goal);
	chainDataLock.unlock();
}

void SimulationController::startSimulation(ChainPtr chain) {

	//If thread was running stop it
	killSimulation();

	//Save chain pointer
	renderChain = chain;

	simSolver.setChain(*renderChain);

	//Run new thread with simulation loop
	simulating = true;
	setSimState(idle);
	waitForNewGoal.lock();

	simulationThread = std::thread(&SimulationController::executeSimulationLoop,
			this);
}

void SimulationController::updateChain() {
	chainDataLock.lock();
	if (renderChain) {
		for (unsigned int i = 0; i < simSolver.getChain().getNumJoints(); i++) {
			renderChain->setJointAngles(i,
					simSolver.getChain().getJointZAngle(i),
					simSolver.getChain().getJointYAngle(i));
		}
	}
	chainDataLock.unlock();
}

void SimulationController::setSimState(const SimulationState& simState) {
	stateLock.lock();
	this->simState = simState;
	stateLock.unlock();
}
