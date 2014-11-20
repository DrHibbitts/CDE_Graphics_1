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
}

SimulationSolver::~SimulationSolver() {
}

void SimulationSolver::solveForStep(const glm::vec3 goal, double stepSize) {
	if (chain) {
		finiteDiffJacobian(goal);
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

void SimulationSolver::finiteDiffJacobian(const glm::vec3& goal) {

	resetWorkingChain();
	costVal = wChain.costFun(goal);

	unsigned int mid = jacobian.size() * 0.5;

	for (unsigned int i = 0; i < mid; i++) {
		wChain.setJointZAngle(i, wChain.getJointZAngle(i) + h);
		jacobian[i] = (1 / h) * (wChain.costFun(goal) - costVal);
		jacobian[i] = (1 / glm::length(jacobian[i])) * jacobian[i];
		wChain.setJointZAngle(i, wChain.getJointZAngle(i) - h);
	}

	for (unsigned int i = mid; i < jacobian.size(); i++) {
		wChain.setJointYAngle(i - mid, wChain.getJointYAngle(i - mid) + h);
		jacobian[i] = (1 / h) * (wChain.costFun(goal) - costVal);
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

	for (unsigned int i = 0; i < mid; i++) {
		angleUpdate = glm::dot(-jacobian[i], costVal) * TO_DEG * stepSize;
		double nextZAngle = wChain.getJointZAngle(i) + angleUpdate;

		if (nextZAngle < wChain.getMaxZ() && nextZAngle > wChain.getMinZ()) {
			wChain.setJointZAngle(i, nextZAngle);
		}

	}

	for (unsigned int i = mid; i < jacobian.size(); i++) {
		angleUpdate = glm::dot(-jacobian[i], costVal) * TO_DEG * stepSize;
		double nextYAngle = wChain.getJointYAngle(i - mid) + angleUpdate;

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
