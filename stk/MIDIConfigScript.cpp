#include "Synth.h"
#include "MIDIConfiguration.h"
#include "MIDIOutScript.h"
#include "MIDIInScript.h"
#include "MIDIConfigScript.h"
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

