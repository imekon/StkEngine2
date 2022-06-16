#ifndef _MULTIOSCMANAGER_H
#define _MULTIOSCMANAGER_H

#include <vector>

#include "FreeVerb.h"
#include "ParametricOsc.h"

class OscillatorManager
{
public:
	OscillatorManager();
	~OscillatorManager();

	void addOscillator(ParametricOsc *osc);
	bool removeOscillator(ParametricOsc *osc);
	void tick(stk::FreeVerb *reverb, double &left, double &right);

private:
	std::vector<ParametricOsc *> oscillators;
};

#endif // _MULTIOSCMANAGER_H

