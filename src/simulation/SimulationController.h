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

#include "SimulationSolver.h"

class SimulationController {
public:
	SimulationController(double epsilon = 0.03);
	virtual ~SimulationController();

	void startSimulation(ChainPtr chain);

	void updateChain();

	void executeSimulationLoop();

	void killSimulation();

	const ChainPtr getChain() const;

	const glm::vec3& getGoal() const;
	void setGoal(const glm::vec3& goal);

private:
	ChainPtr chain;
	SimulationSolver simSolver;

	std::thread simulationThread;
	std::mutex lock;
	std::chrono::milliseconds sleepTime;
	std::chrono::milliseconds stepSleepTime;
	std::chrono::milliseconds idleSleepTime;

	enum SimulationState {
		stepping, reachedGoal, reachedMaxIte, idle
	};

	SimulationState simState;

	bool simulating;
	glm::vec3 goal;
	unsigned int numIterations;
	unsigned int maxIterations;

	double epsilon;
};

#endif /* SRC_SIMULATIONCONTROLLER_H_ */
