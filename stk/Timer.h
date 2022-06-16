#ifndef _TIMER_H
#define _TIMER_H

#include <windows.h>

class Timer
{
public:
	Timer();
	virtual ~Timer();

	virtual void start();
	virtual void stop();
	void setInterval(int time);

protected:
	virtual void tick() = 0;

private:
	bool started;
	int interval;
	HANDLE timerQueue;
	HANDLE timer;

	static void CALLBACK callback(PVOID param, BOOLEAN timerOrWaitFired);
};

#endif // _TIMER_H
