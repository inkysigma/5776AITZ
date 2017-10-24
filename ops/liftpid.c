#include "ops/pid.c"
#include "core/motor.h"

bool lir = false;
bool rir = false;
int target = 0;


pid lliftConfig;
pid rliftConfig;

pid * leftConfig;
pid * rightConfig;

/** Legacy code to ensure stability
 * 
void setRightConfig(pid * rconfig) {
	rliftConfig.kp = rconfig->kp;
	rliftConfig.ki = rconfig->ki;
	rliftConfig.kd = rconfig->kd;
	rliftConfig.dt = rconfig->dt;
	rliftConfig.accumulation = 0;
	rliftConfig.prev_error = 0;
	rliftConfig.min_int = rconfig->min_int;
	rliftConfig.max_int = rconfig->max_int;
	rliftConfig.min_t = rconfig->min_t;
	rliftConfig.max_t = rconfig->max_t;
}

void setLeftConfig(pid * lconfig) {
	lliftConfig.kp = lconfig->kp;
	lliftConfig.ki = lconfig->ki;
	lliftConfig.kd = lconfig->kd;
	lliftConfig.dt = lconfig->dt;
	lliftConfig.accumulation = 0;
	lliftConfig.prev_error = 0;
	lliftConfig.min_int = lconfig->min_int;
	lliftConfig.max_int = lconfig->max_int;
	lliftConfig.min_t = lconfig->min_t;
	lliftConfig.max_t = lconfig->max_t;
}
**/

void setConfig(pid * left, pid * right) {
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
	setTarget(rightConfig, t);
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
