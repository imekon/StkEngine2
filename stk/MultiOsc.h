#ifndef _MULTIOSC_H
#define _MULTIOSC_H

#include "Stk.h"
#include "ADSR.h"

#include "STKParameters.h"
#include "MultiFilter.h"
#include "MultiOscVoice.h"
#include "ParametricOsc.h"

class MultiOsc : public ParametricOsc
{
public:
	explicit MultiOsc();

	void setFrequency(stk::StkFloat frequency) override;
	void noteOn(stk::StkFloat frequency, stk::StkFloat amplitude) override;
	void noteOff(stk::StkFloat amplitude) override;
	stk::StkFloat tick(unsigned int channel = 0) override;
	stk::StkFrames& tick(stk::StkFrames& frames, unsigned int channel = 0) override;

	void setParameter(STK_PARAMETERS parameter, stk::StkFloat value) override;

private:
	stk::StkFloat left;
	stk::StkFloat right;
	stk::StkFloat amplitude;
	MultiOscVoice osc1;
	MultiOscVoice osc2;
	MultiOscVoice osc3;
	stk::ADSR envelope;
	MultiFilter filter;
	stk::ADSR filterEnvelope;

};

#endif // _MULTIOSC_H
