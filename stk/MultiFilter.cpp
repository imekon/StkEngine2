#include "MultiFilter.h"

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

MultiFilter::MultiFilter() :
	filterType(FilterType::LowPass),
	cutoff(0.99),
	cutoffMod(0.0),
	resonance(0.0)
{
	clear();
	calculateFeedback();
}

void MultiFilter::clear()
{
	//Filter::clear();
	buf0[0] = buf0[1] = 0.0;
	buf1[0] = buf1[1] = 0.0;
	buf2[0] = buf2[1] = 0.0;
	buf3[0] = buf3[1] = 0.0;
}

void MultiFilter::initialise()
{
	cutoff = 0.99;
	cutoffMod = 0.0;
	resonance = 0.0;
	filterType = FilterType::LowPass;
	clear();
	calculateFeedback();
}

StkFrames& MultiFilter::tick(StkFrames& frames, unsigned int channel)
{
	return frames;
}

StkFloat MultiFilter::tick(StkFloat input, unsigned int channel)
{
	StkFloat result = 0.0;
	if (input == 0.0)
	{
		return result;
	}

	StkFloat calcCutoff = getCalculatedCutoff();

	buf0[channel] += calcCutoff * (input - buf0[channel] + feedback * (buf0[channel] - buf1[channel]));
	buf1[channel] += calcCutoff * (buf0[channel] - buf1[channel]);
	buf2[channel] += calcCutoff * (buf1[channel] - buf2[channel]);
	buf3[channel] += calcCutoff * (buf2[channel] - buf3[channel]);

	switch (filterType)
	{
	case FilterType::LowPass:
		result = buf3[channel];
		break;

	case FilterType::HighPass:
		result = input - buf3[channel];
		break;

	case FilterType::BandPass:
		result = buf0[channel] - buf3[channel];
		break;
	}

	return result * gain_;
}

void MultiFilter::setCutoff(StkFloat value)
{
	cutoff = value;
	calculateFeedback();
}

void MultiFilter::setResonance(StkFloat value)
{
	resonance = value;
	calculateFeedback();
}

void MultiFilter::setCutoffMod(StkFloat value)
{
	cutoffMod = value;
	calculateFeedback();
}

void MultiFilter::calculateFeedback()
{
	feedback = resonance + resonance / (1.0 - getCalculatedCutoff());
}

StkFloat MultiFilter::getCalculatedCutoff() const
{
	return fmax(fmin(cutoff + cutoffMod, 0.99), 0.01);
}

