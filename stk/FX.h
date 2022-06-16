#ifndef _FX_H
#define _FX_H

#include "Stk.h"
#include "Effect.h"
#include "STKParameters.h"

class FX
{
public:
	explicit FX();
	virtual ~FX();

	void setBypass(bool value);
	bool getBypass() const { return bypass; }

	virtual void setEffectMix(stk::StkFloat mix) = 0;
	virtual stk::StkFloat tick(stk::StkFloat input, int channel = 0) = 0;

	stk::StkFloat getParameter(STK_EFFECT_PARAMETERS parameter) const { return parameters[parameter]; }
	virtual void setParameter(STK_EFFECT_PARAMETERS parameter, stk::StkFloat value);

protected:
	bool bypass;
	stk::StkFloat parameters[STK_EFFECT_MAX];
};

#endif // _FX_H
