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
