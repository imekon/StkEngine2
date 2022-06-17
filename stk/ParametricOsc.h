#ifndef _PARAMETRICOSC_H
#define _PARAMETRICOSC_H

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

