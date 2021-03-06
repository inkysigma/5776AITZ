#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, in3,    LeftLiftPot,    sensorPotentiometer)
#pragma config(Sensor, in4,    RightLiftPot,   sensorPotentiometer)
#pragma config(Sensor, in5,    SwitchLiftPot,  sensorPotentiometer)
#pragma config(Sensor, in7,    MogoLeftPot,    sensorPotentiometer)
#pragma config(Sensor, in8,    MogoRightPot,   sensorPotentiometer)
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
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)
// Select Download method as "competition"
#pragma competitionControl(Competition)

#include "core/motor.h"
#include "core/sensors.h"
#include "ops/motor_ops.h"
#include "ops/build_stack.c"
#include "ops/liftPid.c"
#include "ops/pid.c"
#include "Vex_Competition_Includes.c"

#define LEFT_KP 10
#define LEFT_KI 0
#define LEFT_KD 0
#define LEFT_DT 20

#define RIGHT_KP 10
#define RIGHT_KI 0
#define RIGHT_KD 0
#define RIGHT_DT 20

int cone_counter = 0;


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

	// example pid configuration
	pid *leftConfig = initPid(LEFT_KP, LEFT_KI, LEFT_KD, LEFT_DT, LeftLiftPot);
	pid *rightConfig = initPid(RIGHT_KP, RIGHT_KI, LEFT_KD, LEFT_DT, RightLiftPot);

	while (true) {
		// drive code
		moveDrive(vexRT[Ch3], vexRT[Ch2]);

		// lift control with 5U/D
		if (vexRT[Btn5U]) {
			moveLift(100);
		}

		else if (vexRT[Btn5D]) {
			moveLift(-100);
		}

		else {
			applyStall();
		}

		// Btn6U/D should be assigned to switch lift and functionality
		if (vexRT[Btn6U]) {
			raiseClaw(127);
		}
		else if (vexRT[Btn6D]) {
			lowerClaw(127);
		}
		else {
			raiseClaw(0);
		}

		if (vexRT[Btn7R]) {
			openClawFully();
		}

		else if (vexRT[Btn7D]) {
			closeClawFully();
		}

		if (vexRT[Btn7L]) {
			moveGoal(70);
		}

		else if (vexRT[Btn7U]) {
			moveGoal(-127);
		}

		else {
			moveGoal(0);
		}

		// Btn8U/D should be used for buildStack control
		if (vexRT[Btn8U]) {
			buildStack(cone_counter);
			cone_counter = cone_counter + 1;
		}

		else if (vexRT[Btn8D]) {
			if (cone_counter > 0) {
				cone_counter = cone_counter - 1;
			}
		}

	}
}
