#include "Synth.h"
#include "MIDIConfiguration.h"
#include "MIDIOutScript.h"
#include "ScriptUtilities.h"

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

