#include <windows.h>

#include "Stk.h"
#include "SystemScript.h"
#include "ScriptUtilities.h"
#include "Utilities.h"
#include "StkGlobals.h"
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

using namespace std;

char SystemScript::message[4096];
CRITICAL_SECTION SystemScript::lock;
HANDLE SystemScript::textEvent;
vector<string> SystemScript::messages;

static const duk_function_list_entry scriptSystemLibrary[] =
{
	"GetGlobal",		SystemScript::getGlobal,		1,
	"SetGlobal",		SystemScript::setGlobal,		2,
	"Sleep",			SystemScript::sleep,			1,
	"Log",				SystemScript::log,				1,
	"Status",			SystemScript::status,			1,
	"WaitTick",			SystemScript::waitTick,			0,

	nullptr,			nullptr,						0
};

void SystemScript::initialise()
{
	InitializeCriticalSection(&lock);
	textEvent = CreateEvent(nullptr, FALSE, FALSE, L"StkTextEvent");
}

void SystemScript::shutdown()
{
	DeleteCriticalSection(&lock);
	CloseHandle(textEvent);
}

void SystemScript::loadLibrary(duk_context* context)
{
	ScriptUtilities::loadLibrary(context, "System", scriptSystemLibrary);
}

duk_ret_t SystemScript::getGlobal(duk_context* context)
{
	STK_GLOBALS global = static_cast<STK_GLOBALS>(duk_get_int(context, 0));
	stk::StkFloat value = GetGlobalParam(global);
	duk_push_number(context, value);
	return 1;
}

duk_ret_t SystemScript::setGlobal(duk_context* context)
{
	STK_GLOBALS global = static_cast<STK_GLOBALS>(duk_get_int(context, 0));
	stk::StkFloat value = duk_get_number(context, 1);

	SetGlobalParam(global, value);

	return 0;
}

duk_ret_t SystemScript::sleep(duk_context* context)
{
	int duration = duk_get_int(context, 0);

	Sleep(duration);

	return 0;
}

duk_ret_t SystemScript::log(duk_context* context)
{
	auto text = duk_to_string(context, 0);

	EnterCriticalSection(&lock);

	messages.push_back(text);

	LeaveCriticalSection(&lock);

	Utilities::trace(text);

	SetEvent(textEvent);

	return 0;
}

duk_ret_t SystemScript::status(duk_context* context)
{
	auto text = duk_to_string(context, 0);

	strcpy_s(message, text);

	return 0;
}

duk_ret_t SystemScript::waitTick(duk_context* context)
{
	duk_bool_t result = WaitTick();

	duk_push_boolean(context, result);

	return 1;
}

int SystemScript::getMessageCount()
{
	int count;

	EnterCriticalSection(&lock);

	count = static_cast<int>(messages.size());

	LeaveCriticalSection(&lock);

	return count;
}

const char* SystemScript::getMessage()
{
	EnterCriticalSection(&lock);

	std::string text = messages.back();
	strcpy_s(message, text.c_str());
	messages.pop_back();

	LeaveCriticalSection(&lock);

	return message;
}

bool SystemScript::waitText()
{
	DWORD result = WaitForSingleObject(textEvent, INFINITE);

	if (result == WAIT_OBJECT_0)
		return true;

	return false;
}

