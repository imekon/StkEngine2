#include "ControlsScript.h"
#include "ScriptUtilities.h"
#include "Synth.h"

static const duk_function_list_entry controlsScriptLibrary[] =
{
	"GetFlag",			ControlsScript::getFlag,		1,
	"SetFlag",			ControlsScript::setFlag,		2,
	"GetValue",			ControlsScript::getValue,		1,
	"SetValue",			ControlsScript::setValue,		2,
	nullptr,			nullptr,						0
};


void ControlsScript::loadLibrary(duk_context* context)
{
	ScriptUtilities::loadLibrary(context, "Controls", controlsScriptLibrary);
}

duk_ret_t ControlsScript::getFlag(duk_context* context)
{
	int index = duk_get_int(context, 0);
	bool flag = GetControlFlag(index) != 0;
	duk_push_boolean(context, flag);
	return 1;
}

duk_ret_t ControlsScript::setFlag(duk_context* context)
{
	int index = duk_get_int(context, 0);
	bool flag = duk_get_boolean(context, 1) != 0;
	SetControlFlag(index, flag);
	return 0;
}

duk_ret_t ControlsScript::getValue(duk_context* context)
{
	int index = duk_get_int(context, 0);
	double value = GetControlValue(index);
	duk_push_number(context, value);
	return 1;
}

duk_ret_t ControlsScript::setValue(duk_context* context)
{
	int index = duk_get_int(context, 0);
	double value = duk_get_number(context, 1);
	SetControlValue(index, value);
	return 0;
}
