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
		jacobian.resize(chain->getNumJoints());
	} else {
		wChain.clear();
	}
}

void SimulationSolver::resetWorkingChain() {
	for (unsigned int i = 0; i < chain->getNumJoints(); i++) {
		wChain.setJointAngle(i, chain->getJointAngle(i));
	}
}

void SimulationSolver::finiteDiffJacobian(const glm::vec3& goal) {

	resetWorkingChain();
	costVal = wChain.costFun(goal);

	for (unsigned int i = 0; i < jacobian.size(); i++) {
		wChain.setJointAngle(i, wChain.getJointAngle(i) + h);
		jacobian[i] = (1 / h) * (wChain.costFun(goal) - costVal);
		jacobian[i] = (1 / glm::length(jacobian[i])) * jacobian[i];
		wChain.setJointAngle(i, wChain.getJointAngle(i) - h);
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
	for (unsigned int i = 0; i < jacobian.size(); i++) {
		angleUpdate = glm::dot(-jacobian[i], costVal) * TO_DEG * stepSize;
		chain->setJointAngle(i, chain->getJointAngle(i) + angleUpdate);
	}
}
