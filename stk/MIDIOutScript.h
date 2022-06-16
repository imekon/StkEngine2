#ifndef _MIDIOUTSCRIPT_H
#define _MIDIOUTSCRIPT_H

#include <duktape.h>

#include "MIDIOutput.h"

class MIDIOutScript
{
public:
	static void loadLibrary(duk_context *context);

	static duk_ret_t midiOutput(duk_context *context);
	static duk_ret_t destroyMidiOut(duk_context *context);
	static duk_ret_t send(duk_context *context);

private:
	static MIDIOutput *output;
};

#endif // _MIDIOUTSCRIPT_H
