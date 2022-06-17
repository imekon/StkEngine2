#include "EchoFX.h"

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

EchoFX::EchoFX() : delay(1.0), feedback(0.3), pingPong(0.0)
{
	parameters[STK_EFFECT_DELAY] = delay;
	parameters[STK_EFFECT_FEEDBACK] = feedback;
	parameters[STK_EFFECT_PINGPONG] = pingPong;

	echoLeft.setMaximumDelay(Stk::sampleRate());
	echoRight.setMaximumDelay(Stk::sampleRate() * 2.0);
}

StkFloat EchoFX::tick(stk::StkFloat input, int channel)
{
	if (!bypass)
	{
		StkFloat output;

		switch (channel)
		{
		case 0:
			output = input * (1.0 - feedback) + echoLeft.tick(input + echoLeft.lastOut() * feedback);
			return output;

		case 1:
			output = input * (1.0 - feedback) + echoRight.tick(input + echoRight.lastOut() * feedback);
			return output;
		}
	}

	return input;
}

void EchoFX::setEffectMix(stk::StkFloat mix)
{
	echoLeft.setEffectMix(mix);
	echoRight.setEffectMix(mix);
}

void EchoFX::setParameter(STK_EFFECT_PARAMETERS parameter, stk::StkFloat value)
{
	FX::setParameter(parameter, value);

	switch(parameter)
	{
	case STK_EFFECT_DELAY:
		delay = value;
		echoLeft.setDelay(static_cast<int>(value * Stk::sampleRate()));
		echoRight.setDelay(static_cast<int>((value + pingPong) * Stk::sampleRate()));
		break;

	case STK_EFFECT_FEEDBACK:
		feedback = value;
		break;

	case STK_EFFECT_PINGPONG:
		pingPong = value;
		echoRight.setDelay(static_cast<int>((delay + pingPong) * Stk::sampleRate()));
		break;
	}
}
