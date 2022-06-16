#include "ScriptUtilities.h"
#include "ParametricObjectScript.h"
#include "Synth.h"
#include "Utilities.h"
#include "SimpleSampler.h"
#include "ChorusFX.h"

static const duk_function_list_entry parametricObjectLibrary[] =
{
	"Initialise",	ParametricObjectScript::initialise,		0,
	"Shutdown",		ParametricObjectScript::shutdown,		0,
	"Start",		ParametricObjectScript::start,			0,
	"Stop",			ParametricObjectScript::stop,			0,
	"SetTempo",		ParametricObjectScript::setTempo,		2,
	"SetRawPath",	ParametricObjectScript::setRawPath,		1,
	"MultiOsc",		ParametricObjectScript::multiOsc,		0,
	"SamplerOsc",	ParametricObjectScript::samplerOsc,		0,
	"EchoEffect",	ParametricObjectScript::echoEffect,		0,
	"ChorusEffect", ParametricObjectScript::chorusEffect,	0,

	nullptr,		nullptr,								0
};

void ParametricObjectScript::loadLibrary(duk_context* context)
{
	ScriptUtilities::loadLibrary(context, "Stk", parametricObjectLibrary);
}

duk_ret_t ParametricObjectScript::initialise(duk_context* context)
{
	Initialise();

	return 0;
}

duk_ret_t ParametricObjectScript::shutdown(duk_context* context)
{
	Shutdown();

	return 0;
}

duk_ret_t ParametricObjectScript::start(duk_context* context)
{
	Start();

	return 0;
}

duk_ret_t ParametricObjectScript::stop(duk_context* context)
{
	Stop();

	return 0;
}

duk_ret_t ParametricObjectScript::setRawPath(duk_context* context)
{
	std::string path = duk_get_string(context, 0);

	stk::Stk::setRawwavePath(path.c_str());

	return 0;
}

duk_ret_t ParametricObjectScript::setTempo(duk_context* context)
{
	stk::StkFloat tempo = duk_get_number(context, 0);
	int steps = duk_get_int(context, 1);

	SetTempo(tempo, steps);

	return 0;
}

void ParametricObjectScript::genericOscParams(duk_context* context)
{
	ScriptUtilities::registerProperty(context, "FilterType", getFilterType, setFilterType);
	ScriptUtilities::registerProperty(context, "FilterCutoff", getFilterCutoff, setFilterCutoff);
	ScriptUtilities::registerProperty(context, "FilterQ", getFilterResonance, setFilterResonance);

	ScriptUtilities::registerProperty(context, "EnvAttack", getEnvelopeAttack, setEnvelopeAttack);
	ScriptUtilities::registerProperty(context, "EnvDecay", getEnvelopeDecay, setEnvelopeDecay);
	ScriptUtilities::registerProperty(context, "EnvSustain", getEnvelopeSustain, setEnvelopeSustain);
	ScriptUtilities::registerProperty(context, "EnvRelease", getEnvelopeRelease, setEnvelopeRelease);

	ScriptUtilities::registerProperty(context, "FilterAttack", getFilterEnvelopeAttack, setFilterEnvelopeAttack);
	ScriptUtilities::registerProperty(context, "FilterDecay", getFilterEnvelopeDecay, setFilterEnvelopeDecay);
	ScriptUtilities::registerProperty(context, "FilterSustain", getFilterEnvelopeSustain, setFilterEnvelopeSustain);
	ScriptUtilities::registerProperty(context, "FilterRelease", getFilterEnvelopeRelease, setFilterEnvelopeRelease);
	ScriptUtilities::registerProperty(context, "FilterEnvMix", getFilterEnvelopeMix, setFilterEnvelopeMix);

	ScriptUtilities::registerProperty(context, "Panning", getPanning, setPanning);

	ScriptUtilities::registerProperty(context, "ReverbMix", getReverbMix, setReverbMix);

	ScriptUtilities::registerPropertyFunction(context, "SetParameter", setParameter, 2);
	ScriptUtilities::registerPropertyFunction(context, "GetParameter", setParameter, 1);
	ScriptUtilities::registerPropertyFunction(context, "NoteOn", noteOn, 2);
	ScriptUtilities::registerPropertyFunction(context, "NoteOff", noteOff, 2);

	ScriptUtilities::registerPropertyFunction(context, "AddEffect", addEffect, 1);
	ScriptUtilities::registerPropertyFunction(context, "RemoveEffect", removeEffect, 1);
}

