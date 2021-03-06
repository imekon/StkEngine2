#include "MultiOscPart.h"

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

MultiOscPart::MultiOscPart(): type(STK_OSC_TYPE_SAW)
{
}

void MultiOscPart::setType(STK_OSC_TYPE type)
{
	this->type = type;
}

void MultiOscPart::setFrequency(stk::StkFloat frequency)
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

stk::StkFloat MultiOscPart::tick(unsigned channel)
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

