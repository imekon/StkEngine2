#include "Synth.h"
#include "MIDIConfiguration.h"
#include "MIDIOutScript.h"
#include "MIDIInScript.h"
#include "MIDIConfigScript.h"
#include "ScriptUtilities.h"

static const duk_function_list_entry scriptMIDILibrary[] =
{
	"MIDIInput",		MIDIInScript::midiInput,		1,
	"GetInput",			MIDIInScript::getInput,			1,

	"MIDIOutput",	MIDIOutScript::midiOutput,		1,
	"Send",			MIDIOutScript::send,			3,

	"GetOutputDeviceCount",	MIDIConfigScript::getOutCount, 0,
	"GetOutputDeviceName", MIDIConfigScript::getOutName, 1,
	"GetInputDeviceCount", MIDIConfigScript::getInCount, 0,
	"GetInputDeviceName", MIDIConfigScript::getInName, 1,

	nullptr,		nullptr,						0
};

void MIDIConfigScript::loadLibrary(duk_context* context)
{
	ScriptUtilities::loadLibrary(context, "MIDI", scriptMIDILibrary);
}

duk_ret_t MIDIConfigScript::getInCount(duk_context * context)
{
	int count = MIDIConfiguration::GetNumInputDevices();
	duk_push_int(context, count);
	return 1;
}

duk_ret_t MIDIConfigScript::getInName(duk_context * context)
{
	int device = duk_get_int(context, 0);

	auto name = MIDIConfiguration::GetInputDeviceName(device);

	duk_push_string(context, name.c_str());

	return 1;
}

duk_ret_t MIDIConfigScript::getOutCount(duk_context * context)
{
	int count = MIDIConfiguration::GetNumOutputDevices();
	duk_push_int(context, count);
	return 1;
}

duk_ret_t MIDIConfigScript::getOutName(duk_context * context)
{
	int device = duk_get_int(context, 0);

	auto name = MIDIConfiguration::GetOutputDeviceName(device);

	duk_push_string(context, name.c_str());

	return 1;
}

