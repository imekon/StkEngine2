#include "Synth.h"
#include "MIDIConfiguration.h"
#include "MIDIOutScript.h"
#include "ScriptUtilities.h"

MIDIOutput *MIDIOutScript::output = nullptr;

duk_ret_t MIDIOutScript::midiOutput(duk_context* context)
{
	if (duk_is_constructor_call(context))
	{
		int device = duk_get_int(context, 0);
		auto output = new MIDIOutput(device);
		ScriptUtilities::registerProperty(context, NATIVE_POINTER, output);
		ScriptUtilities::registerDestructor(context, destroyMidiOut);
		return 1;
	}

	return 0;
}

duk_ret_t MIDIOutScript::send(duk_context* context)
{
	int data1 = duk_get_int(context, 0);
	int data2 = duk_get_int(context, 1);
	int data3 = duk_get_int(context, 2);

	duk_push_this(context);
	duk_get_prop_string(context, -1, NATIVE_POINTER);
	auto output = static_cast<MIDIOutput *>(duk_to_pointer(context, -1));

	output->send(data1, data2, data3);

	return 0;
}

duk_ret_t MIDIOutScript::destroyMidiOut(duk_context* context)
{
	duk_get_prop_string(context, 0, NATIVE_POINTER);
	auto output = static_cast<MIDIOutput *>(duk_to_pointer(context, -1));
	duk_pop(context);

	if (output)
	{
		delete output;

		duk_push_pointer(context, nullptr);
		duk_get_prop_string(context, 0, NATIVE_POINTER);
		duk_pop(context);

	}

	return 0;
}

