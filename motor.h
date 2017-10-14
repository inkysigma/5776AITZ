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

void openClawFully();
void closeClawFully();

void moveGoal(int power) {
	int output = getMogoCorrection(power);
	motor[LeftMobileGoal] = output;
	motor[RightMobileGoal] = -power;
}

void moveSwitchLift(int power) {
	motor[SwitchLift] = power;
}

void switch_mogo() {
	moveMobileGoal(80);
	while (SensorValue[
}
