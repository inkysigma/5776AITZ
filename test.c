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
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#include "core/motor.h"
#include "ops/motor_ops.h"
#include "ops/build_stack.c"

task main()
{
	buildStack(0);
}
