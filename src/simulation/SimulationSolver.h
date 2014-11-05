/*
 * SimulationSolver.h
 *
 *  Created on: 30 Oct 2014
 *      Author: garoe
 */

#ifndef SRC_SIMULATIONSOLVER_H_
#define SRC_SIMULATIONSOLVER_H_

#include "../models/Chain.h"

class SimulationSolver {
public:
	SimulationSolver();
	virtual ~SimulationSolver();

	//TODO Include here the Jacobian Solver
	void solveForStep(ChainPtr chain, const glm::vec3 goal);
};

#endif /* SRC_SIMULATIONSOLVER_H_ */
