/*
 * SimulationSolver.cpp
 *
 *  Created on: 30 Oct 2014
 *      Author: garoe
 */

#include "SimulationSolver.h"

SimulationSolver::SimulationSolver(float h) {
	this->h = h;
	wChain = NULL;
}

SimulationSolver::~SimulationSolver() {
	delete wChain;
}

void SimulationSolver::solveForStep(const glm::vec3 goal) {
	if (chain) {
		//Dummy example, rotate a joint
		chain->setJointAngle(2, chain->getJointAngle(2) + 1);
		glm::vec3 endPos = chain->getEndEfectorPos();
		//std::cout << "end pos " << endPos.x << ", " << endPos.y << std::endl;
		finiteDiffJacobian(goal);
	}
}

void SimulationSolver::intialize(ChainPtr chain) {
	this->chain = chain;
	wChain = new Chain((*chain.get()));
	jacobian.resize(chain->getNumJoints());
}

void SimulationSolver::resetWorkingChain() {
	for (unsigned int i = 0; i < chain->getNumJoints(); i++) {
		wChain->setJointAngle(i, chain->getJointAngle(i));
	}
}

void SimulationSolver::finiteDiffJacobian(const glm::vec3& goal) {

	resetWorkingChain();
	glm::vec3 costVal = wChain->costFun(goal);

	for (unsigned int i = 0; i < jacobian.size(); i++) {
		wChain->setJointAngle(i, wChain->getJointAngle(i) + h);
		jacobian[i] = (1 / h) * (wChain->costFun(goal) - costVal);
	}
}

float SimulationSolver::getH() const {
	return h;
}

void SimulationSolver::setH(float h) {
	this->h = h;
}
