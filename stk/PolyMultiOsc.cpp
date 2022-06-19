#include "Utilities.h"
#include "MultiOscVoice.h"
#include "PolyMultiOsc.h"

PolyMultiOsc::PolyMultiOsc(int voiceCount) : left(0.0), right(0.0), amplitude(0.7)
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

	for (int i = 0; i < voiceCount; i++)
	{
		auto voice = new MultiOscVoice(this);
		voicer.addInstrument(voice);
		voices.push_back(voice);
	}
}

void PolyMultiOsc::setFrequency(stk::StkFloat frequency)
{
	voicer.setFrequency(Utilities::noteRatio(parameters[STK_PARAMETER_OSC1_COARSE] + parameters[STK_PARAMETER_OSC1_FINE] / 100.0, frequency));
}

void PolyMultiOsc::noteOn(stk::StkFloat frequency, stk::StkFloat amplitude)
{
	this->amplitude = amplitude;
	filterEnvelope.keyOn();
	setFrequency(frequency);
}

void PolyMultiOsc::noteOff(stk::StkFloat amplitude)
{
	filterEnvelope.keyOff();
}

stk::StkFloat PolyMultiOsc::tick(unsigned int channel)
{
	if (channel == 0)
	{
		// The oscillators
		lastFrame_[0] = voicer.tick();

		// The filter
		filter.setCutoffMod(filterEnvelope.tick() * parameters[STK_FILTER_ENVELOPE_MIX]);
		lastFrame_[0] = filter.tick(lastFrame_[0], channel);

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

stk::StkFrames& PolyMultiOsc::tick(stk::StkFrames& frames, unsigned int channel)
{
	return voicer.tick(frames, channel);
}

void PolyMultiOsc::setParameter(STK_PARAMETERS parameter, stk::StkFloat value)
{
	parameters[parameter] = value;

	switch (parameter)
	{
	case STK_PARAMETER_OSC1_TYPE:
		for(auto voice : voices)
			voice->osc1.setType(static_cast<STK_OSC_TYPE>(static_cast<int>(value)));
		break;

	case STK_PARAMETER_OSC2_TYPE:
		for (auto voice : voices)
			voice->osc2.setType(static_cast<STK_OSC_TYPE>(static_cast<int>(value)));
		break;

	case STK_PARAMETER_OSC3_TYPE:
		for (auto voice : voices)
			voice->osc3.setType(static_cast<STK_OSC_TYPE>(static_cast<int>(value)));
		break;

	case STK_PARAMETER_PANNING:
		Utilities::panning(parameters[STK_PARAMETER_PANNING], parameters[STK_PARAMETER_LEFT], parameters[STK_PARAMETER_RIGHT]);
		break;

	default:
		break;
	}

	setFilter(filter, filterEnvelope, parameter, value);
}
