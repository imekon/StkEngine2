#include "ParametricOsc.h"
#include "MultiFilter.h"
#include "Utilities.h"

using namespace stk;

ParametricOsc::ParametricOsc()
{
	parameters[STK_AMP_ENVELOPE_ATTACK] = 0.1;
	parameters[STK_AMP_ENVELOPE_DECAY] = 0.1;
	parameters[STK_AMP_ENVELOPE_SUSTAIN] = 1.0;
	parameters[STK_AMP_ENVELOPE_RELEASE] = 0.5;

	parameters[STK_FILTER_ENVELOPE_ATTACK] = 0.1;
	parameters[STK_FILTER_ENVELOPE_DECAY] = 0.1;
	parameters[STK_FILTER_ENVELOPE_SUSTAIN] = 1.0;
	parameters[STK_FILTER_ENVELOPE_RELEASE] = 0.5;
	parameters[STK_FILTER_ENVELOPE_MIX] = 0.0;

	parameters[STK_PARAMETER_PANNING] = 0.5;
	Utilities::panning(parameters[STK_PARAMETER_PANNING], parameters[STK_PARAMETER_LEFT], parameters[STK_PARAMETER_RIGHT]);

	parameters[STK_REVERB_MIX] = 0.3;
}

void ParametricOsc::setParameter(STK_PARAMETERS parameter, stk::StkFloat value)
{
	parameters[parameter] = value;
}

void ParametricOsc::addEffect(FX* effect)
{
	effects.push_back(effect);
}

void ParametricOsc::removeEffect(FX* effect)
{
	auto iter = std::find(effects.begin(), effects.end(), effect);

	if (iter != effects.end())
	{
		effects.erase(iter);
	}
}

void ParametricOsc::initialiseFilter(MultiFilter& filter, stk::ADSR& filterEnvelope)
{
	parameters[STK_FILTER_CUTOFF] = filter.getCutoff();
	parameters[STK_FILTER_RES] = filter.getResonance();
	parameters[STK_FILTER_TYPE] = static_cast<StkFloat>(static_cast<int>(filter.getFilterType()));

	filterEnvelope.setAllTimes(parameters[STK_FILTER_ENVELOPE_ATTACK],
		parameters[STK_FILTER_ENVELOPE_DECAY],
		parameters[STK_FILTER_ENVELOPE_SUSTAIN],
		parameters[STK_FILTER_ENVELOPE_RELEASE]);
}

void ParametricOsc::initialiseEnvelope(stk::ADSR& envelope)
{
	envelope.setAllTimes(parameters[STK_AMP_ENVELOPE_ATTACK],
		parameters[STK_AMP_ENVELOPE_DECAY],
		parameters[STK_AMP_ENVELOPE_SUSTAIN],
		parameters[STK_AMP_ENVELOPE_RELEASE]);
}

void ParametricOsc::setFilter(MultiFilter& filter, stk::ADSR& filterEnvelope, STK_PARAMETERS parameter, stk::StkFloat value)
{
	switch (parameter)
	{
	case STK_FILTER_CUTOFF:
		filter.setCutoff(value);
		break;

	case STK_FILTER_RES:
		filter.setResonance(value);
		break;

	case STK_FILTER_TYPE:
		filter.setFilterType(static_cast<FilterType>(static_cast<int>(value)));
		break;

	case STK_FILTER_ENVELOPE_ATTACK:
	case STK_FILTER_ENVELOPE_DECAY:
	case STK_FILTER_ENVELOPE_SUSTAIN:
	case STK_FILTER_ENVELOPE_RELEASE:
		filterEnvelope.setAllTimes(parameters[STK_FILTER_ENVELOPE_ATTACK],
			parameters[STK_FILTER_ENVELOPE_DECAY],
			parameters[STK_FILTER_ENVELOPE_SUSTAIN],
			parameters[STK_FILTER_ENVELOPE_RELEASE]);
		break;

	default:
		break;
	}
}

void ParametricOsc::setEnvelope(stk::ADSR& envelope, STK_PARAMETERS parameter, stk::StkFloat value)
{
	switch (parameter)
	{
	case STK_AMP_ENVELOPE_ATTACK:
	case STK_AMP_ENVELOPE_DECAY:
	case STK_AMP_ENVELOPE_SUSTAIN:
	case STK_AMP_ENVELOPE_RELEASE:
		envelope.setAllTimes(parameters[STK_AMP_ENVELOPE_ATTACK],
			parameters[STK_AMP_ENVELOPE_DECAY],
			parameters[STK_AMP_ENVELOPE_SUSTAIN],
			parameters[STK_AMP_ENVELOPE_RELEASE]);
		break;
	}
}

void ParametricOsc::loadParameters(stk::StkFloat* parameters)
{
	for(int i = 0; i < STK_PARAMETERS_MAX; i++)
	{
		setParameter(static_cast<STK_PARAMETERS>(i), parameters[i]);
	}
}

void ParametricOsc::saveParameters(stk::StkFloat* parameters)
{
	for (int i = 0; i < STK_PARAMETERS_MAX; i++)
	{
		parameters[i] = getParameter(static_cast<STK_PARAMETERS>(i));
	}
}
