#ifndef _ECHOFX_H
#define _ECHOFX_H

#include "Echo.h"
#include "FX.h"

class EchoFX : public FX
{
public:
	EchoFX();

	stk::StkFloat tick(stk::StkFloat input, int channel = 0) override;
	void setEffectMix(stk::StkFloat mix) override;
	void setParameter(STK_EFFECT_PARAMETERS parameter, stk::StkFloat value) override;

private:
	stk::StkFloat delay, feedback, pingPong;
	stk::Echo echoLeft, echoRight;
};

#endif // _ECHOFX_H

