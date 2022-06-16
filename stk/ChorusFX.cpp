#include "Chorus.h"
#include "ChorusFX.h"

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
