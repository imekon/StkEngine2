#include "StkScript.h"
#include "ParametricObjectScript.h"
#include "SystemScript.h"
#include "Utilities.h"
#include "MIDIConfigScript.h"
#include "ControlsScript.h"

StkScript::StkScript(): context(nullptr), errorCode(0)
{

}

void StkScript::initialise()
{
	context = duk_create_heap_default();

	SystemScript::initialise();

	SystemScript::loadLibrary(context);
	ParametricObjectScript::loadLibrary(context);
	MIDIConfigScript::loadLibrary(context);
	ControlsScript::loadLibrary(context);
}

void StkScript::shutdown()
{
	duk_destroy_heap(context);
	context = nullptr;

	SystemScript::shutdown();
}

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

