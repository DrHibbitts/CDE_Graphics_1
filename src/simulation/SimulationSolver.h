/*
 * SimulationSolver.h
 *
 *  Created on: 30 Oct 2014
 *      Author: garoe
 */

#ifndef SRC_SIMULATIONSOLVER_H_
#define SRC_SIMULATIONSOLVER_H_

#include "../rendering/drawables/Chain.h"
#include "../models/ChainModel.h"

class SimulationSolver {
public:
	SimulationSolver(float h = 0.01);

	virtual ~SimulationSolver();

	void solveForStep(const glm::vec3 goal, double stepSize = 0.00001);

	void setChain(ChainPtr chain);

	void updateChain();

	float getH() const;
	void setH(float h);

private:
	void finiteDiffJacobian(const glm::vec3& goal);
	void resetWorkingChain();
	void updateAngles(double stepSize);

	ChainPtr chain;
	ChainModel wChain;

	std::vector<glm::vec3> jacobian;
	float h;
	double scaleFactor;
	glm::vec3 costVal;
};

#endif /* SRC_SIMULATIONSOLVER_H_ */
