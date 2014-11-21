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

	void setGoal(const glm::vec3& goal);

	void solveForStep(double stepSize);

	float getH() const;
	void setH(float h);

	ChainModel& getChain();
	void setChain(const ChainModel& simulationChain);

private:
	void finiteDiffJacobian();
	void resetWorkingChain();

	void setCurrentSpeed();

	void updateAngles(double stepSize);

	void calculateAngleUpdates(unsigned int mid,
			std::vector<double>& normalizedAngles);

	void normalizeAngleUpdates(std::vector<double>& normalizedAngles);

	void updateWorkingChain(unsigned int mid,
			const std::vector<double>& normalizedAngles, double stepSize);

	void updateSimulationChain();

	ChainModel simulationChain;
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
