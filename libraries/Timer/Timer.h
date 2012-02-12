#ifndef TIMER_H
#define TIMER_H

#include <Time.h>

class Timer {
public:
	Timer();
	time_t trigger;

	void Start();
	bool IsTriggered();
	inline void ForceTrigger() {
		trigger = 1;
	}
	inline void SetInterval(int i) {
		interval = i;
	}

private:
	time_t interval;
};

#endif
