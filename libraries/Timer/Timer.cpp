#include "Timer.h"

Timer::Timer() {
	trigger = 0;
	interval = 0;
}

void Timer::Start() {
	if (interval) {
		trigger = now() + interval;
	}
}

bool Timer::IsTriggered() {
	if (now() > trigger && trigger != 0) {
		trigger = 0;
		return true;
	} else {
		return false;
	}
}
