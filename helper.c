#include "motor.h"

void drive(int distance, int power, int waitTime) {
	int timer = 0;
	while (SensorValue[encLeft] < distance && timer < waitTime) {
		motor[left] = power;
		motor[right] = power;
		wait1Msec(20);
		timer += 20;
	}
}
