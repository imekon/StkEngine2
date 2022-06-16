#ifndef _MULTIOSCVOICE_H
#define _MULTIOSCVOICE_H

#include "STKParameters.h"
#include "BlitSquare.h"
#include "BlitSaw.h"
#include "SineWave.h"
#include "Noise.h"
#include "Instrmnt.h"

class MultiOscVoice : public stk::Instrmnt
{
public:
	MultiOscVoice();

	STK_OSC_TYPE getType() const { return type; }
	void setType(STK_OSC_TYPE type);
	void setFrequency(stk::StkFloat frequency) override;
	stk::StkFloat tick(unsigned int channel = 0) override;

	stk::StkFrames& tick(stk::StkFrames& frames, unsigned int channel = 0) override
	{
		return frames;
	}

	void noteOn(stk::StkFloat frequency, stk::StkFloat amplitude) override { }
	void noteOff(stk::StkFloat amplitude) override { }

private:
	STK_OSC_TYPE type;
	stk::BlitSaw saw;
	stk::BlitSquare square;
	stk::SineWave sine;
	stk::Noise noise;
};

#endif // _MULTIOSCVOICE_H
