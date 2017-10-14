#include "corrector.c"

void moveDrive (int left, int right) {
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

void moveGoal(int power) {
	int output = getMogoCorrection(power);
	motor[LeftMobileGoal] = output;
	motor[RightMobileGoal] = -power;
}

void moveSwitchLift(int power) {
	motor[SwitchLift] = power;
}
