#include "OscillatorManager.h"

using namespace stk;

OscillatorManager::OscillatorManager()
{
}

OscillatorManager::~OscillatorManager()
{
	for(auto osc : oscillators)
	{
		delete osc;
	}
}

void OscillatorManager::addOscillator(ParametricOsc* osc)
{
	oscillators.push_back(osc);
}

bool OscillatorManager::removeOscillator(ParametricOsc* osc)
{
	auto iter = std::find(oscillators.begin(), oscillators.end(), osc);

	if (iter != oscillators.end())
	{
		oscillators.erase(iter);
		return true;
	}

	return false;
}

void OscillatorManager::tick(stk::FreeVerb *reverb, double &left, double &right)
{	
	StkFloat mix, l, r;

	left = 0.0;
	right = 0.0;

	for(auto osc : oscillators)
	{
		l = osc->tick(0);
		r = osc->tick(1);
		mix = osc->getParameter(STK_REVERB_MIX);
		left += reverb->tick(l, r, 0) * mix + l;
		right += reverb->tick(l, r, 1) * mix + r;
	}
}
