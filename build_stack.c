#include "pragmas.h"

const int SLOPE;
const int Y_INTERCEPT;
const int BOTTOM;

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
