#ifndef _PARAMETRICOSC_H
#define _PARAMETRICOSC_H

#include "Stk.h"
#include "ADSR.h"
#include "StkParameters.h"
#include "Instrmnt.h"
#include "MultiFilter.h"
#include "FX.h"

class ParametricOsc : public stk::Instrmnt
{
public:
	explicit ParametricOsc();
	stk::StkFloat getParameter(STK_PARAMETERS parameter) const { return parameters[parameter]; }
	virtual void setParameter(STK_PARAMETERS parameter, stk::StkFloat value);
	void loadParameters(stk::StkFloat *parameters);
	void saveParameters(stk::StkFloat *parameters);
	void addEffect(FX *fx);
	void removeEffect(FX *fx);

protected:
	stk::StkFloat parameters[STK_PARAMETERS_MAX];
	std::vector<FX *> effects;

	void initialiseFilter(MultiFilter &filter, stk::ADSR& filterEnvelope);
	void initialiseEnvelope(stk::ADSR& envelope);
	void setFilter(MultiFilter &filter, stk::ADSR& filterEnvelope, STK_PARAMETERS parameter, stk::StkFloat value);
	void setEnvelope(stk::ADSR& envelope, STK_PARAMETERS parameter, stk::StkFloat value);
};

#endif // _PARAMETRICOSC_H

