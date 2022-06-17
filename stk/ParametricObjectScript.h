#ifndef _STKSCRIPTOBJECT_H
#define _STKSCRIPTOBJECT_H

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

#ifdef DUKTAPE_ENABLE
#include <duktape.h>

class ParametricObjectScript
{
public:
	static void loadLibrary(duk_context *context);

	static duk_ret_t initialise(duk_context *context);
	static duk_ret_t shutdown(duk_context *context);
	static duk_ret_t start(duk_context *context);
	static duk_ret_t stop(duk_context *context);
	static duk_ret_t setRawPath(duk_context *context);
	static duk_ret_t setTempo(duk_context *context);

	static duk_ret_t multiOsc(duk_context *context);
	static duk_ret_t samplerOsc(duk_context *context);
	static duk_ret_t destroyOsc(duk_context *context);

	static duk_ret_t echoEffect(duk_context *context);
	static duk_ret_t chorusEffect(duk_context *context);
	static duk_ret_t destroyEffect(duk_context *context);

	static duk_ret_t setParameter(duk_context *context);
	static duk_ret_t getParameter(duk_context *context);

	static duk_ret_t getOsc1Type(duk_context *context);
	static duk_ret_t setOsc1Type(duk_context *context);
	static duk_ret_t getSawGain(duk_context *context);
	static duk_ret_t setSawGain(duk_context *context);
	static duk_ret_t getSawCoarse(duk_context *context);
	static duk_ret_t setSawCoarse(duk_context *context);
	static duk_ret_t getSawFine(duk_context *context);
	static duk_ret_t setSawFine(duk_context *context);

	static duk_ret_t getOsc2Type(duk_context *context);
	static duk_ret_t setOsc2Type(duk_context *context);
	static duk_ret_t getSquareGain(duk_context *context);
	static duk_ret_t setSquareGain(duk_context *context);
	static duk_ret_t getSquareCoarse(duk_context *context);
	static duk_ret_t setSquareCoarse(duk_context *context);
	static duk_ret_t getSquareFine(duk_context *context);
	static duk_ret_t setSquareFine(duk_context *context);

	static duk_ret_t getOsc3Type(duk_context *context);
	static duk_ret_t setOsc3Type(duk_context *context);
	static duk_ret_t getOsc3Gain(duk_context *context);
	static duk_ret_t setOsc3Gain(duk_context *context);
	static duk_ret_t getOsc3Coarse(duk_context *context);
	static duk_ret_t setOsc3Coarse(duk_context *context);
	static duk_ret_t getOsc3Fine(duk_context *context);
	static duk_ret_t setOsc3Fine(duk_context *context);

	static duk_ret_t getRawFile(duk_context *context);
	static duk_ret_t setRawFile(duk_context *context);

	static duk_ret_t getFilterType(duk_context *context);
	static duk_ret_t setFilterType(duk_context *context);
	static duk_ret_t getFilterCutoff(duk_context *context);
	static duk_ret_t setFilterCutoff(duk_context *context);
	static duk_ret_t getFilterResonance(duk_context *context);
	static duk_ret_t setFilterResonance(duk_context *context);

	static duk_ret_t getEnvelopeAttack(duk_context *context);
	static duk_ret_t setEnvelopeAttack(duk_context *context);
	static duk_ret_t getEnvelopeDecay(duk_context *context);
	static duk_ret_t setEnvelopeDecay(duk_context *context);
	static duk_ret_t getEnvelopeSustain(duk_context *context);
	static duk_ret_t setEnvelopeSustain(duk_context *context);
	static duk_ret_t getEnvelopeRelease(duk_context *context);
	static duk_ret_t setEnvelopeRelease(duk_context *context);

	static duk_ret_t getFilterEnvelopeAttack(duk_context *context);
	static duk_ret_t setFilterEnvelopeAttack(duk_context *context);
	static duk_ret_t getFilterEnvelopeDecay(duk_context *context);
	static duk_ret_t setFilterEnvelopeDecay(duk_context *context);
	static duk_ret_t getFilterEnvelopeSustain(duk_context *context);
	static duk_ret_t setFilterEnvelopeSustain(duk_context *context);
	static duk_ret_t getFilterEnvelopeRelease(duk_context *context);
	static duk_ret_t setFilterEnvelopeRelease(duk_context *context);
	static duk_ret_t getFilterEnvelopeMix(duk_context *context);
	static duk_ret_t setFilterEnvelopeMix(duk_context *context);

	static duk_ret_t getPanning(duk_context *context);
	static duk_ret_t setPanning(duk_context *context);

	static duk_ret_t getReverbMix(duk_context *context);
	static duk_ret_t setReverbMix(duk_context *context);

	static duk_ret_t getBypass(duk_context *context);
	static duk_ret_t setBypass(duk_context *context);

	static duk_ret_t getChorusModFreq(duk_context *context);
	static duk_ret_t setChorusModFreq(duk_context *context);
	static duk_ret_t getChorusModDepth(duk_context *context);
	static duk_ret_t setChorusModDepth(duk_context *context);

	static duk_ret_t noteOn(duk_context *context);
	static duk_ret_t noteOff(duk_context *context);

	static duk_ret_t addEffect(duk_context *context);
	static duk_ret_t removeEffect(duk_context *context);

	static void genericOscParams(duk_context* context);
	static void genericEffectParams(duk_context* context);
};
#endif

#endif // _STKSCRIPTOBJECT_H
