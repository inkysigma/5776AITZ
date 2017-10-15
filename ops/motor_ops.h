#include "core/motor.h"
#include "core/sensors.h"

#define CONE_POT_HEIGHT 8
#define CONE_POT_CONST 2
#define CONE_RELEASE_CONST 100

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

void releaseCone() {
	openClaw(100);
	wait1Msec(CONE_RELEASE_CONST);
	stopClaw();
}
