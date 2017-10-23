#include "motor.h"

int leftInit = 0;
int rightInit = 0;

void setInit(int left, int right) {
	leftInit = left;
	rightInit = right;
}

int getLeftPot() {
	return SensorValue[LeftLiftPot] - leftInit;
}

int getRightPot() {
	return SensorValue[RightLiftPot] - rightInit;
}


int mobileGoalLeftInit = 0;
int mobileGoalRightInit = 0;

void setMobileGoalInit(int left, int right) {
	mobileGoalLeftInit = left;
	mobileGoalRightInit = right;
}

int getLeftMobilePot() {
	return SensorValue[MogoLeftPot] - mobileGoalLeftInit;
}

int getRightMobilePot() {
	return SensorValue[MogoRightPot] - mobileGoalRightInit;
}
