#include "Utilities.h"
#include "MonoMultiOsc.h"

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

MonoMultiOsc::MonoMultiOsc() : left(0.0), right(0.0), amplitude(0.7)
{
	parameters[STK_PARAMETER_OSC1_TYPE] = STK_OSC_TYPE_SAW;
	parameters[STK_PARAMETER_OSC1_GAIN] = 1.0;
	parameters[STK_PARAMETER_OSC1_COARSE] = 0.0;
	parameters[STK_PARAMETER_OSC1_FINE] = 0.0;

	parameters[STK_PARAMETER_OSC2_TYPE] = STK_OSC_TYPE_SAW;
	parameters[STK_PARAMETER_OSC2_GAIN] = 0.0;
	parameters[STK_PARAMETER_OSC2_COARSE] = 0.0;
	parameters[STK_PARAMETER_OSC2_FINE] = 0.0;

	parameters[STK_PARAMETER_OSC3_TYPE] = STK_OSC_TYPE_SAW;
	parameters[STK_PARAMETER_OSC3_GAIN] = 0.0;
	parameters[STK_PARAMETER_OSC3_COARSE] = 0.0;
	parameters[STK_PARAMETER_OSC3_FINE] = 0.0;

	initialiseFilter(filter, filterEnvelope);
	initialiseEnvelope(envelope);
}

void MonoMultiOsc::setFrequency(StkFloat frequency)
{
	osc1.setFrequency(Utilities::noteRatio(parameters[STK_PARAMETER_OSC1_COARSE] + parameters[STK_PARAMETER_OSC1_FINE] / 100.0, frequency));
	osc2.setFrequency(Utilities::noteRatio(parameters[STK_PARAMETER_OSC2_COARSE] + parameters[STK_PARAMETER_OSC2_FINE] / 100.0, frequency));
	osc3.setFrequency(Utilities::noteRatio(parameters[STK_PARAMETER_OSC3_COARSE] + parameters[STK_PARAMETER_OSC3_FINE] / 100.0, frequency));
}

void MonoMultiOsc::noteOn(StkFloat frequency, StkFloat amplitude)
{
	this->amplitude = amplitude;
	envelope.keyOn();
	filterEnvelope.keyOn();
	setFrequency(frequency);
}

void MonoMultiOsc::noteOff(StkFloat amplitude)
{
	envelope.keyOff();
	filterEnvelope.keyOff();
}

StkFloat MonoMultiOsc::tick(unsigned int channel)
{
	if (channel == 0)
	{
		// The oscillators
		lastFrame_[0] = osc1.tick() * parameters[STK_PARAMETER_OSC1_GAIN];
		lastFrame_[0] += osc2.tick() * parameters[STK_PARAMETER_OSC2_GAIN];
		lastFrame_[0] += osc3.tick() * parameters[STK_PARAMETER_OSC3_GAIN];

		// The filter
		filter.setCutoffMod(filterEnvelope.tick() * parameters[STK_FILTER_ENVELOPE_MIX]);
		lastFrame_[0] = filter.tick(lastFrame_[0], channel);

		// The envelope
		lastFrame_[0] *= envelope.tick();

		left = parameters[STK_PARAMETER_LEFT] * lastFrame_[0] * amplitude;
		right = parameters[STK_PARAMETER_RIGHT] * lastFrame_[0] * amplitude;

		// The effects
		for (int i = 0; i < effects.size(); i++)
		{
			left += effects[i]->tick(left, 0);
		}

		lastFrame_[0] = left;

		return left;
	}

	// The effects
	for (int i = 0; i < effects.size(); i++)
	{
		right += effects[i]->tick(right, 1);
	}

	return right;
}

StkFrames& MonoMultiOsc::tick(StkFrames& frames, unsigned int channel)
{
	return frames;
}

void MonoMultiOsc::setParameter(STK_PARAMETERS parameter, StkFloat value)
{
	parameters[parameter] = value;

	switch(parameter)
	{
	case STK_PARAMETER_OSC1_TYPE:
		osc1.setType(static_cast<STK_OSC_TYPE>(static_cast<int>(value)));
		break;

	case STK_PARAMETER_OSC2_TYPE:
		osc2.setType(static_cast<STK_OSC_TYPE>(static_cast<int>(value)));
		break;

	case STK_PARAMETER_OSC3_TYPE:
		osc3.setType(static_cast<STK_OSC_TYPE>(static_cast<int>(value)));
		break;

	case STK_PARAMETER_PANNING:
		Utilities::panning(parameters[STK_PARAMETER_PANNING], parameters[STK_PARAMETER_LEFT], parameters[STK_PARAMETER_RIGHT]);
		break;

	default:
		break;
	}

	setFilter(filter, filterEnvelope, parameter, value);
	setEnvelope(envelope, parameter, value);
}

