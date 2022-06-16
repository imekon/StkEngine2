#ifndef _MIDIINSCRIPT_H
#define _MIDIINSCRIPT_H

#include <duktape.h>

#include "MIDIInput.h"

class MIDIInScript
{
public:
	static duk_ret_t midiInput(duk_context *context);
	static duk_ret_t destroyMidiIn(duk_context *context);
	static duk_ret_t getInput(duk_context *context);

private:
	static MIDIInput *input;
};

#endif // _MIDIINSCRIPT_H

