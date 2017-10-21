#ifndef CONCURRENCY_MACRO_CONTROL
#define CONCURRENCY_MACRO_CONTROL

#define executeUntil(method, condition, timeout) {\
	clearTimer(T1); \
	while (condition && time1[T1] < timeout) { \
		method \
	} \
}

#define executeOrTimeout(method, timeout) { \
}

#endif
