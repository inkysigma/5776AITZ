#include "motor.h"

bool ir = false;
int target = 0;

struct pid {
	float kp;
	float kd;
	float ki;
	float dt;
};

pid lliftConfig;
pid rliftConfig;

void setRightConfig(pid rConfig) {
	rliftConfig.kp = rconfig.kp;
	rliftConfig.ki = rconfig.ki;
	rliftConfig.kd = rconfig.kd;
	rliftConfig.dt = rconfig.dt;
}

void setLeftConfig(pid lconfig) {
	lliftConfig.kp = lconfig.kp;
	lliftConfig.ki = lconfig.ki;
	lliftConfig.kd = lconfig.kd;
	lliftConfig.dt = lconfig.dt;
}

// holdLift holds the lift at a specific position using a PID loop.
task holdLeftLift() {
	float integral = 0;
	int proportional = 0;
	int total = 0;
	while (true) {
		int error = SensorValue[LeftLiftPot] - SensorValue[RightLiftButton];
		proportional = lliftConfig.kp * error;
		integral += lliftConfig.ki * total * lliftConfig.dt;
		total = error + integral;
		moveLeftLift(-total);

		wait1Msec(lliftConfig.dt);
	}
}

void startLeftLiftPid() {
	startTask(holdLeftLift);
}

task holdRightLift() {
	int INT_MAX = 127;
	int INT_MIN = -127;
	float integral = 0;
	int proportional = 0;
	int total = 0;
	while (ir) {
		int error = target - SensorValue[RightLiftPot];
		integral += rliftConfig.ki * error * rliftConfig.dt;
		if (integral > INT_MAX) {
			integral = INT_MAX;
		}
		else if (integral < INT_MIN) {
			integral = INT_MIN;
		}
		float total = proportional + integral;
		moveRightLift(total);

		wait1Msec(rliftConfig.dt);
	}
}

void startRightPid(int t) {
	if (ir) {
		return;
	}
	target = t;
	ir = true;
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
