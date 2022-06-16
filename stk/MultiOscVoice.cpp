#include "MultiOscVoice.h"

MultiOscVoice::MultiOscVoice(): type(STK_OSC_TYPE_SAW)
{
}

void MultiOscVoice::setType(STK_OSC_TYPE type)
{
	this->type = type;
}

void MultiOscVoice::setFrequency(stk::StkFloat frequency)
{
	switch(type)
	{
	case STK_OSC_TYPE_NONE:
	case STK_OSC_TYPE_NOISE:
		break;

	case STK_OSC_TYPE_SAW:
		saw.setFrequency(frequency);
		break;

	case STK_OSC_TYPE_SQUARE:
		square.setFrequency(frequency);
		break;

	case STK_OSC_TYPE_SINE:
		sine.setFrequency(frequency);
		break;
	}	
}

stk::StkFloat MultiOscVoice::tick(unsigned channel)
{
	switch(type)
	{
	case STK_OSC_TYPE_SAW:
		return saw.tick();

	case STK_OSC_TYPE_SQUARE:
		return square.tick();

	case STK_OSC_TYPE_NOISE:
		return noise.tick();

	case STK_OSC_TYPE_SINE:
		return sine.tick();
	}

	return 0.0;
}

