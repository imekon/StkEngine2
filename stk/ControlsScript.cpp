#include "ControlsScript.h"
#include "ScriptUtilities.h"
#include "Synth.h"

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
