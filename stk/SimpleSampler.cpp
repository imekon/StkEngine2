#include "SimpleSampler.h"

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

using namespace std;
using namespace stk;

SimpleSampler::SimpleSampler() : playing(false), gain(0.7)
{
}

void SimpleSampler::setRawFile(string filename)
{
	this->filename = filename;

	wave.openFile(Stk::rawwavePath() + filename, true);
	wave.setRate(22050.0 / Stk::sampleRate());
}

void SimpleSampler::noteOn(stk::StkFloat frequency, stk::StkFloat amplitude)
{
	gain = amplitude;
	playing = true;
	wave.reset();
}

void SimpleSampler::noteOff(stk::StkFloat amplitude)
{
	playing = false;
}

StkFloat SimpleSampler::tick(unsigned int channel)
{
	if (playing)
	{
		StkFloat sample = wave.tick();
		if (wave.isFinished())
		{
			playing = false;
		}
		return sample;
	}

	return 0.0;
}

StkFrames& SimpleSampler::tick(StkFrames& frames, unsigned int channel)
{
	//for (unsigned int i = 0; i < frames.size(); i++)
	//{
	//	frames[i] = tick();
	//}
	return frames;
}
