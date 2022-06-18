#include "Utilities.h"
#include "MultiOscVoice.h"

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

using namespace stk;

MultiOscVoice::MultiOscVoice(ParametricOsc *parametricOsc) : parametricOsc(parametricOsc)
{
	left = 0.0;
	right = 0.0;
	amplitude = 0.7;
}

void MultiOscVoice::setFrequency(StkFloat frequency)
{
	osc1.setFrequency(Utilities::noteRatio(parametricOsc->getParameter(STK_PARAMETER_OSC1_COARSE) + parametricOsc->getParameter(STK_PARAMETER_OSC1_FINE) / 100.0, frequency));
	osc2.setFrequency(Utilities::noteRatio(parametricOsc->getParameter(STK_PARAMETER_OSC2_COARSE) + parametricOsc->getParameter(STK_PARAMETER_OSC2_FINE) / 100.0, frequency));
	osc3.setFrequency(Utilities::noteRatio(parametricOsc->getParameter(STK_PARAMETER_OSC3_COARSE) + parametricOsc->getParameter(STK_PARAMETER_OSC3_FINE) / 100.0, frequency));
}

void MultiOscVoice::noteOn(StkFloat frequency, StkFloat amplitude)
{
	this->amplitude = amplitude;
	envelope.keyOn();
	setFrequency(frequency);
}

void MultiOscVoice::noteOff(StkFloat amplitude)
{
	envelope.keyOff();
}

StkFloat MultiOscVoice::tick(unsigned int channel)
{
	if (channel == 0)
	{
		// The oscillators
		lastFrame_[0] = osc1.tick() * parametricOsc->getParameter(STK_PARAMETER_OSC1_GAIN);
		lastFrame_[0] += osc2.tick() * parametricOsc->getParameter(STK_PARAMETER_OSC2_GAIN);
		lastFrame_[0] += osc3.tick() * parametricOsc->getParameter(STK_PARAMETER_OSC3_GAIN);

		// The envelope
		lastFrame_[0] *= envelope.tick();

		left = parametricOsc->getParameter(STK_PARAMETER_LEFT) * lastFrame_[0] * amplitude;
		right = parametricOsc->getParameter(STK_PARAMETER_RIGHT) * lastFrame_[0] * amplitude;

		lastFrame_[0] = left;

		return left;
	}

	return right;
}

StkFrames& MultiOscVoice::tick(StkFrames& frames, unsigned int channel)
{
	return frames;
}

