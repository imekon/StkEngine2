#include "Chorus.h"
#include "ChorusFX.h"

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

ChorusFX::ChorusFX() : left(0.0), right(0.0)
{

}

stk::StkFloat ChorusFX::tick(stk::StkFloat input, int channel)
{
	if (bypass)
		return input;
	else
	{
		if (channel == 0)
		{
			left = leftChorus.tick(input, 0) * 0.7 + rightChorus.tick(input, 0) * 0.7;
			right = leftChorus.tick(input, 1) * 0.7 + rightChorus.tick(input, 1) * 0.7;

			return left;
		}

		return right;
	}
}

void ChorusFX::setEffectMix(stk::StkFloat mix)
{
	leftChorus.setEffectMix(mix);
	rightChorus.setEffectMix(mix);
}

void ChorusFX::setParameter(STK_EFFECT_PARAMETERS parameter, stk::StkFloat value)
{
	FX::setParameter(parameter, value);

	switch(parameter)
	{
	case STK_EFFECT_MOD_DEPTH:
		leftChorus.setModDepth(value);
		rightChorus.setModDepth(value);
		break;

	case STK_EFFECT_MOD_FREQ:
		leftChorus.setModFrequency(value);
		rightChorus.setModFrequency(value);
		break;
	}
}
