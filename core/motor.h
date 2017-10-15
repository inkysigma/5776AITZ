#include "sensors.h"


#define CLAW_TIME 2000
#define SWITCH_TIME 2000
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

void moveLift (int power) {
	moveLeftLift(power);
	moveRightLift(power);
}


void openClaw(int power) {
	motor[Claw] = power;
}

void closeClaw(int power) {
	openClaw(-power);
}

void stopClaw() {
	openClaw(0);
}

void openClawFully() {
	int d = 0;
	openClaw(40);
	while (d < CLAW_TIME) {
		delay(20);
		d += 20;
	}
}

void closeClawFully() {
	// using timing for now
	int d = 0;
	openClaw(-40);
	while (d < CLAW_TIME) {
		wait1MSec(20);
		d += 20;
	}
}

bool prevOutwardState = 1;

void switchClaw() {
	// move the switch lift until it rotates the other way
	int delay = 0;
	moveSwitchLift(prevOutwardState * 100);
	while (delay < SWITCH_TIME) {
		wait1Msec(20);
		delay += 20;
	}
	prevOutwardState = -prevOutwardState;
}

void moveLeftMogo(int power) {
	int output = getMogoCorrection(power);
	motor[LeftMobileGoal] = output;
}

void moveRightMogo(int power) {
	motor[RightMobileGoal] = power;
}

void moveGoal(int power) {
	moveLeftMogo(power);
	moveRightMogo(-power);
}

void moveSwitchLift(int power) {
	motor[SwitchLift] = power;
}


void applyStall() {
	moveRightLift(10);
	moveLeftLift(10);
}

