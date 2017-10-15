#include "pragmas.h"

const int SLOPE = 25;
const int Y_INTERCEPT= 1;
const int BOTTOM = SensorValue[LeftLiftPot];

void buildStack(int level) {
	openClawFully();
	switchClaw();
	closeClawFully();
	moveLiftTo(level * SLOPE + Y_INTERCEPT);
  moveClawBackward(backward_angle);
	openClawFully();
	switchClaw();
	moveLiftTo(BOTTOM);
}

void build_up(int *level) {
    if (*level != 14) {
    	*level++;
    }
    buildStack(*level);
}
