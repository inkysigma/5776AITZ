#include "motor.h"
// int tile = tile length
// void pickUpCone(int level);

void autonomous() {
	// TODO: Implement the actual methods and find the associated values
	moveDrive(2 * tile);
	rotate(90);
	pickUpCone(0);
	rotate(-90);
	moveDrive(tile);
	rotate(90);
	moveDrive(1.5 * tile);
	rotate(90);
	pickUpMobileGoal();
	moveDrive(0.5 * tile);
	rotate(90);
	pickUpCone(1);
	moveDrive(0.5 * tile);
	pickUpCone(2);
	moveDrive(tile);
	rotate(-90);
	moveDrive(2 * tile);
	rotate(45);
	moveDrive(sqrt(2) * tile);
}
