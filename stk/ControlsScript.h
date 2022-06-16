#ifndef _CONTROLSSCRIPT_H
#define _CONTROLSSCRIPT_H

#include "duktape.h"

class ControlsScript
{
public:
	static void loadLibrary(duk_context *context);

	static duk_ret_t getFlag(duk_context *context);
	static duk_ret_t setFlag(duk_context *context);
	static duk_ret_t getValue(duk_context *context);
	static duk_ret_t setValue(duk_context *context);
};

#endif // _CONTROLSSCRIPT_H

