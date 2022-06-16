#ifndef _CHORUSFX_H
#define _CHORUSFX_H

#include "FX.h"
#include "Chorus.h"

class ChorusFX : public FX
{
public:
	explicit ChorusFX();

	stk::StkFloat tick(stk::StkFloat input, int channel = 0) override;
	void setEffectMix(stk::StkFloat mix) override;
	void setParameter(STK_EFFECT_PARAMETERS parameter, stk::StkFloat value) override;

private:
	stk::StkFloat left, right;
	stk::Chorus leftChorus, rightChorus;
};

#endif // _CHORUSFX_H
