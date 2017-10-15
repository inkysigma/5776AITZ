#include "motor.h"
#include "sensors.h"
#include "stall.c"

#define CONE_POT_HEIGHT 10
#define CONE_POT_CONST 2

void moveLiftTo(int cone_level, bool stall) {
	while (getLeftPot() < CONE_POT_HEIGHT * cone_level + CONE_POT_CONST) {
		moveLift(90);
	}
	if (stall) {
		applyStall();
	}
	else {
		moveLift(0);
	}
}
