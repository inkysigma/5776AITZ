#include "motor.h"

bool lir = false;
bool rir = false;
int target = 0;

struct pid {
	float kp;
	float kd;
	float ki;
	float min_int;
	float max_int;
	float min_t;
	float max_t;
	float dt;
};

pid lliftConfig;
pid rliftConfig;

void setRightConfig(pid rconfig) {
	rliftConfig.kp = rconfig.kp;
	rliftConfig.ki = rconfig.ki;
	rliftConfig.kd = rconfig.kd;
	rliftConfig.dt = rconfig.dt;
	rliftConfig.min_int = rconfig.min_int;
	rliftConfig.max_int = rconfig.max_int;
	rliftConfig.min_t = rconfig.min_t;
	rliftConfig.max_t = rconfig.max_t;
}

void setLeftConfig(pid lconfig) {
	lliftConfig.kp = lconfig.kp;
	lliftConfig.ki = lconfig.ki;
	lliftConfig.kd = lconfig.kd;
	lliftConfig.dt = lconfig.dt;
	lliftConfig.min_int = lconfig.min_int;
	lliftConfig.max_int = lconfig.max_int;
	lliftConfig.min_t = lconfig.min_t;
	lliftConfig.max_t = lconfig.max_t;
}

// holdLift holds the lift at a specific position using a PID loop. This should target the right side
task holdLeftLift() {
	float integral = 0;
	float total = 0;
	while (lir) {
		int error = getRightPot() - getLeftPot();
		integral += error * lliftConfig.dt/1000;

		if (integral > lliftConfig.max_int) {
			integral = lliftConfig.max_int;
			} else if (integral < lliftConfig.min_int) {
			integral = lliftConfig.min_int;
		}

		total = lliftConfig.kp * error + lliftConfig.ki * integral;

		if (total > rliftConfig.max_t) {
			total = rliftConfig.max_t;
			} else if (total < rliftConfig.min_t) {
			total = rliftConfig.min_t;
		}

		moveLeftLift(total);

		wait1Msec(lliftConfig.dt);
		datalogAddValue(0, total);
	}
}

// holdRightLift should target some given target. Once the user moves up or down, this task should stop. Once movement stops,
// this ought to start running
task holdRightLift() {
	float integral = 0;
	int proportional = 0;
	int total = 0;
	while (rir) {
		int error = target - getRightPot();
		integral += error * rliftConfig.dt/1000;

		if (integral > rliftConfig.max_int) {
			integral = rliftConfig.max_int;
		}
		else if (integral < rliftConfig.min_int) {
			integral = rliftConfig.min_int;
		}
		float total = rliftConfig.kp * error + rliftConfig.ki * integral;
		if (total > rliftConfig.max_t) {
			total = rliftConfig.max_t;
			} else if (total < rliftConfig.min_t) {
			total = rliftConfig.min_t;
		}
		moveRightLift(total);
		datalogAddValue(1, total);
		wait1Msec(rliftConfig.dt);
	}
}

void startRightPid(int t) {
	target = t;
	rir = true;
	startTask(holdRightLift);
}

void startLeftPid() {
	lir = true;
	startTask(holdLeftLift);
}

void stopRightPid() {
	rir = false;
	stopTask(holdRightLift);
}

void stopLeftPid() {
	lir = false;
	stopTask(holdLeftLift);
}
