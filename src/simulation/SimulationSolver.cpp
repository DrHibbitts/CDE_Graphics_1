/*
 * SimulationSolver.cpp
 *
 *  Created on: 30 Oct 2014
 *      Author: garoe
 */

#include "SimulationSolver.h"

SimulationSolver::SimulationSolver() {
	wChain = NULL;
}

SimulationSolver::~SimulationSolver() {
}

void SimulationSolver::solveForStep(ChainPtr chain, const glm::vec3& goal) {
	if (chain) {
		//Dummy example, rotate a joint
		chain->setJointAngle(2, chain->getJointAngle(2) + 1);
	}
}
