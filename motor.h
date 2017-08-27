#ifndef MOTOR_H
#define MOTOR_H
void moveDrive (int left, int right) {
	motor[LeftDrive] = left;
	motor[RightDrive] = -right;
}

void moveLift (int power) {
	motor[TopLift] = power;
	motor[BottomLift] = power;
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
	motor[LeftMobileGoal] = power;
	motor[RightMobileGoal] = -power;
}
#endif
