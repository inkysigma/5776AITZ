#include "sensors.h"

#define LEVEL_CHANGE 30

void moveSwitchLift(int power);

void moveDrive(int left, int right) {
	motor[LeftDrive] = left;
	motor[RightDrive] = -right;
}

void rotateDrive(int speed) {
	motor[LeftDrive] = speed;
	motor[RightDrive] = speed;
}

void moveLeftLift(int power) {
	motor[LeftLift] = -power;
}

void moveRightLift(int power) {
	motor[RightLift] = power;
}

void moveLift(int power) {
	moveLeftLift(power);
	moveRightLift(power);
}

void openClaw(int power) {
	motor[Claw] = -power;
}

void closeClaw(int power) {
	openClaw(-power);
}

void stopClaw() {
	openClaw(0);
}

int prevOutwardState = 1;

void lowerClaw(int power) {
	// move the switch lift until it rotates the other way
  moveSwitchLift(power);
}

void raiseClaw(int power) {
	moveSwitchLift(-power);
}

void moveLeftMogo(int power) {
	motor[LeftMobileGoal] = -power;
}

void moveRightMogo(int power) {
	motor[RightMobileGoal] = power;
}

void moveGoal(int power) {
	moveLeftMogo(power);
	moveRightMogo(power);
}

void moveSwitchLift(int power) {
	motor[SwitchLift] = -power;
}


void applyStall() {
	moveLift(15);
}
