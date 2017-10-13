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

void setRightConfig(pid rconfig) {
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

int rightLiftInit = SensorValue[RightLiftPot];
int leftLiftInit = SensorValue[LeftLiftPot];

int getRightPot() {
	return SensorValue[RightLiftPot] - rightLiftInit;
}

int getLeftPot() {
	return SensorValue[LeftLiftPot] - leftLiftInit;
}

// holdLift holds the lift at a specific position using a PID loop.
task holdLeftLift() {
	float integral = 0;
	int proportional = 0;
	int total = 0;
	while (true) {
		int error = getRightPot() - getLeftPot();
		proportional = lliftConfig.kp * error;
		integral += total * lliftConfig.dt/1000;
		total = proportional + lliftConfig.ki * integral;
		moveLeftLift(total);

		wait1Msec(lliftConfig.dt);
		datalogAddValue(0, total);
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
		int error = target - getRightPot();
		integral += error * rliftConfig.dt/1000;
		if (integral > INT_MAX) {
			integral = INT_MAX;
		}
		else if (integral < INT_MIN) {
			integral = INT_MIN;
		}
		float total = rliftConfig.kp * error + rliftConfig.ki * integral;
		moveRightLift(total);
		datalogAddValue(1, total);
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

void stopRightPid() {
	if (!ir) {
		return;
	}
	ir = false;
	stopTask(holdRightLift);
}

bool isRunning() {
	return ir;
}
