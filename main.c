#pragma config(Sensor, in1,    			gyro,           sensorGyro)
#pragma config(Sensor, in3,    			LeftLiftPot,    sensorPotentiometer)
#pragma config(Sensor, in4,    			RightLiftPot,   sensorPotentiometer)
#pragma config(Sensor, in7,    			MogoRightPot,   sensorPotentiometer)
#pragma config(Sensor, in8,    			MogoLeftPot,    sensorPotentiometer)
#pragma config(Sensor, dgtl1,  			RightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  			LeftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  			RightLiftEnc,   sensorRotation)
#pragma config(Sensor, dgtl6,  			LeftLiftEnc,    sensorRotation)
#pragma config(Sensor, dgtl7,  			RightLiftButton,sensorDigitalIn)
#pragma config(Sensor, dgtl8,  			LeftLiftButton, sensorDigitalIn)
#pragma config(Motor,  port2,           LeftDrive,     	tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           RightDrive,    	tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           LeftLift,     	tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           RightLift,      tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           LeftMobileGoal, tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           RightMobileGoal,tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           SwitchLift,    	tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,			Claw,          	tmotorVex393HighSpeed_MC29, openLoop)
#pragma platform(VEX2)
// Select Download method as "competition"
#pragma competitionControl(Competition)

#include "motor.h"
#include "sensors.h"
#include "pid.c"

//#include "autonomous.c"
#include "Vex_Competition_Includes.c"



bool pidrunning = true;

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
