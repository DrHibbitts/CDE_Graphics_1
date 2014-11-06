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
	SimulationSolver(float h = 0.01);

	virtual ~SimulationSolver();

	void intialize(ChainPtr chain);

	void solveForStep(const glm::vec3 goal);

	float getH() const;
	void setH(float h);

private:
	void finiteDiffJacobian(const glm::vec3& goal);
	void resetWorkingChain();

	ChainPtr chain;
	Chain *wChain;
	std::vector<glm::vec3> jacobian;
	float h;
};

#endif /* SRC_SIMULATIONSOLVER_H_ */
