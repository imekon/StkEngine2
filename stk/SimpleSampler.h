#ifndef _SIMPLESAMPLER_H
#define _SIMPLESAMPLER_H

#include "FileWvIn.h"
#include "ParametricOsc.h"

class SimpleSampler : public ParametricOsc
{
public:
	SimpleSampler();

	const char *getRawFile() const { return filename.c_str(); }
	void setRawFile(std::string filename);
	void noteOn(stk::StkFloat frequency, stk::StkFloat amplitude) override;
	void noteOff(stk::StkFloat amplitude) override;
	stk::StkFloat tick(unsigned int channel = 0) override;
	stk::StkFrames& tick(stk::StkFrames& frames, unsigned int channel = 0) override;

private:
	bool playing;
	std::string filename;
	stk::StkFloat gain;
	stk::FileWvIn wave;
};

#endif // _SIMPLESAMPLER_H
