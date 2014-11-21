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

void SimulationSolver::setGoal(const glm::vec3& goal) {
	cGoal = goal;
	startPos = simulationChain.getEndEfectorPos();
	journey = glm::length(cGoal - startPos);
	journeyLower = journey * 0.2;
	journeyUpper = journey * 0.8;
	scaleFactor = initialSpeed;
}

void SimulationSolver::solveForStep(double stepSize) {
	if (simulationChain.getNumJoints() > 0) {
		resetWorkingChain();
		setCurrentSpeed();
		finiteDiffJacobian();
		updateAngles(stepSize);
	}
}

void SimulationSolver::resetWorkingChain() {
	for (unsigned int i = 0; i < wChain.getNumJoints(); i++) {
		wChain.setJointZAngle(i, simulationChain.getJointZAngle(i));
		wChain.setJointYAngle(i, simulationChain.getJointYAngle(i));
	}
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

void SimulationSolver::finiteDiffJacobian() {
	costVal = wChain.costFun(cGoal);

	unsigned int mid = jacobian.size() * 0.5;

	for (unsigned int i = 0; i < mid; i++) {
		wChain.setJointZAngle(i, wChain.getJointZAngle(i) + h);
		jacobian[i] = (1 / h) * (wChain.costFun(cGoal) - costVal);
		jacobian[i] = glm::normalize(jacobian[i]);
		wChain.setJointZAngle(i, wChain.getJointZAngle(i) - h);
	}

	for (unsigned int i = mid; i < jacobian.size(); i++) {
		wChain.setJointYAngle(i - mid, wChain.getJointYAngle(i - mid) + h);
		jacobian[i] = (1 / h) * (wChain.costFun(cGoal) - costVal);
		jacobian[i] = glm::normalize(jacobian[i]);
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

	unsigned int mid = jacobian.size() * 0.5;
	std::vector<double> normalizedAngles(jacobian.size(), 0);

	calculateAngleUpdates(mid, normalizedAngles);

	normalizeAngleUpdates(normalizedAngles);

	updateWorkingChain(mid, normalizedAngles, stepSize);

	updateSimulationChain();
}

void SimulationSolver::calculateAngleUpdates(unsigned int mid,
		std::vector<double>& normalizedAngles) {
	double angleUpdate;
	//Precalculate all angle updates
	for (unsigned int i = 0; i < mid; i++) {
		//Multiply jacobian inverse transpose by f(x), negative because
		//we want to go in negative gradient direction
		angleUpdate = glm::dot(-jacobian[i], costVal) * TO_DEG
				* wChain.getBoneStiffness(i);
		normalizedAngles.at(i) = angleUpdate;
	}
	for (unsigned int i = mid; i < jacobian.size(); i++) {
		angleUpdate = glm::dot(-jacobian[i], costVal) * TO_DEG
				* wChain.getBoneStiffness(i - mid);
		normalizedAngles.at(i) = angleUpdate;
	}
}

void SimulationSolver::normalizeAngleUpdates(
		std::vector<double>& normalizedAngles) {
	//Normalise the angle update
	double angleSum = 0;
	for (unsigned int i = 0; i < normalizedAngles.size(); i++) {
		angleSum += normalizedAngles.at(i) * normalizedAngles.at(i);
	}
	angleSum = 1.0 / std::sqrt(angleSum);
	for (unsigned int i = 0; i < normalizedAngles.size(); i++) {
		normalizedAngles.at(i) = normalizedAngles.at(i) * angleSum
				* scaleFactor;
	}
}

void SimulationSolver::updateWorkingChain(unsigned int mid,
		const std::vector<double>& normalizedAngles, double stepSize) {
	//If it is within the permitted values, update the angle
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

void SimulationSolver::updateSimulationChain() {
	for (unsigned int i = 0; i < wChain.getNumJoints(); i++) {
		simulationChain.setJointAngles(i, wChain.getJointZAngle(i),
				wChain.getJointYAngle(i));
	}
}

ChainModel& SimulationSolver::getChain() {
	return simulationChain;
}

void SimulationSolver::setChain(const ChainModel& simulationChain) {
	//wChain is a real copy of chain, not just another pointer to it
	this->simulationChain = simulationChain;
	wChain = this->simulationChain;
	jacobian.resize(this->simulationChain.getNumJoints() * 2);
}
