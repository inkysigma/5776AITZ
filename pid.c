#define Kp 1
#define Kd 0
#define Ki 0.001
#define dt 0.01
#include "motor.h"

void startPid() {
    isRunning = 1;
    startTask(liftPid);
}

void stopPid() {
    isRunning = 0;
    stopTask(liftPid);
}
/* #pragma config(Sensor, dgtl10,          encLeft,       sensorQuadEncoder)
#pragma config(Sensor, dgtl12,          encRight,      sensorQuadEncoder)
#pragma config(Motor,  port2,           right,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           left,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           toplift,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           bottomlift,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           mogoR,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           mogoL,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           top4bar,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           claw,          tmotorVex393_MC29, openLoop) **/

void drive(int distance, int power, int waitTime) {
	int timer = 0;
	while (SensorValue[encLeft] < distance && timer < waitTime) {
		motor[left] = power;
		motor[right] = power;
		wait1Msec(20);
		timer += 20;
	}
}

void moveLift(int power) {
	motor[toplift] = power;
	motor[bottomlift] = power;
}

void moveMogo(int power) {
	motor[mogoR] = power;
	motor[mogoL] = power;
}

void moveTop4bar(int power) {
	motor[top4bar] = power;
}

void claw_move(int power) {
	motor[claw] = power;
}
// Allows user to control the robot
// PID should be active when button values are equal to 0
task user_control() {
	while(true) {

		motor[right] = vexRT[Ch2];
		motor[left] = vexRT[Ch3];


		if(vexRT[Btn6U] == 1) {
			moveLift(127);
			} else if (vexRT[Btn6D]) {
			moveLift(-127);
		}

		if(vexRT[Btn5U] == 1) {
			moveMogo(127);
			} else if (vexRT[Btn5D]) {
			moveMogo(-127);
		}

		if(vexRT[Btn8U] == 1) {
			moveTop4bar(127);
			} else if (vexRT[Btn8D]) {
			moveTop4bar(-127);
		}

		if(vexRT[Btn8L] == 1) {
			claw_move(127);
			} else if (vexRT[Btn8R]) {
			claw_move(-127);
		}
	}
}

// holdLift holds the lift at a specific position using a PID loop.
task holdLift() {
	writeDebugStreamLine("PID loop is running");
	int SCALE_PROPORTIONAL = 0.05;
	int SCALE_INTEGRAL = 0.005;
	int INT_MAX = SCALE_PROPORTIONAL * 30;
	int INT_MIN = SCALE_PROPORTIONAL * 20;
	int integral = 0;
	int proportional = 0;
	int total = 0;
	while (!vexRT[Btn6D]) {
		writeDebugStreamLine("PID loop is in progress");
		int error;
		proportional = SCALE_PROPORTIONAL * error;
		integral += SCALE_INTEGRAL * error;
		if (integral > INT_MAX) {
			integral = INT_MAX;
		}
		else if (integral < INT_MIN) {
			integral = INT_MIN;
		}
		total = proportional + integral;
		moveLift(total);
		wait1Msec(20);
	}
	writeDebugStreamLine("PID Loop is stopping");
}

task main() {
}
