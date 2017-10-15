#include "core/motor.h"
#include "core/sensors.h"

#define CONE_POT_HEIGHT 8
#define CONE_POT_CONST 2
#define CONE_RELEASE_CONST 100

const int OUT_ANGLE = 90;
const int IN_ANGLE = 0;
const int FAST_SPEED = 100;
const int SLOW_ANGLE = 45;
const int SLOW_SPEED = 50;
const int SYNC_SPEED = 15;

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


void moveMogoOut() {
	while (SensorValue[MogoRightPot] < SLOW_ANGLE) {
		moveGoal(SLOW_SPEED);
	}
	while (SensorValue[MogoRightPot] > OUT_ANGLE) {
		// motor[RightMobileGoal] = FAST_SPEED;
		moveGoal(FAST_SPEED);
	}
}

void moveMogoIn() {
	while (SensorValue[MogoRightPot] > IN_ANGLE) {
		moveRightMogo(-FAST_SPEED);
		moveLeftMogo(FAST_SPEED);
	}
	moveRightMogo(0);
	moveLeftMogo(0);
}

void syncMogo() {
	while (SensorValue[MogoRightPot] > IN_ANGLE && SensorValue[MogoLeftPot] > IN_ANGLE) {
		if (SensorValue[MogoRightPot] > IN_ANGLE) {
			motor[RightMobileGoal] = -SYNC_SPEED;
		} else {
			motor[RightMobileGoal] = 0;
		}
		if (SensorValue[MogoLeftPot] > IN_ANGLE) {
			motor[LeftMobileGoal] = -SYNC_SPEED;
		} else {
			motor[LeftMobileGoal] = 0;
		}
	}
}
