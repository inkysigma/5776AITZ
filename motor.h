#include "corrector.c"
const OUT_ANGLE = 90;
const IN_ANGLE = 0;
const FAST_SPEED = 100;
const SLOW_ANGLE = 45;
const SLOW_SPEED = 50
const SYNC_SPEED = 15;
void moveDrive(int left, int right) {
	motor[LeftDrive] = left;
	motor[RightDrive] = -right;
}

void rotateDrive(int speed) {
	motor[LeftDrive] = speed;
	motor[RightDrive] = speed;
}

void moveLeftLift(int power) {
	motor[LeftLift] = power;
}

void moveRightLift(int power) {
	motor[RightLift] = -power;
}

void moveLift (int power) {
	motor[LeftLift] = power;
	motor[RightLift] = -power;
}

void moveRight(int power) {
	motor[RightLift] = -power;
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

}
void closeClawFully() {

}
void moveClawForward() {

}
void moveLiftTo(int target) {

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
