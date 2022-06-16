#ifndef _STK_ENGINE_H
#define _STK_ENGINE_H

#include "RtAudio.h"
#include "Timer.h"
#include "OscillatorManager.h"
#include "FreeVerb.h"
#include "StkGlobals.h"

class StkEngine : public Timer
{
public:
	StkEngine();
	virtual ~StkEngine();

	void start() override;
	void stop() override;

	stk::StkFloat getGlobal(STK_GLOBALS global) const { return globals[global]; }
	void setGlobal(STK_GLOBALS global, stk::StkFloat value);
	void setTempo(stk::StkFloat tempo, int steps);

	void addOsc(ParametricOsc *osc);
	bool removeOsc(ParametricOsc *osc);

	bool waitTick() const;

protected:
	void tick() override;

private:
	HANDLE tickEvent;
	RtAudio dac;
	stk::FreeVerb reverb;

	stk::StkFloat globals[STK_GLOBAL_MAX];

	OscillatorManager oscManager;

	static int rtAudioTick(void *outputBuffer,
		void *inputBuffer,
		unsigned int nBufferFrames,
		double streamTime,
		RtAudioStreamStatus status,
		void *dataPointer);
};

#endif // _STK_ENGINE_H
