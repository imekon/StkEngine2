#ifndef _MIDICONFIGSCRIPT_H
#define _MIDICONFIGSCRIPT_H

#include "duktape.h"

class MIDIConfigScript
{
public:
	static void loadLibrary(duk_context *context);

	static duk_ret_t getInCount(duk_context *context);
	static duk_ret_t getInName(duk_context *context);
	static duk_ret_t getOutCount(duk_context *context);
	static duk_ret_t getOutName(duk_context *context);

};

#endif // _MIDICONFIGSCRIPT_H

