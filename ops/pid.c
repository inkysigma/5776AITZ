struct pid
{
	// constants used for the pid control
	float kp;
	float kd;
	float ki;

	// bounding the integral
	float min_int;
	float max_int;

	// bounding the total
	float max_total;
	float min_total;

	// delta time in milliseconds
	float dt;

	// used for holding state
	float accumulation;
	float prev_error;

	// the sensor the use and the target
	tSensors sensor;
	float target;
};

pid *initPid(float kp, float ki, float kd, int dt)
{
	pid config;
	pid *ref = &config;

	ref->kp = kp;
	ref->ki = ki;
	ref->kd = kd;
	ref->dt = dt;
	ref->min_int = -30;
	ref->max_int = 30;
	ref->min_total = -110;
	ref->min_total = 110;

	return ref;
}

void resetPid(pid *config)
{
	config->accumulation = 0;
	config->prev_error = 0;
}

void setTarget(pid *config, float target)
{
	config->target = target;
}

float pidStep(pid *config)
{
	float error = SensorValue[config->sensor] - config->target;
	float integral = config->accumulation + error * config->dt / 1000;
	float derivative = error - config->prev_error;
	config->accumulation = integral;

	// check if integral has exceeded maximum
	if (integral > config->max_int)
	{
		integral = config->max_int;
	}
	else if (integral < config->min_int)
	{
		integral = config->min_int;
	}

	float total = config->kp * error + config->ki * integral + config->kd * derivative;

	// check if the total has exceeded a certain total
	if (total > config->max_total)
	{
		total = config->max_total;
	}
	else if (total < config->min_total)
	{
		total = config->min_total;
	}
	return total;
}

void waitPid(pid * config) {
	wait1Msec(config->dt);
}
