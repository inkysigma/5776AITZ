#pragma config(Sensor, in2,    LiftPot,        sensorPotentiometer)

#define Kp 1
#define Kd 0
#define Ki 0.001
#define dt 0.01

#include "motor.h"

int target = 0;
int isRunning = 0;


// holdLift holds the lift at a specific position using a PID loop.
task holdLift() {
	int INT_MAX = Kp * 30;
	int INT_MIN = Kp * 20;
	int integral = 0;
	int proportional = 0;
	int total = 0;
	while (!isRunning) {
		int error = SensorValue[LiftPot] - target;
		proportional = Kp * error;
		integral +=  Ki * error;
		if (integral > INT_MAX) {
			integral = INT_MAX;
		}
		else if (integral < INT_MIN) {
			integral = INT_MIN;
		}
		total = proportional + integral;
		moveLift(total);
		wait1Msec(20);
	}
}

void startPid(int t) {
	target = t;
	isRunning = 1;
	startTask(holdLift);
}

void stopPid() {
	isRunning = 0;
	stopTask(holdLift);
}


task main() {
}
