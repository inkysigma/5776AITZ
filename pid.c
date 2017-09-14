#pragma config(Sensor, in2,    LiftPot,        sensorPotentiometer)

#define Kp 1
#define Kd 0
#define Ki 0.001
#define dt 0.01

#include "motor.h"

int target = 0;
int isRunning = 0;

typedef struct {
	float kp;
	float kd;
	float ki;
	float dt;
} pid;

pid liftConfig;


// holdLift holds the lift at a specific position using a PID loop.
task holdLift() {
	int INT_MAX = liftConfig.kp * 30;
	int INT_MIN = liftConfig.kp * 20;
	int integral = 0;
	int proportional = 0;
	int total = 0;
	while (!isRunning) {
		int error = SensorValue[LiftPot] - target;
		proportional = liftConfig.kp * error;
		integral += liftConfig.ki * error;
		if (integral > INT_MAX) {
			integral = INT_MAX;
		}
		else if (integral < INT_MIN) {
			integral = INT_MIN;
		}
		total = proportional + integral;
		moveLift(total);
		wait1Msec(liftConfig.dt);
	}
}

void startPid(int t, pid config) {
	target = t;
	isRunning = 1;
	liftConfig = config;
	startTask(holdLift);
}

void stopPid() {
	isRunning = 0;
	stopTask(holdLift);
}


task main() {
}