void ParametricObjectScript::genericEffectParams(duk_context* context)
{
	ScriptUtilities::registerProperty(context, "Bypass", getBypass, setBypass);
}

duk_ret_t ParametricObjectScript::multiOsc(duk_context* context)
{
	if (duk_is_constructor_call(context))
	{
		auto osc = CreateSynth();

		ScriptUtilities::registerProperty(context, NATIVE_POINTER, osc);

		ScriptUtilities::registerProperty(context, "Osc1Type", getOsc1Type, setOsc1Type);
		ScriptUtilities::registerProperty(context, "Osc1Gain", getSawGain, setSawGain);
		ScriptUtilities::registerProperty(context, "Osc1Coarse", getSawCoarse, setSawCoarse);
		ScriptUtilities::registerProperty(context, "Osc1Fine", getSawFine, setSawFine);

		ScriptUtilities::registerProperty(context, "Osc2Type", getOsc2Type, setOsc2Type);
		ScriptUtilities::registerProperty(context, "Osc2Gain", getSquareGain, setSquareGain);
		ScriptUtilities::registerProperty(context, "Osc2Coarse", getSquareCoarse, setSquareCoarse);
		ScriptUtilities::registerProperty(context, "Osc2Fine", getSquareFine, setSquareFine);

		ScriptUtilities::registerProperty(context, "Osc3Type", getOsc3Type, setOsc3Type);
		ScriptUtilities::registerProperty(context, "Osc3Gain", getOsc3Gain, setOsc3Gain);
		ScriptUtilities::registerProperty(context, "Osc3Coarse", getOsc3Coarse, setOsc3Coarse);
		ScriptUtilities::registerProperty(context, "Osc3Fine", getOsc3Fine, setOsc3Fine);

		genericOscParams(context);

		ScriptUtilities::registerDestructor(context, destroyOsc);

		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::samplerOsc(duk_context* context)
{
	if (duk_is_constructor_call(context))
	{
		auto osc = CreateSamplerSynth();

		ScriptUtilities::registerProperty(context, NATIVE_POINTER, osc);

		genericOscParams(context);

		ScriptUtilities::registerProperty(context, "Filename", getRawFile, setRawFile);

		ScriptUtilities::registerDestructor(context, destroyOsc);

		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::destroyOsc(duk_context *context)
{
	duk_get_prop_string(context, 0, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_to_pointer(context, -1));
	duk_pop(context);

	if (osc)
	{
		DestroySynth(osc);

		duk_push_pointer(context, nullptr);
		duk_get_prop_string(context, 0, NATIVE_POINTER);
		duk_pop(context);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::echoEffect(duk_context* context)
{
	if (duk_is_constructor_call(context))
	{
		auto fx = CreateEchoEffect();

		ScriptUtilities::registerProperty(context, NATIVE_POINTER, fx);

		genericEffectParams(context);

		ScriptUtilities::registerDestructor(context, destroyEffect);

		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::chorusEffect(duk_context* context)
{
	if (duk_is_constructor_call(context))
	{
		auto fx = CreateChorusEffect();

		ScriptUtilities::registerProperty(context, NATIVE_POINTER, fx);

		genericEffectParams(context);

		ScriptUtilities::registerProperty(context, "ModSpeed", getChorusModFreq, setChorusModFreq);
		ScriptUtilities::registerProperty(context, "ModDepth", getChorusModDepth, setChorusModDepth);

		ScriptUtilities::registerDestructor(context, destroyEffect);

		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::destroyEffect(duk_context* context)
{
	duk_get_prop_string(context, 0, NATIVE_POINTER);
	auto fx = static_cast<FX *>(duk_to_pointer(context, -1));
	duk_pop(context);

	if (fx)
	{
		DestroyEffect(fx);

		duk_push_pointer(context, nullptr);
		duk_get_prop_string(context, 0, NATIVE_POINTER);
		duk_pop(context);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setParameter(duk_context* context)
{
	STK_PARAMETERS parameter = static_cast<STK_PARAMETERS>(duk_get_int(context, 0));
	stk::StkFloat value = duk_get_number(context, 1);

	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));

	if (osc)
	{
		SetOscParam(osc, parameter, value);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getParameter(duk_context* context)
{
	STK_PARAMETERS parameter = static_cast<STK_PARAMETERS>(duk_get_int(context, 0));

	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));

	if (osc)
	{
		stk::StkFloat value = GetOscParam(osc, parameter);

		duk_push_number(context, value);

		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getOsc1Type(duk_context* context)
{
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		stk::StkFloat value = GetOscParam(osc, STK_PARAMETER_OSC1_TYPE);
		duk_push_number(context, value);
		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setOsc1Type(duk_context* context)
{
	stk::StkFloat value = duk_get_number(context, 0);
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		SetOscParam(osc, STK_PARAMETER_OSC1_TYPE, value);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getSawGain(duk_context* context)
{
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		stk::StkFloat value = GetOscParam(osc, STK_PARAMETER_OSC1_GAIN);
		duk_push_number(context, value);
		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setSawGain(duk_context* context)
{
	stk::StkFloat value = duk_get_number(context, 0);
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		SetOscParam(osc, STK_PARAMETER_OSC1_GAIN, value);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getSawCoarse(duk_context* context)
{
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		stk::StkFloat value = GetOscParam(osc, STK_PARAMETER_OSC1_COARSE);
		duk_push_number(context, value);
		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setSawCoarse(duk_context* context)
{
	stk::StkFloat value = duk_get_number(context, 0);
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		SetOscParam(osc, STK_PARAMETER_OSC1_COARSE, value);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getSawFine(duk_context* context)
{
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		stk::StkFloat value = GetOscParam(osc, STK_PARAMETER_OSC1_FINE);
		duk_push_number(context, value);
		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setSawFine(duk_context* context)
{
	stk::StkFloat value = duk_get_number(context, 0);
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		SetOscParam(osc, STK_PARAMETER_OSC1_FINE, value);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getOsc2Type(duk_context* context)
{
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		stk::StkFloat value = GetOscParam(osc, STK_PARAMETER_OSC2_TYPE);
		duk_push_number(context, value);
		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setOsc2Type(duk_context* context)
{
	stk::StkFloat value = duk_get_number(context, 0);
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		SetOscParam(osc, STK_PARAMETER_OSC2_TYPE, value);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getSquareGain(duk_context* context)
{
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		stk::StkFloat value = GetOscParam(osc, STK_PARAMETER_OSC2_GAIN);
		duk_push_number(context, value);
		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setSquareGain(duk_context* context)
{
	stk::StkFloat value = duk_get_number(context, 0);
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		SetOscParam(osc, STK_PARAMETER_OSC2_GAIN, value);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getSquareCoarse(duk_context* context)
{
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		stk::StkFloat value = GetOscParam(osc, STK_PARAMETER_OSC2_COARSE);
		duk_push_number(context, value);
		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setSquareCoarse(duk_context* context)
{
	stk::StkFloat value = duk_get_number(context, 0);
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		SetOscParam(osc, STK_PARAMETER_OSC2_COARSE, value);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getSquareFine(duk_context* context)
{
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		stk::StkFloat value = GetOscParam(osc, STK_PARAMETER_OSC2_FINE);
		duk_push_number(context, value);
		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setSquareFine(duk_context* context)
{
	stk::StkFloat value = duk_get_number(context, 0);
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		SetOscParam(osc, STK_PARAMETER_OSC2_FINE, value);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getOsc3Type(duk_context* context)
{
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		stk::StkFloat value = GetOscParam(osc, STK_PARAMETER_OSC3_TYPE);
		duk_push_number(context, value);
		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setOsc3Type(duk_context* context)
{
	stk::StkFloat value = duk_get_number(context, 0);
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		SetOscParam(osc, STK_PARAMETER_OSC3_TYPE, value);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getOsc3Gain(duk_context* context)
{
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		stk::StkFloat value = GetOscParam(osc, STK_PARAMETER_OSC3_GAIN);
		duk_push_number(context, value);
		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setOsc3Gain(duk_context* context)
{
	stk::StkFloat value = duk_get_number(context, 0);
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		SetOscParam(osc, STK_PARAMETER_OSC3_GAIN, value);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getOsc3Coarse(duk_context* context)
{
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		stk::StkFloat value = GetOscParam(osc, STK_PARAMETER_OSC3_COARSE);
		duk_push_number(context, value);
		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setOsc3Coarse(duk_context* context)
{
	stk::StkFloat value = duk_get_number(context, 0);
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		SetOscParam(osc, STK_PARAMETER_OSC3_COARSE, value);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getOsc3Fine(duk_context* context)
{
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		stk::StkFloat value = GetOscParam(osc, STK_PARAMETER_OSC3_FINE);
		duk_push_number(context, value);
		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setOsc3Fine(duk_context* context)
{
	stk::StkFloat value = duk_get_number(context, 0);
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		SetOscParam(osc, STK_PARAMETER_OSC3_FINE, value);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getRawFile(duk_context* context)
{
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<SimpleSampler *>(duk_get_pointer(context, -1));
	if (osc)
	{
		auto filename = osc->getRawFile();

		duk_push_string(context, filename);

		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setRawFile(duk_context* context)
{
	std::string filename = duk_get_string(context, 0);
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<SimpleSampler *>(duk_get_pointer(context, -1));
	if (osc)
	{
		osc->setRawFile(filename.c_str());
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getFilterType(duk_context* context)
{
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		stk::StkFloat value = GetOscParam(osc, STK_FILTER_TYPE);
		duk_push_number(context, value);
		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setFilterType(duk_context* context)
{
	stk::StkFloat value = duk_get_number(context, 0);
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		SetOscParam(osc, STK_FILTER_RES, value);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getFilterCutoff(duk_context* context)
{
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		stk::StkFloat value = GetOscParam(osc, STK_FILTER_CUTOFF);
		duk_push_number(context, value);
		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setFilterCutoff(duk_context* context)
{
	stk::StkFloat value = duk_get_number(context, 0);
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		SetOscParam(osc, STK_FILTER_CUTOFF, value);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getFilterResonance(duk_context* context)
{
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		stk::StkFloat value = GetOscParam(osc, STK_FILTER_RES);
		duk_push_number(context, value);
		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setFilterResonance(duk_context* context)
{
	stk::StkFloat value = duk_get_number(context, 0);
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		SetOscParam(osc, STK_FILTER_RES, value);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getEnvelopeAttack(duk_context* context)
{
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		stk::StkFloat value = GetOscParam(osc, STK_AMP_ENVELOPE_ATTACK);
		duk_push_number(context, value);
		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setEnvelopeAttack(duk_context* context)
{
	stk::StkFloat value = duk_get_number(context, 0);
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		SetOscParam(osc, STK_AMP_ENVELOPE_ATTACK, value);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getEnvelopeDecay(duk_context* context)
{
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		stk::StkFloat value = GetOscParam(osc, STK_AMP_ENVELOPE_DECAY);
		duk_push_number(context, value);
		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setEnvelopeDecay(duk_context* context)
{
	stk::StkFloat value = duk_get_number(context, 0);
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		SetOscParam(osc, STK_AMP_ENVELOPE_DECAY, value);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getEnvelopeSustain(duk_context* context)
{
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		stk::StkFloat value = GetOscParam(osc, STK_AMP_ENVELOPE_SUSTAIN);
		duk_push_number(context, value);
		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setEnvelopeSustain(duk_context* context)
{
	stk::StkFloat value = duk_get_number(context, 0);
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		SetOscParam(osc, STK_AMP_ENVELOPE_SUSTAIN, value);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getEnvelopeRelease(duk_context* context)
{
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		stk::StkFloat value = GetOscParam(osc, STK_AMP_ENVELOPE_RELEASE);
		duk_push_number(context, value);
		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setEnvelopeRelease(duk_context* context)
{
	stk::StkFloat value = duk_get_number(context, 0);
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		SetOscParam(osc, STK_AMP_ENVELOPE_RELEASE, value);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getFilterEnvelopeAttack(duk_context* context)
{
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		stk::StkFloat value = GetOscParam(osc, STK_FILTER_ENVELOPE_ATTACK);
		duk_push_number(context, value);
		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setFilterEnvelopeAttack(duk_context* context)
{
	stk::StkFloat value = duk_get_number(context, 0);
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		SetOscParam(osc, STK_FILTER_ENVELOPE_ATTACK, value);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getFilterEnvelopeDecay(duk_context* context)
{
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		stk::StkFloat value = GetOscParam(osc, STK_FILTER_ENVELOPE_DECAY);
		duk_push_number(context, value);
		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setFilterEnvelopeDecay(duk_context* context)
{
	stk::StkFloat value = duk_get_number(context, 0);
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		SetOscParam(osc, STK_FILTER_ENVELOPE_DECAY, value);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getFilterEnvelopeSustain(duk_context* context)
{
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		stk::StkFloat value = GetOscParam(osc, STK_FILTER_ENVELOPE_SUSTAIN);
		duk_push_number(context, value);
		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setFilterEnvelopeSustain(duk_context* context)
{
	stk::StkFloat value = duk_get_number(context, 0);
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		SetOscParam(osc, STK_FILTER_ENVELOPE_SUSTAIN, value);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getFilterEnvelopeRelease(duk_context* context)
{
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		stk::StkFloat value = GetOscParam(osc, STK_FILTER_ENVELOPE_RELEASE);
		duk_push_number(context, value);
		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setFilterEnvelopeRelease(duk_context* context)
{
	stk::StkFloat value = duk_get_number(context, 0);
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		SetOscParam(osc, STK_FILTER_ENVELOPE_RELEASE, value);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getFilterEnvelopeMix(duk_context* context)
{
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		stk::StkFloat value = GetOscParam(osc, STK_FILTER_ENVELOPE_MIX);
		duk_push_number(context, value);
		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setFilterEnvelopeMix(duk_context* context)
{
	stk::StkFloat value = duk_get_number(context, 0);
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		SetOscParam(osc, STK_FILTER_ENVELOPE_MIX, value);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getPanning(duk_context* context)
{
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		stk::StkFloat value = GetOscParam(osc, STK_PARAMETER_PANNING);
		duk_push_number(context, value);
		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setPanning(duk_context* context)
{
	stk::StkFloat value = duk_get_number(context, 0);
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		SetOscParam(osc, STK_PARAMETER_PANNING, value);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getReverbMix(duk_context* context)
{
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		stk::StkFloat value = GetOscParam(osc, STK_REVERB_MIX);
		duk_push_number(context, value);
		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setReverbMix(duk_context* context)
{
	stk::StkFloat value = duk_get_number(context, 0);
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));
	if (osc)
	{
		SetOscParam(osc, STK_REVERB_MIX, value);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getBypass(duk_context* context)
{
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto effect = static_cast<FX *>(duk_get_pointer(context, -1));

	if (effect)
	{
		auto bypass = GetEffectParam(effect, STK_EFFECT_BYPASS);
		duk_push_boolean(context, bypass > 0.0);
		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setBypass(duk_context* context)
{
	bool value = duk_get_boolean(context, 0) != 0;

	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto effect = static_cast<FX *>(duk_get_pointer(context, -1));

	if (effect)
	{
		effect->setBypass(value);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getChorusModFreq(duk_context* context)
{
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto effect = static_cast<ChorusFX *>(duk_get_pointer(context, -1));
	if (effect)
	{
		auto value = GetEffectParam(effect, STK_EFFECT_MOD_FREQ);
		duk_push_number(context, value);
		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setChorusModFreq(duk_context* context)
{
	stk::StkFloat value = duk_get_number(context, 0);
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto effect = static_cast<ChorusFX *>(duk_get_pointer(context, -1));
	if (effect)
	{
		SetEffectParam(effect, STK_EFFECT_MOD_FREQ, value);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::getChorusModDepth(duk_context* context)
{
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto effect = static_cast<ChorusFX *>(duk_get_pointer(context, -1));
	if (effect)
	{
		auto value = GetEffectParam(effect, STK_EFFECT_MOD_DEPTH);
		duk_push_number(context, value);
		return 1;
	}

	return 0;
}

duk_ret_t ParametricObjectScript::setChorusModDepth(duk_context* context)
{
	stk::StkFloat value = duk_get_number(context, 0);
	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto effect = static_cast<ChorusFX *>(duk_get_pointer(context, -1));
	if (effect)
	{
		SetEffectParam(effect, STK_EFFECT_MOD_DEPTH, value);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::noteOn(duk_context* context)
{
	int note = duk_get_int(context, 0);
	stk::StkFloat amplitude = duk_get_number(context, 1);

	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));

	if (osc)
	{
		Utilities::trace("Note On: %d %1.2f\n", note, amplitude);

		NoteOn(osc, note, amplitude);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::noteOff(duk_context* context)
{
	int note = duk_get_int(context, 0);
	stk::StkFloat amplitude = duk_get_number(context, 1);

	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));

	if (osc)
	{
		Utilities::trace("Note Off: %d %1.2f\n", note, amplitude);

		NoteOff(osc, note, amplitude);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::addEffect(duk_context* context)
{
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto effect = static_cast<FX *>(duk_get_pointer(context, -1));

	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));

	if (osc && effect)
	{
		OscAddEffect(osc, effect);
	}

	return 0;
}

duk_ret_t ParametricObjectScript::removeEffect(duk_context* context)
{
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto effect = static_cast<FX *>(duk_get_pointer(context, -1));

	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto osc = static_cast<ParametricOsc *>(duk_get_pointer(context, -1));

	if (osc && effect)
	{
		OscRemoveEffect(osc, effect);
	}

	return 0;
}

