#include "EchoFX.h"

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
