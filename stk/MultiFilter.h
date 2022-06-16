#ifndef _MULTIFILTER_H
#define _MULTIFILTER_H

#include "stk.h"
#include "Filter.h"

enum class FilterType
{
	LowPass,
	HighPass,
	BandPass
};

class MultiFilter : public stk::Filter
{
public:
	MultiFilter();

	void clear() override;
	stk::StkFrames& tick(stk::StkFrames& frames, unsigned int channel = 0) override;
	stk::StkFloat tick(stk::StkFloat input, unsigned int channel);

	FilterType getFilterType() const { return filterType; }
	void setFilterType(FilterType type) { filterType = type; }

	stk::StkFloat getCutoff() const { return cutoff; }
	void setCutoff(stk::StkFloat value);

	stk::StkFloat getCutoffMod() const { return cutoffMod; }
	void setCutoffMod(stk::StkFloat value);

	stk::StkFloat getResonance() const { return resonance; }
	void setResonance(stk::StkFloat value);

	void initialise();

private:
	FilterType filterType;
	stk::StkFloat cutoff;
	stk::StkFloat cutoffMod;
	stk::StkFloat resonance;
	stk::StkFloat buf0[2];
	stk::StkFloat buf1[2];
	stk::StkFloat buf2[2];
	stk::StkFloat buf3[2];
	stk::StkFloat feedback;

	void calculateFeedback();
	stk::StkFloat getCalculatedCutoff() const;
};

#endif // _MULTIFILTER_H
