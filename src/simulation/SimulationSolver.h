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

	void solveForStep(const glm::vec3 goal, double stepSize = 0.034);

	void setChain(ChainPtr chain);

	void updateChain();

	float getH() const;
	void setH(float h);

private:
	void finiteDiffJacobian();
	void resetWorkingChain();
	void updateAngles(double stepSize);
	void setCurrentSpeed();
	void setGoal(const glm::vec3& goal);

	ChainPtr chain;
	ChainModel wChain;

	std::vector<glm::vec3> jacobian;
	float h;
	double scaleFactor;
	double journey;
	double journeyLower;
	double journeyUpper;
	double maxSpeed;
	double initialSpeed;
	glm::vec3 costVal;
	glm::vec3 cGoal;
	glm::vec3 startPos;
};

#endif /* SRC_SIMULATIONSOLVER_H_ */
