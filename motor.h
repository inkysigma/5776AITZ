#include "corrector.c"
#include "sensors.h"

const int OUT_ANGLE = 90;
const int IN_ANGLE = 0;
const int FAST_SPEED = 100;
const int SLOW_ANGLE = 45;
const int SLOW_SPEED = 50;
const int SYNC_SPEED = 15;

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

void syncMogo() {
	while (SensorValue[MogoRightPot] > IN_ANGLE && SensorValue[MogoLeftPot] > IN_ANGLE) {
		if (SensorValue[MogoRightPot] > IN_ANGLE) {
			motor[RightMobileGoal] = -SYNC_SPEED;
		} else {
			motor[RightMobileGoal] = 0;
		}
		if (SensorValue[MogoLeftPot] > IN_ANGLE) {
			motor[LeftMobileGoal] = -SYNC_SPEED;
		} else {
			motor[LeftMobileGoal] = 0;
		}
	}
}

void moveMogoOut() {
	while (SensorValue[MogoRightPot] < SLOW_ANGLE) {
		motor[RightMobileGoal] = SLOW_SPEED;
	}
	while (SensorValue[MogoRightPot] > OUT_ANGLE) {
		motor[RightMobileGoal] = FAST_SPEED;
	}
}

void moveMogoIn() {
	while (SensorValue[MogoRightPot] > IN_ANGLE) {
		moveRightMogo(-FAST_SPEED);
		moveLeftMogo(FAST_SPEED);
	}
	moveRightMogo(0);
	moveLeftMogo(0);
}
