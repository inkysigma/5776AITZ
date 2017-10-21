#include "motor_ops.h"

void buildStack(int current_level) {
	// start with claw at top and get cone and return to top to dispense
	// raiseLiftTo(current_level, true);
	// writeDebugStreamLine("raised lift");

	// move the claw to the ending positions
	openClawFully();
	writeDebugStreamLine("opened claw fully");

	lowerClawFully();
	writeDebugStreamLine("lowered claw fully");

	lowerLiftTo(0, false);
	writeDebugStreamLine("lowered the lift to ground state");

	closeClawFully();
	writeDebugStreamLine("closed the claw fully");

	// extend the claw a bit further so that we don't get caught
	raiseClawPartial(true);

	// swtich the claw back on top
	raiseLiftTo(current_level, true);
	writeDebugStreamLine("raised the lift back up");

	raiseClawFully();
	writeDebugStreamLine("raised claw fully");
	wait1Msec(250);

	lowerLiftTo(current_level, true);

	releaseCone(false);
	writeDebugStreamLine("released the cone");
}
