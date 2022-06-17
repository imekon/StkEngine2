#ifndef _SCRIPTUTILITIES_H
#define _SCRIPTUTILITIES_H

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

#ifdef DUKTAPE_ENABLE
#include <duktape.h>

#include <functional>

#include "Value.h"

class ScriptUtilities
{
public:
	static void readArray(duk_context *context, std::function<bool(const char *)> callback);
	static void readObject(duk_context *context, int index, const char **keys, Value *values, const Value *defValues);

	static void loadLibrary(duk_context *context, const char *moduleName, const duk_function_list_entry *funcs);

	static void registerProperty(duk_context *context, const char *name, const char *value);
	static void registerProperty(duk_context *context, const char *name, void *value);
	static void registerProperty(duk_context *context, const char *name, duk_c_function getter, duk_c_function setter);
	static void registerPropertyFunction(duk_context *context, const char *name, duk_c_function func, duk_idx_t args);
	static void registerDestructor(duk_context *context, duk_c_function func);

	static void pushTwoKeys(duk_context *context, int x, int y);
	static void pushTwoKeys(duk_context *context, float x, float y);
};
#endif
#endif

