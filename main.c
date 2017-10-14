#include "pragmas.h"
// Select Download method as "competition"
#pragma competitionControl(Competition)

#include "motor.h"
#include "pid.c"
//#include "autonomous.c"
#include "Vex_Competition_Includes.c"



bool pidrunning = true;

void pre_auton() {
	datalogClear();

	setInitialValues(SensorValue[RightLiftPot], SensorValue[LeftLiftPot]);
	bStopTasksBetweenModes = true;

	SensorType[in1] = sensorNone;
	delay(1500);

	SensorType[in1] = sensorGyro;
	delay(1500);
}

task autonomous() {
}

task usercontrol() {
	pid config;
	pid rconfig;

	config.kp = 1;
	config.ki = 0;
	config.kd = 0;
	config.dt = 15;
	config.min_int = -30;
	config.max_int = 30;
	config.min_t = -120;
	config.max_t = 120;

	rconfig.kp = 1;
	rconfig.ki = 0;
	rconfig.kd = 0;
	rconfig.dt = 15;
	rconfig.min_int = -30;
	rconfig.max_int = 30;
	rconfig.min_t = -120;
	rconfig.max_t = 120;

	setLeftConfig(config);
	setRightConfig(rconfig);

	startLeftPid();

	while (true) {
		// drive code
		moveDrive(vexRT[Ch3], vexRT[Ch2]);

		if (vexRT[Btn6U]) {
			openClaw(127);
		}
		else if (vexRT[Btn6D]) {
			closeClaw(127);
		}
		else {
			stopClaw();
		}

		if (vexRT[Btn8L]) {
			moveGoal(100);
		}
		else if (vexRT[Btn8R]) {
			moveGoal(-100);
		}
		else {
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
			if (pidrunning) {
				moveRightLift(100);
			}
			else {
				moveLift(100);
			}
		}
		else if (vexRT[Btn5D]) {
			stopRightPid();
			if (pidrunning) {
				moveRightLift(-100);
			}
			else {
				moveLift(-100);
			}
		}
		else {
			if (pidrunning) {
				startRightPid(SensorValue[RightLiftPot]);
			}
			else {
				moveLift(0);
			}
		}

		if (vexRT[Btn7L]) {
			stopRightPid();
			stopLeftPid();
			pidrunning = false;
		}
		else if (vexRT[Btn7R]) {
			startLeftPid();
			startRightPid(SensorValue[RightLiftPot]);
			pidrunning = true;
		}
		}
	}
}
