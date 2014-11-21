/*
 * SimulationHandler.h
 *
 *  Created on: 31 Oct 2014
 *      Author: garoe
 */

#ifndef SRC_SIMULATIONCONTROLLER_H_
#define SRC_SIMULATIONCONTROLLER_H_

#include <thread>
#include <chrono>
#include <mutex>
#include <iostream>

#include "SimulationSolver.h"

class SimulationController {
public:
	SimulationController();
	virtual ~SimulationController();

	//Launches new thread that will execute the simulation
	void startSimulation(ChainPtr chain);

	//Updates rendering Chain with the new simulated data
	void updateChain();

	void killSimulation();

	const glm::vec3& getGoal() const;
	void setGoal(const glm::vec3& goal);
private:
	//Method executed by the simulation thread
	void executeSimulationLoop();

	enum SimulationState {
		stepping, reachedGoal, reachedMaxIte, idle, exitState
	};

	void setSimState(const SimulationState& simState);
private:
	ChainPtr renderChain;

	SimulationSolver simSolver;

	std::thread simulationThread;
	//Lock to protect the chain data
	std::mutex chainDataLock;
	//Lock to sleep simulation thread until a new goal a set
	std::mutex waitForNewGoal;
	//Lock to protect simulation controller state
	std::mutex stateLock;
	std::chrono::milliseconds stepSleepTime;

	SimulationState simState;

	bool simulating;
	bool realGoal;
	glm::vec3 goal;
	unsigned int numIterations;
	unsigned int maxIterations;
	double stepSize;

	double epsilon;
};

typedef boost::shared_ptr<SimulationController> SimulationControllerPtr;

#endif /* SRC_SIMULATIONCONTROLLER_H_ */
