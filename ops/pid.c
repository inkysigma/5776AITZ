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
	float min_total;
	float max_total;

	// delta time in milliseconds
	float dt;

	// used for holding state
	float accumulation;
	float prev_error;

	// the sensor the use and the target
	tSensors sensor;
	float target;
};

pid *initPid(float kp, float ki, float kd, int dt, tSensors sensor)
{
	// initialize the pid to some constants. for tSensors sensor, pass in
	// an actual sensor like initPid(kp, ki, kd, dt, in1) or
	// also initPid(kp, ki, kd, dt, LeftLiftPot)
	// TODO: implement a method to set the max and min
	pid config;
	pid *ref = &config;

	ref->kp = kp;
	ref->ki = ki;
	ref->kd = kd;
	ref->dt = dt;
	ref->min_int = -30;
	ref->max_int = 30;
	ref->min_total = -110;
	ref->max_total = 110;
	ref->sensor = sensor;

	return ref;
}

void resetPid(pid *config)
{
	// reset the pid accumulator and prev_error
	config->accumulation = 0;
	config->prev_error = 0;
}

void setTarget(pid *config, float target)
{
	// set the target of the pid for a given instance
	config->target = target;
}

int pidStep(pid *config)
{
	// calculate the value derived by a pid
	float current_pos = SensorValue[config->sensor]
	float error = SensorValue[config->sensor] - config->target;
	float integral = config->accumulation + error * config->dt / 1000;
	float derivative = error - config->prev_error;
	config->accumulation = integral;

	writeDebugStreamLine("		current position: %f", current_pos);
	writeDebugStreamLine("		current error: %f", error);
	// check if integral has exceeded maximum
	if (integral > config->max_int)
	{
		integral = config->max_int;
	}
	else if (integral < config->min_int)
	{
		integral = config->min_int;
	}
	writeDebugStreamLine("		current proportional constant: %f", config->kp);
	float prop_res = config->kp * error;
	float total = prop_res + config->ki *integral + config->kd * derivative;
	writeDebugStreamLine("		current proportional: %f", prop_res);
	writeDebugStreamLine("		current total: %f", total);
	writeDebugStreamLine("		current proportional constant: %f", config->kp);
	// check if the total has exceeded a certain total
	if (total > config->max_total)
	{
		total = config->max_total;
		writeDebugStreamLine("		Maximum for total reached. Setting total to %d", total);
	}
	else if (total < config->min_total)
	{
		total = config->min_total;
		writeDebugStreamLine("		Minimum for total reached. Setting total to %d", total);
	}
	return (int) total;
}

void waitPid(pid *config) {
	// wait the time of a pid
	wait1Msec(config->dt);
}
