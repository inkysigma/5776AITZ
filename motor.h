void moveDrive (int left, int right) {
	motor[LeftDrive] = left;
	motor[RightDrive] = -right;
}

void moveLeftLift(int power) {
	motor[LeftLift] = -power;
}

void moveRightLift(int power) {
	motor[RightLift] = power;
}

void moveLift (int power) {
	motor[LeftLift] = -power;
	motor[RightLift] = power;
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

void moveSwitchLift(int power) {
	motor[SwitchLift] = power;
}
