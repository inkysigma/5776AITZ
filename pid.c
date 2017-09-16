#pragma config(Sensor, in2,    LiftPot,        sensorPotentiometer)
#include "motor.h"

bool ir = false;

typedef struct {
	float kp;
	float kd;
	float ki;
	float dt;
} pid;

pid lliftConfig;
pid rliftConfig;
int leftTarget = 0;
int rightTarget = 0;


// holdLift holds the lift at a specific position using a PID loop.
task holdLeftLift() {
	int INT_MAX = 127;
	int INT_MIN = -127;
	int integral = 0;
	int proportional = 0;
	int total = 0;
	while (ir) {
		int error = leftTarget - SensorValue[LeftLiftPot];
		proportional = lliftConfig.kp * error;
		integral += lliftConfig.ki * error * lliftConfig.dt;
		if (integral > INT_MAX) {
			integral = INT_MAX;
		}
		else if (integral < INT_MIN) {
			integral = INT_MIN;
		}
		total = proportional + integral;
		moveLeftLift(total);
		datalogAddValue(total, 2);
		wait1Msec(lliftConfig.dt);
	}
}

task holdRightLift() {
	int INT_MAX = 127;
	int INT_MIN = -127;
	int integral = 0;
	int proportional = 0;
	int total = 0;
	while (ir) {
		int error = rightTarget - SensorValue[LeftLiftPot];
		integral += rliftConfig.ki * error * rliftConfig.dt;
		if (integral > INT_MAX) {
			integral = INT_MAX;
		}
		else if (integral < INT_MIN) {
			integral = INT_MIN;
		}
		total = proportional + integral;
		moveRightLift(total);
		datalogAddValue(total, 1);
		wait1Msec(rliftConfig.dt);
	}
}

void startPid(int tl, int tr, pid config, pid rconfig) {
	leftTarget = tl;
	rightTarget = tr;
	ir = true;
	lliftConfig.kp = config.kp;
	lliftConfig.ki = config.ki;
	lliftConfig.kd = config.kd;
	lliftConfig.dt = config.dt;
	rliftConfig.kp = rconfig.kp;
	rliftConfig.ki = rconfig.ki;
	rliftConfig.kd = rconfig.kd;
	rliftConfig.dt = rconfig.dt;
	startTask(holdLeftLift);
	startTask(holdRightLift);
}

void stopPid() {
	ir = false;
	stopTask(holdLeftLift);
	stopTask(holdRightLift);
}

bool isRunning() {
	return ir;
}
