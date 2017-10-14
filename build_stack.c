const int slope;
const int y_intercept;
const int forward_angle; // angle for vertical fourbar
const int backward_angle;

void buildStack(int level) {
	openClawFully();
	startPid(level * slope + y_intercept);
    move_claw_forward(forward_angle);
    move_claw_backward(backward_angle);
	closeClawFully();
}

void build_up(int *level) {
    if (*level != 14) {
    	*level++;
    }
    buildStack(*level);
}
