#pragma once

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

#include "Stk.h"
#include "ADSR.h"

#include "MultiFilter.h"
#include "MultiOscPart.h"
#include "ParametricOsc.h"

class MultiOscVoice : public stk::Instrmnt
{
public:
	explicit MultiOscVoice(ParametricOsc *parametricOsc);

	void setFrequency(stk::StkFloat frequency) override;
	void noteOn(stk::StkFloat frequency, stk::StkFloat amplitude) override;
	void noteOff(stk::StkFloat amplitude) override;
	stk::StkFloat tick(unsigned int channel = 0) override;
	stk::StkFrames& tick(stk::StkFrames& frames, unsigned int channel = 0) override;

private:
	friend class PolyMultiOsc;

	stk::StkFloat left;
	stk::StkFloat right;
	stk::StkFloat amplitude;
	MultiOscPart osc1;
	MultiOscPart osc2;
	MultiOscPart osc3;
	stk::ADSR envelope;
	ParametricOsc* parametricOsc;
};

