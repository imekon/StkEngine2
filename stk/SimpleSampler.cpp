#include "SimpleSampler.h"

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
