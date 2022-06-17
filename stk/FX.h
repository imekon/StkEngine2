#ifndef _FX_H
#define _FX_H

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
#include "Effect.h"
#include "STKParameters.h"

class FX
{
public:
	explicit FX();
	virtual ~FX();

	void setBypass(bool value);
	bool getBypass() const { return bypass; }

	virtual void setEffectMix(stk::StkFloat mix) = 0;
	virtual stk::StkFloat tick(stk::StkFloat input, int channel = 0) = 0;

	stk::StkFloat getParameter(STK_EFFECT_PARAMETERS parameter) const { return parameters[parameter]; }
	virtual void setParameter(STK_EFFECT_PARAMETERS parameter, stk::StkFloat value);

protected:
	bool bypass;
	stk::StkFloat parameters[STK_EFFECT_MAX];
};

#endif // _FX_H
