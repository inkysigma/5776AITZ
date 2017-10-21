#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, in3,    LeftLiftPot,    sensorPotentiometer)
#pragma config(Sensor, in4,    RightLiftPot,   sensorPotentiometer)
#pragma config(Sensor, in5,    SwitchLiftPot,  sensorPotentiometer)
#pragma config(Sensor, in7,    MogoRightPot,   sensorPotentiometer)
#pragma config(Sensor, in8,    MogoLeftPot,    sensorPotentiometer)
#pragma config(Sensor, dgtl1,  RightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  LeftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  RightLiftEnc,   sensorRotation)
#pragma config(Sensor, dgtl6,  LeftLiftEnc,    sensorRotation)
#pragma config(Sensor, dgtl7,  RightLiftButton, sensorDigitalIn)
#pragma config(Sensor, dgtl8,  LeftLiftButton, sensorDigitalIn)
#pragma config(Motor,  port2,           LeftDrive,     tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           RightDrive,    tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           LeftLift,      tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           RightLift,     tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           LeftMobileGoal, tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           RightMobileGoal, tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           SwitchLift,    tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           Claw,          tmotorVex393HighSpeed_MC29, openLoop)
#pragma platform(VEX2)
// Select Download method as "competition"
#pragma competitionControl(Competition)

#include "core/motor.h"
#include "core/sensors.h"
#include "ops/pid.c"
#include "ops/motor_ops.h"
#include "ops/build_stack.c"

#include "Vex_Competition_Includes.c"


void pre_auton() {
	datalogClear();

	setInit(SensorValue[RightLiftPot], SensorValue[LeftLiftPot]);
	bStopTasksBetweenModes = true;

	SensorType[in1] = sensorNone;
	delay(1500);

	SensorType[in1] = sensorGyro;
	delay(1500);
}

task autonomous() {
}

task usercontrol() {
	pid * lconfig = initPid(1, 0, 0, 15);
	pid * rconfig = initPid(1, 0, 0, 15);

	setLeftConfig(lconfig);
	setRightConfig(rconfig);

	bool pidrunning = false;

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
		}
		else if (vexRT[Btn7D]) {
			moveSwitchLift(-127);
		}
		else {
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
