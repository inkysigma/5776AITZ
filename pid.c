#pragma config(Sensor, in2,    LiftPot,        sensorPotentiometer)
#include "motor.h"

int target = 0;
bool isRunning = false;

typedef struct {
	float kp;
	float kd;
	float ki;
	float dt;
} pid;

pid liftConfig;
int leftTarget = 0;
int rightTarget = 0;


// holdLift holds the lift at a specific position using a PID loop.
task holdLeftLift() {
	int INT_MAX = 127;
	int INT_MIN = -127;
	float integral = 0;
	int proportional = 0;
	while (isRunning) {
		int error = SensorValue[LeftLiftPot] - leftTarget;
		proportional = liftConfig.kp * error;
		integral += liftConfig.ki * error * liftConfig.dt;
		if (integral > INT_MAX) {
			integral = INT_MAX;
		}
		else if (integral < INT_MIN) {
			integral = INT_MIN;
		}
		float total = proportional + integral;
		moveLeftLift(total);
		wait1Msec(liftConfig.dt);
	}
}

task holdRightLift() {
	int INT_MAX = 127;
	int INT_MIN = -127;
	float integral = 0;
	int proportional = 0;
	while (isRunning) {
		int error = SensorValue[RightLiftPot] - rightTarget;
		integral += liftConfig.ki * error * liftConfig.dt;
		if (integral > INT_MAX) {
			integral = INT_MAX;
		}
		else if (integral < INT_MIN) {
			integral = INT_MIN;
		}
		float total = proportional + integral;
		moveRightLift(total);
		wait1Msec(liftConfig.dt);
	}
}

void startPid(int tl, int tr, pid config) {
	if (isRunning) {
		return;
	}
	leftTarget = tl;
	rightTarget = tr;
	isRunning = true;
	liftConfig.kp = config.kp;
	liftConfig.ki = config.ki;
	liftConfig.kd = config.kd;
	liftConfig.dt = config.dt;
	startTask(holdLeftLift);
	startTask(holdRightLift);
}

void stopPid() {
	isRunning = false;
	stopTask(holdLeftLift);
	stopTask(holdRightLift);
}
