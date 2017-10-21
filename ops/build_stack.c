#include "motor_ops.h"

void buildStack(int current_level) {
	// start with claw at top and get cone and return to top to dispense
	raiseLiftTo(current_level, true);
	writeDebugStreamLine("raised lift");

	lowerClawPartial(true);
	writeDebugStreamLine("lowered claw fully");

	lowerLiftTo(0, false);
	writeDebugStreamLine("lowered the lift to ground state");

	lowerClawFully();

	closeClawFully();
	writeDebugStreamLine("closed the claw fully");

	// extend the claw a bit further so that we don't get caught
	raiseClawPartial(true);
	writeDebugStreamLine("raised the claw partially");

	// swtich the claw back on top
	raiseLiftTo(current_level, true);
	writeDebugStreamLine("raised the lift back up");

	raiseClawFully();
	writeDebugStreamLine("raised claw fully");

	lowerLiftTo(current_level, true);

	releaseCone(false);
	writeDebugStreamLine("released the cone");

	delay(100);
}
