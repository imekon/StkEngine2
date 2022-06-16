#include "Utilities.h"
#include "MultiOsc.h"

using namespace stk;

MultiOsc::MultiOsc()
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

	left = 0.0;
	right = 0.0;
	amplitude = 0.7;
}

void MultiOsc::setFrequency(StkFloat frequency)
{
	osc1.setFrequency(Utilities::noteRatio(parameters[STK_PARAMETER_OSC1_COARSE] + parameters[STK_PARAMETER_OSC1_FINE] / 100.0, frequency));
	osc2.setFrequency(Utilities::noteRatio(parameters[STK_PARAMETER_OSC2_COARSE] + parameters[STK_PARAMETER_OSC2_FINE] / 100.0, frequency));
	osc3.setFrequency(Utilities::noteRatio(parameters[STK_PARAMETER_OSC3_COARSE] + parameters[STK_PARAMETER_OSC3_FINE] / 100.0, frequency));
}

void MultiOsc::noteOn(StkFloat frequency, StkFloat amplitude)
{
	this->amplitude = amplitude;
	envelope.keyOn();
	filterEnvelope.keyOn();
	setFrequency(frequency);
}

void MultiOsc::noteOff(StkFloat amplitude)
{
	envelope.keyOff();
	filterEnvelope.keyOff();
}

StkFloat MultiOsc::tick(unsigned int channel)
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

StkFrames& MultiOsc::tick(StkFrames& frames, unsigned int channel)
{
	return frames;
}

void MultiOsc::setParameter(STK_PARAMETERS parameter, StkFloat value)
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

