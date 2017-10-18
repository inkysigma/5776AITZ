#include "core/motor.h"

task main()
{
	// first
	moveDrive(tile);
	rotate(-90);
	moveDrive(1.5 * tile);
	rotate(90);
	moveDrive(1.5 * tile);
	rotate(90);
	moveDrive(0.5 * tile);
	pickUpMobileGoal();
	rotate(90);
	moveDrive(0.5 * tile);
	pickUpCone();
	moveDrive(0.5 * tile);
	pickUpCone();
	rotate(-90);
	moveDrive(0.5 * tile);
	rotate(-45);
	moveDrive(sqrt(2)/2 * tile);
	rotate(-90);
	moveDrive(sqrt(2)/2 * tile);
	rotate(-45);
	moveDrive(1.5 * tile);
	// idk what im doing
}
