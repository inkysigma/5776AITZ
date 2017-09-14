#include "motor.h"

void autonomous() {
	// TODO: Implement the actual methods and find the associated values
	moveForward();
	rotate();
	pickUpCone();

	moveBackward();

	counterRotate();

	moveForward();

	rotate();
	deposit();

	pickUpMobileGoal();

	moveForward();
	pickUpCone();

	deposit();

	rotate();

	moveForward();

	counterRotate();

	pickUpCone();

	deposit();

	rotate();

	moveForward();

	counterRotate();

	pickUpCone();

	deposit();

	counterRotate();

	moveForward();

	dropCone();
}
