#include "pragmas.h"
#include "motor_ops.h"

const int SLOPE = 25;
const int Y_INTERCEPT= 1;
const int BOTTOM = SensorValue[LeftLiftPot];

void buildStack(int start_level) {
	openClawFully();
	switchClaw();
	closeClawFully();

	moveLiftTo(2, false);
  switchClaw();

	openClawFully();
	switchClaw();
	moveLiftTo(0, false);
}

void build_up(int *level) {
    if (*level != 14) {
    	*level++;
    }
    buildStack(*level);
}
