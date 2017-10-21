#include "core/motor.h"
#include "core/sensors.h"
#include "util/concurrency.h"

#define CONE_POT_HEIGHT 140
#define CONE_POT_CONST 5
#define CONE_RELEASE_CONST 50
#define MIN_LIFT_POT 0
#define SWITCH_TIME 1250
#define LOW_SWITCH_POT 3800
#define HIGH_SWITCH_POT 1675
#define OPEN_CLAW_TIME 70
#define CLOSE_CLAW_TIME 70

const int OUT_ANGLE = 90;
const int IN_ANGLE = 0;
const int FAST_SPEED = 100;
const int SLOW_ANGLE = 45;
const int SLOW_SPEED = 50;
const int SYNC_SPEED = 15;

void raiseLiftTo(int cone_level, bool stall) {
	while (getLeftPot() < CONE_POT_HEIGHT * cone_level + CONE_POT_CONST) {
		moveLift(90);
		wait1Msec(5;
	}
	if (stall) {
		wait1Msec(170);
		applyStall();
	}
	else {
		moveLift(0);
	}
}

void lowerLiftTo(int cone_level, bool stall) {

	executeUntil({
		moveLift(-90);
		wait1Msec(5);
	},
	getLeftPot() > CONE_POT_HEIGHT * cone_level + CONE_POT_CONST,
	4000);

	if (stall) {
		wait1Msec(170);
		applyStall();
	}
	else {
		moveLift(0);
	}
}

void raiseClawPartial(bool stall) {
	executeUntil({
		raiseClaw(127);
		wait1Msec(5);
	},
	SensorValue[SwitchLiftPot] > 3200, 4000);
		if (stall) {
		wait1Msec(170);
		applyStall();
	}
	else {
		moveLift(0);
	}
}

void releaseCone(bool close) {
	openClaw(100);
	wait1Msec(CONE_RELEASE_CONST);
	if (close) {
		closeClawFully();
	}
	else {
		stopClaw();
	}
}


void lowerClawFully() {
  	lowerClaw(100);
  	executeUntil(wait1Msec(50), SensorValue[SwitchLiftPot] < LOW_SWITCH_POT, 4000);
	lowerClaw(0);
}

void raiseClawFully() {
  raiseClaw(100);
  while (SensorValue[SwitchLiftPot] > HIGH_SWITCH_POT) {
		wait1Msec(50);
	}
	lowerClaw(0);
}

void openClawFully() {
	openClaw(80);
	wait1Msec(OPEN_CLAW_TIME);
	openClaw(0);
	wait1Msec(40);
}

void closeClawFully() {
	closeClaw(70);
	wait1Msec(CLOSE_CLAW_TIME);
	closeClaw(15);
	wait1Msec(40);
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
