#include <windows.h>

#include "Stk.h"
#include "SystemScript.h"
#include "ScriptUtilities.h"
#include "Utilities.h"
#include "StkGlobals.h"
#include "Synth.h"

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

