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

#include "SimulationSolver.h"

class SimulationController {
public:
	SimulationController();
	virtual ~SimulationController();

	void startSimulation(ChainPtr chain);

	void executeSimulationLoop();

	void killSimulation();

	const ChainPtr getChain() const;

	const glm::vec3& getGoal() const;
	void setGoal(const glm::vec3& goal);

private:
	ChainPtr chain;
	SimulationSolver simSolver;
	std::thread simulationThread;
	bool simulating;
	glm::vec3 goal;
	std::chrono::milliseconds simSleepTime;
};

#endif /* SRC_SIMULATIONCONTROLLER_H_ */
