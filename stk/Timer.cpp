#include <windows.h>

#include "Timer.h"

Timer::Timer(): timer(nullptr)
{
	interval = 0;
	timerQueue = CreateTimerQueue();
	started = false;
}

Timer::~Timer()
{
	if (timerQueue)
	{
		DeleteTimerQueue(timerQueue);
	}
}

void Timer::start()
{
	CreateTimerQueueTimer(&timer, timerQueue, callback, this, 0, interval, 0);
	started = true;
}

void Timer::stop()
{
	DeleteTimerQueueTimer(timerQueue, timer, nullptr);
	started = false;
}

void Timer::setInterval(int time)
{
	bool hasStarted = started;

	if (hasStarted)
		stop();

	interval = time;

	if (hasStarted)
		start();
}

void CALLBACK Timer::callback(PVOID param, BOOLEAN timerOrWaitFired)
{
	if (param)
	{
		auto timer = static_cast<Timer *>(param);
		timer->tick();
	}
}
