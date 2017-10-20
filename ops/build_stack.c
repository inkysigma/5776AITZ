#include "motor_ops.h"

void buildStack(int current_level) {
	// start with claw at top and get cone and return to top to dispense
	// raiseLiftTo(current_level, true);
	// writeDebugStreamLine("raised lift");

	// move the claw to the ending positions
	openClawFully(true);
	writeDebugStreamLine("opened claw fully");

	// lowerClawFully();
	// writeDebugStreamLine("lowered claw fully");

	lowerLiftTo(0, false);
	writeDebugStreamLine("lowered the lift to ground state");

	closeClawFully(true);
	writeDebugStreamLine("closed the claw fully");

	// swtich the claw back on top
	writeDebugStreamLine("raised the lift back up");

	raiseClawFully();
	writeDebugStreamLine("raised claw fully");
	wait1Msec(250);

	releaseCone(false);
	writeDebugStreamLine("released the cone");
}
