#include "pid.c"
#include "motor.h"

void linePid(int target, pid config, int err) {
	int INT_MAX = liftConfig.kp * 30;
	int INT_MIN = liftConfig.kp * 20;
	int integral = 0;
	int proportional = 0;
	int total = 0;
	while (!isRunning) {
		int error = SensorValue[LiftPot] - target;
		proportional = config.kp * error;
		integral += config.ki * error;
		if (integral > INT_MAX) {
			integral = INT_MAX;
		}
		else if (integral < INT_MIN) {
			integral = INT_MIN;
		}
		total = proportional + integral;
		moveLift(total);
		wait1Msec(config.dt);
	}
}
