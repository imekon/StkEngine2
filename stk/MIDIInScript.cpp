#include "Synth.h"
#include "MIDIConfiguration.h"
#include "MIDIInScript.h"
#include "ScriptUtilities.h"

MIDIInput *MIDIInScript::input = nullptr;

duk_ret_t MIDIInScript::midiInput(duk_context * context)
{
	if (duk_is_constructor_call(context))
	{
		int device = duk_get_int(context, 0);
		auto input = new MIDIInput(device);
		ScriptUtilities::registerProperty(context, NATIVE_POINTER, input);
		ScriptUtilities::registerDestructor(context, destroyMidiIn);
		return 1;
	}

	return 0;
}

duk_ret_t MIDIInScript::destroyMidiIn(duk_context * context)
{
	duk_get_prop_string(context, 0, NATIVE_POINTER);
	auto input = static_cast<MIDIInput *>(duk_to_pointer(context, -1));
	duk_pop(context);

	if (input)
	{
		delete input;

		duk_push_pointer(context, nullptr);
		duk_get_prop_string(context, 0, NATIVE_POINTER);
		duk_pop(context);

	}

	return 0;
}

duk_ret_t MIDIInScript::getInput(duk_context * context)
{
	int index = duk_get_int(context, 0);

	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto input = static_cast<MIDIInput *>(duk_to_pointer(context, -1));

	if (input)
	{
		int value = input->GetInput(index);
		duk_push_int(context, value);
	}

	return 0;
}

