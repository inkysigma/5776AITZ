#include "ops/pid.c"
#include "core/motor.h"

bool lir = false;
bool rir = false;

pid *leftConfig;
pid *rightConfig;

// setConfig sets the left and right pid configuration. use initPid(kp, ki, kd, dt, sensor)
// to create a configuration. pass the reference to config.
void setConfig(pid *left, pid *right) {
	leftConfig = left;
	rightConfig = right;
}

// holdLift holds the lift at a specific position using a PID loop. This should target the right side
task holdLeftLift() {
	float total = 0;
	while (lir) {
		setTarget(leftConfig, getRightPot());
		total = pidStep(leftConfig);
		moveLeftLift(total);
		waitPid(leftConfig);
	}
}

// holdRightLift should target some given target. Once the user moves up or down, this task should stop. Once movement stops,
// this ought to start running
task holdRightLift() {
	float total = 0;
	while (rir) {
		total = pidStep(rightConfig);
		moveRightLift(total);
		waitPid(rightConfig);
	}
}

void startRightPid(int t) {
	resetPid(rightConfig);
	setTarget(rightConfig, t);
	rir = true;
	startTask(holdRightLift);
}

void startLeftPid() {
	resetPid(leftConfig);
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
