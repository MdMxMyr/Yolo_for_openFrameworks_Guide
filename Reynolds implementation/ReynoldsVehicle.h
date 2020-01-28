#pragma once

#include "ofMain.h"
#include <algorithm>  


class ReynoldsVehicle: public ofBaseApp {

public:
	// Creates a Reynold's Vehicle at specified location (default = the centre of the screen)
	void setupVehicle();
	void setupVehicle(int x, int y);
	void setupVehicle(glm::vec2 initPos);

	// Vehicle location SETTER
	void setVehiclePos(int x, int y);
	void setVehiclePos(glm::vec2 newPos);
	// Vehicle location GETTER
	glm::vec2 getVehiclePos();

	// Set's the position of the target (e.g., estimated eye-gaze location)
	void setTargetPos(int x, int y);
	void setTargetPos(glm::vec2 newTarget);
	glm::vec2 getTargetPos();

	glm::vec2 calcDesired();
	glm::vec2 calcSteer();

	// Calculate the attraction of a Yolo-Bounding-Box (or other rectangle) w.r.t to the Vehicle's position
	glm::vec2 calcAttraction(ofRectangle i);
	glm::vec2 calcAttraction(int x, int y, int w, int h);

	// Step fuctions for actually moving the vehicle, called in update once for every step
	void applyForce(glm::vec2 force);
	void updateVehicle();
	void vehicleTick();

	glm::vec2 pos = glm::vec2(0, 0);
	glm::vec2 vel = glm::vec2(0, 0);
	glm::vec2 acc = glm::vec2(0, 0);
	glm::vec2 target = glm::vec2(0, 0);

	// Helper functions
	int calcDistanceToAttraction(ofRectangle i);
	int calcDistanceToAttraction(int x, int y, int w, int h);

	bool isSmallerDistance(const ofRectangle& i, const ofRectangle& j);
	bool vehicleInZone(ofRectangle i);
	bool vehicleInZone(int x, int y, int w, int h);

	// Demo is slow on purpose so that behaviors can be observed more easily
	// Increase these values for a more realistic effect
	int maxVel = 15;
	int maxF = 15;

	void draw();
	void drawVehicle();
	void drawTarget();
	void drawDesired();
	void drawSteer();

	bool debug = true;
};