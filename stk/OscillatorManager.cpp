#include "OscillatorManager.h"

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

OscillatorManager::OscillatorManager()
{
}

OscillatorManager::~OscillatorManager()
{
	for(auto osc : oscillators)
	{
		delete osc;
	}
}

void OscillatorManager::addOscillator(ParametricOsc* osc)
{
	oscillators.push_back(osc);
}

bool OscillatorManager::removeOscillator(ParametricOsc* osc)
{
	auto iter = std::find(oscillators.begin(), oscillators.end(), osc);

	if (iter != oscillators.end())
	{
		oscillators.erase(iter);
		return true;
	}

	return false;
}

void OscillatorManager::tick(stk::FreeVerb *reverb, double &left, double &right)
{	
	StkFloat mix, l, r;

	left = 0.0;
	right = 0.0;

	for(auto osc : oscillators)
	{
		l = osc->tick(0);
		r = osc->tick(1);
		mix = osc->getParameter(STK_REVERB_MIX);
		left += reverb->tick(l, r, 0) * mix + l;
		right += reverb->tick(l, r, 1) * mix + r;
	}
}
