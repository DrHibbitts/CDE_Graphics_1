/*
 * SimulationSolver.cpp
 *
 *  Created on: 30 Oct 2014
 *      Author: garoe
 */

#include "SimulationSolver.h"

#define TO_DEG  180.0 / M_PI

SimulationSolver::SimulationSolver(float h) {
	this->h = h;
	scaleFactor = 1;
	journey = 0;
	journeyLower = 0;
	journeyUpper = 0;
	maxSpeed = 2;
	initialSpeed = 0.2;
}

SimulationSolver::~SimulationSolver() {
}

void SimulationSolver::setCurrentSpeed() {
	double currentDistance = journey
			- glm::length(cGoal - wChain.getEndEfectorPos());
	if (currentDistance < journeyLower) {
		scaleFactor = currentDistance
				* ((maxSpeed - initialSpeed) * 5 / journey) + initialSpeed;
	} else if (currentDistance < journeyUpper) {
		scaleFactor = maxSpeed;
	} else {
		scaleFactor = currentDistance * (-5 / journey) + initialSpeed + 5;
	}
}

void SimulationSolver::setGoal(const glm::vec3& goal) {
	cGoal = goal;
	startPos = wChain.getEndEfectorPos();
	journey = glm::length(cGoal - startPos);
	journeyLower = journey * 0.2;
	journeyUpper = journey * 0.8;
	scaleFactor = 1;
}

void SimulationSolver::solveForStep(const glm::vec3 goal, double stepSize) {
	if (chain) {
		if (cGoal != goal) {
			setGoal(goal);
		}
		setCurrentSpeed();
		finiteDiffJacobian();
		updateAngles(stepSize);
	}
}

void SimulationSolver::setChain(ChainPtr chain) {
	this->chain = chain;

	if (chain) {
		//wChain is a real copy of chain, not just another pointer to it
		chain->copyToModel(wChain);
		jacobian.resize(chain->getNumJoints() * 2);
	} else {
		wChain.clear();
	}
}

void SimulationSolver::resetWorkingChain() {
	for (unsigned int i = 0; i < wChain.getNumJoints(); i++) {
		wChain.setJointZAngle(i, chain->getJointZAngle(i));
	}
}

void SimulationSolver::finiteDiffJacobian() {

	resetWorkingChain();
	costVal = wChain.costFun(cGoal);

	unsigned int mid = jacobian.size() * 0.5;

	for (unsigned int i = 0; i < mid; i++) {
		wChain.setJointZAngle(i, wChain.getJointZAngle(i) + h);
		jacobian[i] = (1 / h) * (wChain.costFun(cGoal) - costVal);
		jacobian[i] = (1 / glm::length(jacobian[i])) * jacobian[i];
		wChain.setJointZAngle(i, wChain.getJointZAngle(i) - h);
	}

	for (unsigned int i = mid; i < jacobian.size(); i++) {
		wChain.setJointYAngle(i - mid, wChain.getJointYAngle(i - mid) + h);
		jacobian[i] = (1 / h) * (wChain.costFun(cGoal) - costVal);
		jacobian[i] = (1 / glm::length(jacobian[i])) * jacobian[i];
		wChain.setJointYAngle(i - mid, wChain.getJointYAngle(i - mid) - h);
	}
}

float SimulationSolver::getH() const {
	return h;
}

void SimulationSolver::setH(float h) {
	this->h = h;
}

void SimulationSolver::updateAngles(double stepSize) {

	double angleUpdate;
	unsigned int mid = jacobian.size() * 0.5;

	std::vector<double> normalizedAngles(jacobian.size(), 0);

	//Precalculate all angle updates
	for (unsigned int i = 0; i < mid; i++) {
		angleUpdate = glm::dot(-jacobian[i], costVal) * TO_DEG
				* wChain.getBoneStiffness(i);
		normalizedAngles.at(i) = angleUpdate;
	}

	for (unsigned int i = mid; i < jacobian.size(); i++) {
		angleUpdate = glm::dot(-jacobian[i], costVal) * TO_DEG
				* wChain.getBoneStiffness(i - mid);
		normalizedAngles.at(i) = angleUpdate;
	}

	//Normalise
	double angleSum = 0;
	for (unsigned int i = 0; i < normalizedAngles.size(); i++) {
		angleSum += normalizedAngles.at(i) * normalizedAngles.at(i);
	}

	angleSum = 1.0 / std::sqrt(angleSum);

	for (unsigned int i = 0; i < normalizedAngles.size(); i++) {
		normalizedAngles.at(i) = normalizedAngles.at(i) * angleSum
				* scaleFactor;
	}

	//Actual update
	for (unsigned int i = 0; i < mid; i++) {
		double nextZAngle = wChain.getJointZAngle(i)
				+ normalizedAngles.at(i) * stepSize;
		if (nextZAngle < wChain.getMaxZ() && nextZAngle > wChain.getMinZ()) {
			wChain.setJointZAngle(i, nextZAngle);
		}
	}

	for (unsigned int i = mid; i < jacobian.size(); i++) {
		double nextYAngle = wChain.getJointYAngle(i - mid)
				+ normalizedAngles.at(i) * stepSize;
		if (nextYAngle < wChain.getMaxY() && nextYAngle > wChain.getMinY()) {
			wChain.setJointYAngle(i - mid, nextYAngle);
		}
	}
}

void SimulationSolver::updateChain() {
	if (chain) {
		for (unsigned int i = 0; i < wChain.getNumJoints(); i++) {
			chain->setJointAngles(i, wChain.getJointZAngle(i),
					wChain.getJointYAngle(i));
		}
	}
}
