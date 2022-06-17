#include "ParametricOsc.h"
#include "MultiFilter.h"
#include "Utilities.h"

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
