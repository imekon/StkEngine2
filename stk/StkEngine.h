#ifndef _STK_ENGINE_H
#define _STK_ENGINE_H

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
