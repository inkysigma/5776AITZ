#include "motor_ops.h"

void buildStack(int current_level) {
	// start with claw at top and get cone and return to top to dispense
	writeDebugStreamLine("	raising lift {");
	raiseLiftTo(current_level, true);
	writeDebugStreamLine("	}");

	writeDebugStreamLine("	lowering claw fully {");
	lowerClawPartial(true);
	writeDebugStreamLine("	}");


	writeDebugStreamLine("	lowering the lift to ground state {");
	lowerLiftTo(0, false);
	writeDebugStreamLine("	}");

	writeDebugStreamLine("	lowering claw fully {");
	lowerClawFully();
	writeDebugStreamLine("	}");

	delay(750);

	writeDebugStreamLine("	closing the claw fully {");
	closeClawFully();
	writeDebugStream("	}");

	// extend the claw a bit further so that we don't get caugh
	writeDebugStreamLine("	raising the claw partially {");
	raiseClawPartial(true);
	writeDebugStreamLine("	}");

	// swtich the claw back on top
	writeDebugStreamLine("	raising the lift back up {");
	raiseLiftTo(current_level, true);
	writeDebugStreamLine("	}");

	writeDebugStreamLine("	raising claw fully {");
	raiseClawFully(true);
	writeDebugStreamLine("	}");

	writeDebugStreamLine("	lowering lift {");
	lowerLiftTo(current_level, true);
	writeDebugStreamLine("	}");

	delay(400);

	writeDebugStreamLine("	releasing cone {");
	releaseCone(false);
	writeDebugStreamLine("	}");

	delay(100);
}
