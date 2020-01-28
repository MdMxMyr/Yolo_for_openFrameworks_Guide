#include "ReynoldsVehicle.h"



void ReynoldsVehicle::setupVehicle() {
	setVehiclePos((int) ofGetWindowWidth() / 2, (int) ofGetWindowHeight() / 2);
	return;
}

void ReynoldsVehicle::setupVehicle(int x, int y) {
	setVehiclePos(glm::vec2(x, y));
	return;
}

void ReynoldsVehicle::setupVehicle(glm::vec2 initPos) {
	setVehiclePos(initPos);
	return;
}

void ReynoldsVehicle::setVehiclePos(int x, int y) {
	setVehiclePos(glm::vec2(x, y));
	return;
}

void ReynoldsVehicle::setVehiclePos(glm::vec2 newPos) {
	pos = newPos;
	return;
}

glm::vec2 ReynoldsVehicle::getVehiclePos() {
	return pos;
}



void ReynoldsVehicle::setTargetPos(int x, int y) {
	setTargetPos(glm::vec2(x, y));
	return;
}

void ReynoldsVehicle::setTargetPos(glm::vec2 newTarget) {
	target = newTarget;
	return;
}

glm::vec2 ReynoldsVehicle::getTargetPos() {
	return target;
}


glm::vec2 ReynoldsVehicle::calcDesired() {
	glm::vec2 desired = target - pos;
	return desired;
}

int ReynoldsVehicle::calcDistanceToAttraction(ofRectangle i) {
	return calcDistanceToAttraction((int)i.x, (int)i.y, (int)i.width, (int)i.height);
}

int ReynoldsVehicle::calcDistanceToAttraction(int x, int y, int w, int h) {
	glm::vec2 centerPoint = glm::vec2((int)x + w / 2, (int)y + h / 2);
	glm::vec2 desired_to_target = centerPoint - target;
	return (int) glm::length(desired_to_target);
}

bool ReynoldsVehicle::isSmallerDistance(const ofRectangle& i, const ofRectangle& j) {
	return calcDistanceToAttraction(i) < calcDistanceToAttraction(j);
}

bool ReynoldsVehicle::vehicleInZone(ofRectangle i) {
	return vehicleInZone((int)i.x, (int)i.y, (int)i.width, (int)i.height);
}

bool ReynoldsVehicle::vehicleInZone(int x, int y, int w, int h) {
	if ((pos.x >= x) && (pos.x <= x + w)
		&& (pos.y >= y) && (pos.y <= y + h)) {
		return true;
	}
	else {
		return false;
	}
}

glm::vec2 ReynoldsVehicle::calcSteer() {
	glm::vec2 desired = calcDesired();
	if (debug) cout << "vehicle desired pre: " << desired << "\n";

	int distance = glm::length(glm::vec2(desired.x, desired.y));

	if (debug) cout << "distance to target: " << distance << "\n";

	if (distance <= 1) {
		return glm::vec2(0, 0);
	}
	
	int speed = maxVel;
	if (distance < 100) {
		speed = (int) ofMap(distance, 0, 100, 0, maxVel);
	} 

	if (debug) cout << "vehicle speed: " << speed << "\n";

	desired = glm::normalize(glm::vec2(desired.x, desired.y));
	if (debug) cout << "normalized desire " << desired << "\n";
	desired *= speed;

	glm::vec2 steer = desired - vel;
	if (debug) cout << "steer: " << steer << " = desired " << desired << " - velocity " << vel << "\n";

	steer = glm::vec2( (int) std::min((int)steer.x, maxF), (int) std::min((int)steer.y, maxF));
	return steer;
}

glm::vec2 ReynoldsVehicle::calcAttraction(ofRectangle i) {
	return calcAttraction((int)i.x, (int)i.y, (int)i.width, (int)i.height);
}

glm::vec2 ReynoldsVehicle::calcAttraction(int x, int y, int w, int h) {
	glm::vec2 centerPoint = glm::vec2((int) x + w / 2, (int) y + h / 2);
	glm::vec2 desired_to_target = centerPoint - target;
	int distance = glm::length(desired_to_target);

	int avg_r = (w + h) / 2;
	int compensated_avg_r = avg_r * (1.4 - ofMap(avg_r, ofGetWindowWidth()*0.05, ofGetWindowWidth()*0.2, 0, 0.4));

	if (distance < compensated_avg_r * 0.5 && distance > avg_r * 0.4) {
		glm::vec2 desired_to_vehicle = centerPoint - pos;

		ofSetColor(0, 0, 255);
		if (debug) ofDrawLine(pos.x, pos.y, centerPoint.x, centerPoint.y);

		desired_to_vehicle = glm::normalize(desired_to_vehicle);
		desired_to_vehicle *= (int) ofMap(distance, 0, 100, 0, maxVel);;
		glm::vec2 steer = desired_to_vehicle - vel;
		steer = glm::vec2( (int) std::min((int)steer.x, maxF), (int) std::min((int)steer.y, maxF));
		return steer;
	}
	else {
		return glm::vec2((int) 0, (int) 0);
	}
}

void ReynoldsVehicle::applyForce(glm::vec2 force) {
	if (debug) cout << "applying f " << force << "\n";
	acc += force;
	return;
}

void ReynoldsVehicle::updateVehicle() {
	glm::vec2 steer = calcSteer();
	applyForce(steer);

	pos += vel;
	vel += acc;
	acc = glm::vec2(0, 0);

	return;
}

void ReynoldsVehicle::vehicleTick() {
	glm::vec2 steer = calcSteer();
	applyForce(steer);
	updateVehicle();
}


void ReynoldsVehicle::draw() {
	drawVehicle();

	if (debug) {
		drawTarget();
		drawDesired();
		drawSteer();
		cout << getVehiclePos() << " " << calcDesired() << "\n";
		cout << getTargetPos() << "\n";
		return;
	}

}

void ReynoldsVehicle::drawVehicle() {
	glm::vec2 v_pos = getVehiclePos();
	ofSetColor(255, 255, 255);
	ofDrawCircle(v_pos.x, v_pos.y, 20);
	return;
}

void ReynoldsVehicle::drawTarget() {
	glm::vec2 t_pos = getTargetPos();
	ofSetColor(0, 255, 0);
	ofDrawLine(t_pos.x, 0, t_pos.x, ofGetWindowHeight());
	ofDrawLine(0, t_pos.y, ofGetWindowWidth(), t_pos.y);
	return;
}

void ReynoldsVehicle::drawDesired() {
	glm::vec2 v_pos = getVehiclePos();
	glm::vec2 desired = calcDesired();
	ofSetColor(0, 0, 255);
	ofDrawLine(v_pos.x, v_pos.y, v_pos.x + desired.x, v_pos.y + desired.y);
	return;
}

void ReynoldsVehicle::drawSteer() {
	glm::vec2 v_pos = getVehiclePos();
	glm::vec2 steer = calcSteer();
	ofSetColor(100, 255, 100);
	ofDrawLine(v_pos.x, v_pos.y, v_pos.x + steer.x, v_pos.y + steer.y);
	return;
}
