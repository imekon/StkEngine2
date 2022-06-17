#ifndef _SYNTH_H
#define _SYNTH_H

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

#include <windows.h>

#include "Stk.h"
#include "StkParameters.h"
#include "StkGlobals.h"

#include "FX.h"

#define NATIVE_POINTER "\xff\xffpointer"

class ParametricOsc;
class MIDIInput;
class MIDIOutput;

extern "C"
{
	struct SynthReturn
	{
		int errorCode;
		char errorMessage[256];
	};

	extern SynthReturn __stdcall StkScriptInitialise();
	extern SynthReturn __stdcall StkScriptShutdown();
	extern SynthReturn __stdcall StkScriptReadFile(const char *filename);
	extern SynthReturn __stdcall StkScriptEvaluate(const char *text);

	extern void __stdcall Initialise();
	extern void __stdcall Shutdown();
	extern void __stdcall Start();
	extern void __stdcall Stop();

	extern const char * __stdcall GetEngineVersion(int version);

	extern int __stdcall GetMessageCount();
	extern const char * __stdcall GetMessageText();
	extern BOOL __stdcall GetControlFlag(int index);
	extern void __stdcall SetControlFlag(int index, BOOL flag);
	extern double __stdcall GetControlValue(int index);
	extern void __stdcall SetControlValue(int index, double value);
	extern void __stdcall SetTempo(stk::StkFloat tempo, int steps);
	extern bool __stdcall WaitTick();
	extern bool __stdcall WaitText();
	extern double __stdcall GetGlobalParam(STK_GLOBALS global);
	extern void __stdcall SetGlobalParam(STK_GLOBALS global, double value);

	extern ParametricOsc * __stdcall CreateSynth();
	extern ParametricOsc * __stdcall CreateSamplerSynth();
	extern void __stdcall DestroySynth(ParametricOsc *osc);

	extern FX * __stdcall CreateEchoEffect();
	extern FX * __stdcall CreateChorusEffect();
	extern void __stdcall DestroyEffect(FX *effect);

	extern void __stdcall OscAddEffect(ParametricOsc *osc, FX *effect);
	extern void __stdcall OscRemoveEffect(ParametricOsc *osc, FX *effect);

	extern void __stdcall SetOscParam(ParametricOsc *osc, STK_PARAMETERS parameter, stk::StkFloat value);
	extern stk::StkFloat __stdcall GetOscParam(ParametricOsc *osc, STK_PARAMETERS parameter);

	extern void __stdcall LoadParams(ParametricOsc *osc, stk::StkFloat *params);
	extern void __stdcall SaveParams(ParametricOsc *osc, stk::StkFloat *params);

	extern void __stdcall SetEffectParam(FX *effect, STK_EFFECT_PARAMETERS parameter, stk::StkFloat value);
	extern stk::StkFloat __stdcall GetEffectParam(FX *effect, STK_EFFECT_PARAMETERS parameter);

	extern void __stdcall NoteOn(ParametricOsc *osc, int note, stk::StkFloat amplitude);
	extern void __stdcall NoteOff(ParametricOsc *osc, int note, stk::StkFloat amplitude);

	extern int __stdcall MIDIGetInputDeviceCount();
	extern int __stdcall MIDIGetOutputDeviceCount();

	extern void __stdcall MIDIGetInputDeviceName(int device, char *name, int size);
	extern void __stdcall MIDIGetOutputDeviceName(int device, char *name, int size);

	extern MIDIInput * __stdcall MIDICreateInput(int device);
	extern int __stdcall MIDIGetInput(MIDIInput *input, int index);
	extern void __stdcall MIDICloseInput(MIDIInput *input);

	extern MIDIOutput * __stdcall MIDICreateOutput(int device);
	extern void __stdcall MIDISendOutput(MIDIOutput *, int control, int data1, int data2);
	extern void __stdcall MIDICloseOutput(MIDIOutput *output);
}

#endif // _SYNTH_H

