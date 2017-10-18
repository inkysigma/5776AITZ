#ifndef CONCURRENCY_MACRO_CONTROL
#define CONCURRENCY_MACRO_CONTROL

#define executeUntil(method, condition) executeUntil(method, condition, 700)

#define executeUntil(method, condition, timeout) {\
	ClearTimer(T1); \
	while (condition && timer1[T1] < timeout) { \
		method \
	} \
}

#endif
