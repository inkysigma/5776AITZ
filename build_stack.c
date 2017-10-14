#include "pragmas.h"

const int slope;
const int y_intercept;
const int forward_angle; // angle for vertical fourbar
const int backward_angle;
const int bottom;

void buildStack(int level) {
	openClawFully();
	moveClawForward(forward_angle);
	closeClawFully();
	moveLiftTo(level * slope + y_intercept);
    moveClawBackward(backward_angle);
	openClawFully();
	moveClawForward(forward_angle);
	moveLiftTo(bottom);
}

void build_up(int *level) {
    if (*level != 14) {
    	*level++;
    }
    buildStack(*level);
}
