#include "ops/motor_ops.h"

const int SLOPE = 25;
const int Y_INTERCEPT= 1;
const int BOTTOM = SensorValue[LeftLiftPot];

void buildStack(int current_level) {
	// start with claw at top and get cone and return to top to dispense
	moveLiftTo(current_level, true);
	writeDebugStreamLine("raised lift");

	// move the claw to the ending positions
	openClawFully(true);
	writeDebugStreamLine("opened claw fully");

	lowerClawFully();
	writeDebugStreamLine("lowered claw fully");

	lowerLiftTo(0, true);
	writeDebugStreamLine("lowered the lift to ground state");

	closeClawFully();
	writeDebugStreamLine("closed the claw fully");

	// swtich the claw back on top
	moveLiftTo(current_level, true);
	writeDebugStreamLine("raised the lift back up");

  raiseClawFully();
  writeDebugStreamLine("raised claw fully");

  // release the cone
	releaseCone(false);
	writeDebugStream("released the cone");
}
