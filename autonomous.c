#include "core/motor.h"

bool isKill(int current, int target, int time, int max) {
	if (abs(current) < target && time > max) {
		return true;
	}
	return false;
}

void pickUpCone(int level) {
}

void rotate(int degrees) {
	// Remember to scale the degree value by 1000
	degrees *= 1000;
	int first_pause = degrees * 0.6;
	int second_pause = degrees * 0.75;
	int third_pause = degrees * 0.9;
	while (SensorValue[gyro] < first_pause) {
		rotateDrive(sgn(degrees) * 100);
	}

	while (SensorValue[gyro] < second_pause) {
		rotateDrive(sgn(degrees) * 70);
	}

	while (SensorValue[gyro] < third_pause) {
		rotateDrive(sgn(degrees) * 50);
	}

	while (SensorValue[gyro] < degrees) {
		rotateDrive(sgn(degrees) * 10);
	}
	rotateDrive(0);
}

void setDrive(int ticks) {
	SensorValue[RightEncoder] = 0;
	SensorValue[LeftEncoder] = 0;
	int timePassed = 0;
	while ((abs(SensorValue[RightEncoder]) < 0.7 * ticks) &&
		!isKill(SensorValue[RightEncoder], ticks, timePassed, 2500)) {
		moveDrive(100, 100);
		delay(20);
		timePassed += 20;
	}
	moveDrive(0, 0);

	while (abs(SensorValue[RightEncoder]) < 0.8 * ticks &&
		!isKill(SensorValue[RightEncoder], ticks, timePassed, 2500)) {
		moveDrive(70, 70);
		delay(20);
		timePassed += 20;
	}

	while (abs(SensorValue[RightEncoder]) < ticks &&
		!isKill(SensorValue[RightEncoder], ticks, timePassed, 2500)) {
		moveDrive(10, 10);
		delay(20);
		timePassed += 20;
	}
	moveDrive(0, 0);
}

void pickUpMobileGoal() {
}

void putDownMobileGoal() {
}


void auto() {
	// TODO: Implement the actual methods and find the associated values
	int ticks = 0;

	// NOTE: Don't use tile. Apparently is inaccurate to convert due to momentum and inertia
	setDrive(ticks);
	rotate(90);
	pickUpCone(0);
	rotate(-90);
	setDrive(ticks);
	rotate(90);
	setDrive(ticks);
	rotate(90);
	pickUpMobileGoal();
	setDrive(ticks);
	rotate(90);
	pickUpCone(1);
	setDrive(ticks);
	pickUpCone(2);
	setDrive(ticks);
	rotate(-90);
	setDrive(ticks);
	rotate(45);
	setDrive(ticks);
	putDownMobileGoal();
}

void auto2() {
	int ticks;

	setDrive(ticks);
	rotate(90);
	setDrive(ticks);
	rotate(90);
	setDrive(ticks);
	pickUpMobileGoal();
	rotate(90);
	setDrive(ticks);
	pickUpCone(0);
	setDrive(ticks);
	pickUpCone(1);
	rotate(-90);
	setDrive(ticks);
	pickUpCone(2);
	rotate(90);
	setDrive(ticks);
	rotate(-90);
	setDrive(ticks);
	rotate(45);
	setDrive(ticks);
	putDownMobileGoal();
}
