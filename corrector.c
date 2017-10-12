#define MoGoKP 1

int initialLeft = SensorValue[MogoLeftPot];
int initialRight = SensorValue[MogoRightPot];

float getMogoCorrection(int power) {
	float dleft = SensorValue[MogoLeftPot] - initialLeft;
	float dright = SensorValue[MogoRightPot] - initialRight;
	datalogAddValue(0, power + MoGoKP * (dright - dleft));
	datalogAddValue(1, dright - dleft);
	return power ;//+ MoGoKP * (dright - dleft);
}
