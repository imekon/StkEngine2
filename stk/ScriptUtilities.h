#ifndef _SCRIPTUTILITIES_H
#define _SCRIPTUTILITIES_H

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

