#ifndef _SYSTEMSCRIPT_H
#define _SYSTEMSCRIPT_H

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

#include <windows.h>

#include <vector>
#include <string>

#ifdef DUKTAPE_ENABLE
#include <duktape.h>
#endif

#define MESSAGE_SIZE 4096

class SystemScript
{
public:
	static void initialise();
	static void shutdown();

#ifdef DUKTAPE_ENABLE
	static void loadLibrary(duk_context *context);

	static duk_ret_t getGlobal(duk_context *context);
	static duk_ret_t setGlobal(duk_context *context);
	static duk_ret_t sleep(duk_context *context);
	static duk_ret_t log(duk_context *context);
	static duk_ret_t status(duk_context *context);
	static duk_ret_t waitTick(duk_context *context);
#endif

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
