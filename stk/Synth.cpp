#include "StkParameters.h"
#include "StkEngine.h"
#include "Utilities.h"
#include "Synth.h"
#include "StkScript.h"
#include "SystemScript.h"
#include "Controls.h"
#include "STK_VERSION.h"
#include "MultiOsc.h"
#include "SimpleSampler.h"
#include "EchoFX.h"
#include "ChorusFX.h"
#include "MIDIConfiguration.h"
#include "MIDIInput.h"
#include "MIDIOutput.h"

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


//#define DUKTAPE_ENABLE

StkEngine *engine = nullptr;
StkScript *script = nullptr;
Controls *controls = new Controls();

extern "C"
{
	SynthReturn __stdcall StkScriptInitialise()
	{
		SynthReturn result;

#ifdef DUKTAPE_ENABLE
		script = new StkScript();

		script->initialise();
#else
		script = nullptr;
#endif

		result.errorCode = 0;
		result.errorMessage[0] = 0;

		return result;
	}

	SynthReturn __stdcall StkScriptShutdown()
	{
		SynthReturn result;

#ifdef DUKTAPE_ENABLE
		script->shutdown();

		delete script;
		script = nullptr;
#endif

		result.errorCode = 0;
		result.errorMessage[0] = 0;

		return result;
	}

	SynthReturn __stdcall StkScriptReadFile(const char *filename)
	{
		SynthReturn result;

#ifdef DUKTAPE_ENABLE
		Utilities::trace("Read file: %s\n", filename);

		script->readfile(filename);
		
		result.errorCode = script->getErrorCode();
		strcpy_s(result.errorMessage, script->getErrorMessage().c_str());
#else
		result.errorCode = 0;
		result.errorMessage[0] = 0;
#endif

		return result;
	}

	SynthReturn __stdcall StkScriptEvaluate(const char *text)
	{
		SynthReturn result;

#ifdef DUKTAPE_ENABLE
		std::string error = script->evaluate(text);
		strcpy_s(result.errorMessage, error.c_str());
		result.errorCode = error.size() != 0;
#else
		result.errorCode = 0;
		result.errorMessage[0] = 0;
#endif

		return result;
	}

	const char * __stdcall GetEngineVersion(int version)
	{
		switch(version)
		{
		case STK_VERSION_DUKTAPE:
#ifdef DUKTAPE_ENABLE
			return DUK_GIT_DESCRIBE;
#endif

		case STK_VERSION_SYNTHESIS:
			return "4.6.2";

		case STK_VERSION_ENGINE:
			return "2.0.0 (17/06/2022)";

		default:
			return "";
		}

		return "";
	}

	const char * __stdcall GetMessageText()
	{
#ifdef DUKTAPE_ENABLE
		return SystemScript::getMessage();
#else
		return "";
#endif
	}

	int __stdcall GetMessageCount()
	{
#ifdef DUKTAPE_ENABLE
		return SystemScript::getMessageCount();
#else
		return 0;
#endif
	}

	void __stdcall Initialise()
	{
		Utilities::trace("Initialise...\n");
		engine = new StkEngine();
	}

	void __stdcall Shutdown()
	{
		Utilities::trace("Shutdown...\n");
		delete engine;
		engine = nullptr;
	}

	void __stdcall Start()
	{
		engine->start();
	}

	void __stdcall Stop()
	{
		engine->stop();
	}

	BOOL __stdcall GetControlFlag(int index)
	{
		if (controls)
			return controls->getFlag(index);

		return false;
	}

	void __stdcall SetControlFlag(int index, BOOL flag)
	{
		if (controls)
			controls->setFlag(index, flag != 0);
	}

	double __stdcall GetControlValue(int index)
	{
		if (controls)
			return controls->getValue(index);

		return 0.0;
	}

	void __stdcall SetControlValue(int index, double value)
	{
		if (controls)
			controls->setValue(index, value);
	}

	double __stdcall GetGlobalParam(STK_GLOBALS global)
	{
		if (engine)
		{
			return engine->getGlobal(global);
		}

		return 0.0;
	}

	void __stdcall SetGlobalParam(STK_GLOBALS global, double value)
	{
		if (engine)
		{
			engine->setGlobal(global, value);
		}
	}

	ParametricOsc * __stdcall CreateSynth()
	{
		auto osc = new MultiOsc();

		engine->addOsc(osc);

		return osc;
	}

	ParametricOsc * __stdcall CreateSamplerSynth()
	{
		auto osc = new SimpleSampler();

		engine->addOsc(osc);

		return osc;
	}

	void __stdcall DestroySynth(ParametricOsc *osc)
	{
		if (engine && engine->removeOsc(osc))
			delete osc;
	}

	FX * __stdcall CreateEchoEffect()
	{
		return new EchoFX();
	}

	FX * __stdcall CreateChorusEffect()
	{
		return new ChorusFX();
	}

	void __stdcall DestroyEffect(FX* effect)
	{
		delete effect;
	}

	void __stdcall OscAddEffect(ParametricOsc *osc, FX *effect)
	{
		if (osc && effect)
		{
			osc->addEffect(effect);
		}
	}

	void __stdcall OscRemoveEffect(ParametricOsc *osc, FX *effect)
	{
		if (osc && effect)
		{
			osc->removeEffect(effect);
		}
	}

	void __stdcall SetTempo(stk::StkFloat tempo, int steps)
	{
		if (engine)
			engine->setTempo(tempo, steps);
	}

	bool __stdcall WaitTick()
	{
		if (engine)
		{
			return engine->waitTick();
		}

		return false;
	}

	bool __stdcall WaitText()
	{
#ifdef DUKTAPE_ENABLE
		return SystemScript::waitText();
#else
		return true;
#endif
	}

	void __stdcall SetOscParam(ParametricOsc *osc, STK_PARAMETERS parameter, stk::StkFloat value)
	{
		osc->setParameter(parameter, value);
	}

	stk::StkFloat __stdcall GetOscParam(ParametricOsc *osc, STK_PARAMETERS parameter)
	{
		return osc->getParameter(parameter);
	}

	void __stdcall LoadParams(ParametricOsc *osc, stk::StkFloat *params)
	{
		osc->loadParameters(params);
	}

	void __stdcall SaveParams(ParametricOsc *osc, stk::StkFloat *params)
	{
		osc->saveParameters(params);
	}

	void __stdcall SetEffectParam(FX *effect, STK_EFFECT_PARAMETERS parameter, stk::StkFloat value)
	{
		effect->setParameter(parameter, value);
	}

	stk::StkFloat __stdcall GetEffectParam(FX *effect, STK_EFFECT_PARAMETERS parameter)
	{
		return effect->getParameter(parameter);
	}

	void __stdcall NoteOn(ParametricOsc *osc, int note, stk::StkFloat amplitude)
	{
		double freq = Utilities::midiToFreq(note);
		osc->noteOn(freq, amplitude);
	}

	void __stdcall NoteOff(ParametricOsc *osc, int note, stk::StkFloat amplitude)
	{
		osc->noteOff(amplitude);
	}

	int __stdcall MIDIGetInputDeviceCount()
	{
		return MIDIConfiguration::GetNumInputDevices();
	}

	int __stdcall MIDIGetOutputDeviceCount()
	{
		return MIDIConfiguration::GetNumOutputDevices();
	}

	void __stdcall MIDIGetInputDeviceName(int device, char *name, int size)
	{
		auto nameStr = MIDIConfiguration::GetInputDeviceName(device);
		strcpy_s(name, size, nameStr.c_str());
	}

	void __stdcall MIDIGetOutputDeviceName(int device, char *name, int size)
	{
		auto nameStr = MIDIConfiguration::GetOutputDeviceName(device);
		strcpy_s(name, size, nameStr.c_str());
	}

	MIDIInput * __stdcall MIDICreateInput(int device)
	{
		auto input = new MIDIInput(device);
		return input;
	}

	int __stdcall MIDIGetInput(MIDIInput *input, int index)
	{
		return input->GetInput(index);
	}

	void __stdcall MIDICloseInput(MIDIInput *input)
	{
		delete input;
	}

	MIDIOutput * __stdcall MIDICreateOutput(int device)
	{
		auto output = new MIDIOutput(device);
		return output;
	}

	void __stdcall MIDISendOutput(MIDIOutput *output, int control, int data1, int data2)
	{
		output->send(control, data1, data2);
	}

	void __stdcall MIDICloseOutput(MIDIOutput *output)
	{
		delete output;
	}
}

