#include "pragmas.h"
// Select Download method as "competition"
#pragma competitionControl(Competition)

#include "motor.h"
#include "corrector.c"
#include "pid.c"
//#include "autonomous.c"
#include "Vex_Competition_Includes.c"

void pre_auton() {
	datalogClear()
	bStopTasksBetweenModes = true;


	SensorType[in1] = sensorNone;
	delay(1500);

	SensorType[in1] = sensorGyro;
	delay(1500);
}

void pre_auton() {}

task autonomous() {
}

task usercontrol() {
	datalogClear();
	pid config;
	pid rconfig;
	config.kp = 1;
	config.ki = 0.2;
	config.kd = 0;
	config.dt = 15;

	rconfig.kp = 1;
	rconfig.ki = 0.2;
	rconfig.kd = 0;
	rconfig.dt = 15;

	setLeftConfig(config);
	setRightConfig(rconfig);

	startLeftLiftPid();

	while (true) {
		// drive code
		moveDrive(vexRT[Ch3], vexRT[Ch2]);

		// lift code
		if (vexRT[Btn5U]) {
			stopPid();
			moveRight(127);
			} else if (vexRT[Btn5D]) {
			stopPid();
			moveRight(-127);
			} else {
			if (!isRunning()) {
				moveRight(0);
			}
		}

		if (vexRT[Btn6U]) {
			openClaw(127);
			} else if (vexRT[Btn6D]) {
			closeClaw(127);
			} else {
			stopClaw();
		}

		if (vexRT[Btn8L]) {
			moveGoal(100);
			} else if (vexRT[Btn8R]) {
			moveGoal(-100);
			} else {
			moveGoal(0);
		}

		if (vexRT[Btn7U]) {
			moveSwitchLift(127);
			} else if (vexRT[Btn7D]) {
			moveSwitchLift(-127);
			} else {
			moveSwitchLift(0);
		}
		if (vexRT[Btn5U]) {
			stopRightPid();
			moveRightLift(127);
			} else if (vexRT[Btn5D]) {
			stopRightPid();
			moveRightLift(-127);
			} else {
			startRightPid(SensorValue[RightLiftPot]);
		}
		}
	}
}
