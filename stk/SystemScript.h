#ifndef _SYSTEMSCRIPT_H
#define _SYSTEMSCRIPT_H

#include <windows.h>

#include <vector>
#include <string>

#include <duktape.h>

#define MESSAGE_SIZE 4096

class SystemScript
{
public:
	static void initialise();
	static void shutdown();

	static void loadLibrary(duk_context *context);

	static duk_ret_t getGlobal(duk_context *context);
	static duk_ret_t setGlobal(duk_context *context);
	static duk_ret_t sleep(duk_context *context);
	static duk_ret_t log(duk_context *context);
	static duk_ret_t status(duk_context *context);
	static duk_ret_t waitTick(duk_context *context);

	static int getMessageCount();
	static const char *getMessage();
	static bool waitText();

private:
	static CRITICAL_SECTION lock;
	static HANDLE textEvent;
	static std::vector<std::string> messages;
	static char message[4096];
};

#endif // _SYSTEMSCRIPT_H
