#include <windows.h>

#include "Timer.h"

/*

STKEngine2

Copyright 2016-2022 Pete Goodwin

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Note this only applies to STKEngine2 and not the STK software itself.
*/

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
