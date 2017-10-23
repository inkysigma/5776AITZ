struct pid {
	float kp;
	float kd;
	float ki;
	float min_int;
	float max_int;
	float min_t;
	float max_t;
	float dt;
	float accumulation;
	float prev_error;
	tSensors sensor;
	float target;
};

pid * initPid(float kp, float ki, float kd, int dt) {
	pid config;
	pid * ref = &config;

	ref->kp = kp;
	ref->ki = ki;
	ref->kd = kd;
	ref->dt = dt;
	ref->min_int = -30;
	ref->max_int = 30;
	ref->min_t = -110;
	ref->max_t = 110;

	return ref;
}

void resetPid(pid * config) {
	config->accumulation = 0;
	config->prev_error = 0;
}

void setTarget(pid * config, float target) {
	config->target = target;
}

float pidStep(pid * config) {
	float error = SensorValue[config->sensor] - config->target;
	float integral = config->accumulation + error * config->dt / 1000;
	float derivative = error - config->prev_error;
	config->accumulation = integral;
	return config->kp * error + config->ki * integral + config->kd * derivative;
}
