#include "StkScript.h"
#include "ParametricObjectScript.h"
#include "SystemScript.h"
#include "Utilities.h"
#include "MIDIConfigScript.h"
#include "ControlsScript.h"

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

StkScript::StkScript(): 
#ifdef DUKTAPE_ENABLE
	context(nullptr),
#endif
	errorCode(0)
{

}

void StkScript::initialise()
{
#ifdef DUKTAPE_ENABLE
	context = duk_create_heap_default();
#endif

	SystemScript::initialise();

#ifdef DUKTAPE_ENABLE
	SystemScript::loadLibrary(context);
	ParametricObjectScript::loadLibrary(context);
	MIDIConfigScript::loadLibrary(context);
	ControlsScript::loadLibrary(context);
#endif
}

void StkScript::shutdown()
{
#ifdef DUKTAPE_ENABLE
	duk_destroy_heap(context);

	context = nullptr;
#endif

	SystemScript::shutdown();
}

#ifdef DUKTAPE_ENABLE
void StkScript::push_file_as_string(const char *filename)
{
	FILE *f;
	size_t len;
	char buf[16384];

	f = fopen(filename, "rb");
	if (f)
	{
		len = fread((void *)buf, 1, sizeof(buf), f);
		fclose(f);
		duk_push_lstring(context, (const char *)buf, (duk_size_t)len);
	}
	else
	{
		duk_push_undefined(context);
	}
}

void StkScript::readfile(const char* filename)
{
	errorCode = 0;

	push_file_as_string(filename);
	if (duk_peval(context) != 0)
	{
		errorMessage = duk_safe_to_string(context, -1);
		errorCode = -1;
	}

	duk_pop(context);
}

void StkScript::invokeTick()
{
	duk_push_global_object(context);
	duk_get_prop_string(context, -1, "tick");
	if (duk_pcall(context, 0) != 0)
	{
		errorMessage = std::string("Running 'tick': ") + duk_safe_to_string(context, -1);
		errorCode = -1;
	}
	duk_pop(context);
}

std::string StkScript::evaluate(const char* text) const
{
	const char *result = "";

	Utilities::trace("Input: %s\n", text);

	if (duk_peval_string(context, text) != 0)
	{
		result = duk_safe_to_string(context, -1);
		Utilities::trace("Result: %s\n", result);
	}

	return result;
}
#endif
