#pragma config(Sensor, in2,    LiftPot,        sensorPotentiometer)
#include "motor.h"

bool ir = false;
int target = 0;

typedef struct {
	float kp;
	float kd;
	float ki;
	float dt;
} pid;

pid lliftConfig;
pid rliftConfig;

int leftOffset = SensorValue[LeftLiftPot];
int rightOffset = SensorValue[RightLiftPot];


// holdLift holds the lift at a specific position using a PID loop.
task holdLeftLift() {
	int INT_MAX = 127;
	int INT_MIN = -127;
	float integral = 0;
	int proportional = 0;
	int total = 0;
	while (ir) {
		int error = (target - leftOffset) - (SensorValue[LeftLiftPot] - leftOffset);
		proportional = lliftConfig.kp * error;
		integral += lliftConfig.ki * error * lliftConfig.dt;
		if (integral > INT_MAX) {
			integral = INT_MAX;
		}
		else if (integral < INT_MIN) {
			integral = INT_MIN;
		}
		total = proportional + integral;
		moveLeftLift(-total);
		datalogAddValue(total, 1);
		datalogAddValue(error, 2)
		wait1Msec(lliftConfig.dt);
	}
}

task holdRightLift() {
	int INT_MAX = 127;
	int INT_MIN = -127;
	float integral = 0;
	int proportional = 0;
	int total = 0;
	while (ir) {
		int error = (target - leftOffset) - (SensorValue[RightLiftPot]- rightOffset);
		integral += rliftConfig.ki * error * rliftConfig.dt;
		if (integral > INT_MAX) {
			integral = INT_MAX;
		}
		else if (integral < INT_MIN) {
			integral = INT_MIN;
		}
		float total = proportional + integral;
		moveRightLift(total);

		datalogAddValue(total, 3);
		datalogAddValue(error, 4);
		wait1Msec(rliftConfig.dt);
	}
}

void startPid(int t, pid config, pid rconfig) {
	if (ir) {
		return;
	}
	target = t - leftOffset;
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
