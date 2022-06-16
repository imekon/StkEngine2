#include "FX.h"

FX::FX()
{
	bypass = false;
	parameters[STK_EFFECT_MIX] = 0.0;
}

FX::~FX()
{
}

void FX::setBypass(bool value)
{
	bypass = value;
}

void FX::setParameter(STK_EFFECT_PARAMETERS parameter, stk::StkFloat value)
{
	parameters[parameter] = value;

	switch (parameter)
	{
	case STK_EFFECT_BYPASS:
		setBypass(value > 0.0);
		break;

	case STK_EFFECT_MIX:
		setEffectMix(value);
		break;
	}
}
