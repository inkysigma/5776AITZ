#define Kp 1
#define Kd 0.001
#define Ki 0.001
#define dt 0.01
#include "motor.h"

int isRunning = 0;
int target = 0;
task liftPid() {
    float prevError = 0;
    float integral = 0;
    while (isRunning) {
        int err = SensorValue[LiftPot] - target;
        int derivative = err - prevError;
        prevError = err;
        integral += err * dt;
        moveLift(Kp * err + Kd * derivative + Ki * integral);
    }
}

void startPid() {
    isRunning = 1;
    startTask(liftPid);
}

void stopPid() {
    isRunning = 0;
    stopTask(liftPid)
}
