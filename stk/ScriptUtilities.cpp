#include "ScriptUtilities.h"

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
void ScriptUtilities::readArray(duk_context *context, std::function<bool(const char *)> callback)
{
	if (duk_is_array(context, -1))
	{
		duk_enum(context, -1, DUK_ENUM_ARRAY_INDICES_ONLY);
		while (duk_next(context, -1, false))
		{
			duk_get_prop_index(context, -1, 0);
			duk_get_prop_string(context, -4, duk_get_string(context, -1));
			const char *value = duk_get_string(context, -1);
			(callback)(value);
			duk_pop(context); // get_prop_string
			duk_pop(context); // get_prop_index
			duk_pop(context); // duk_next
		}

		duk_pop(context); // duk_enum
	}
}

void ScriptUtilities::readObject(duk_context *context, int index, const char **keys, Value *values, const Value *defValues)
{
	if (duk_is_object(context, index))
	{
		for (auto i = 0; keys[i] != nullptr; i++)
		{
			if (duk_get_prop_string(context, index, keys[i]))
			{
				auto type = duk_get_type(context, -1);
				switch (type)
				{
				case DUK_TYPE_BOOLEAN:
					values[i].set(duk_get_boolean(context, -1) != 0);
					break;

				case DUK_TYPE_NUMBER:
					values[i].set((float)duk_get_number(context, -1));
					break;
				}
			}
			else
			{
				values[i] = defValues[i];
			}

			duk_pop(context);
		}
	}
	else
	{
		for (auto i = 0; keys[i] != nullptr; i++)
		{
			values[i] = defValues[i];
		}
	}
}

void ScriptUtilities::loadLibrary(duk_context *context, const char *moduleName, const duk_function_list_entry *funcs)
{
	duk_push_global_object(context);
	duk_push_object(context);  /* -> [ ... global obj ] */
	duk_put_function_list(context, -1, funcs);
	duk_put_prop_string(context, -2, moduleName);  /* -> [ ... global ] */
	duk_pop(context);
}

void ScriptUtilities::registerProperty(duk_context *context, const char *name, const char *value)
{
	duk_push_this(context);
	duk_push_string(context, value);
	duk_put_prop_string(context, -2, name);
}

void ScriptUtilities::registerProperty(duk_context *context, const char *name, void *value)
{
	duk_push_this(context);
	duk_push_pointer(context, value);
	duk_put_prop_string(context, -2, name);
}

void ScriptUtilities::registerProperty(duk_context* context, const char* name, duk_c_function getter, duk_c_function setter)
{
	duk_push_string(context, name);
	duk_push_c_function(context, getter, 0);
	duk_push_c_function(context, setter, 1);
	duk_def_prop(context, -4, DUK_DEFPROP_HAVE_GETTER | DUK_DEFPROP_HAVE_SETTER);
}

void ScriptUtilities::registerPropertyFunction(duk_context *context, const char *name, duk_c_function func, duk_idx_t args)
{
	duk_push_this(context);
	duk_push_c_function(context, func, args);
	duk_put_prop_string(context, -2, name);
}

void ScriptUtilities::registerDestructor(duk_context *context, duk_c_function func)
{
	duk_push_c_function(context, func, 1);
	duk_set_finalizer(context, -2);
}

void ScriptUtilities::pushTwoKeys(duk_context *context, float x, float y)
{
	auto arrayIndex = duk_push_array(context);
	duk_push_number(context, x);
	duk_put_prop_string(context, arrayIndex, "x");
	duk_push_number(context, y);
	duk_put_prop_string(context, arrayIndex, "y");
}

void ScriptUtilities::pushTwoKeys(duk_context *context, int x, int y)
{
	auto arrayIndex = duk_push_array(context);
	duk_push_int(context, x);
	duk_put_prop_string(context, arrayIndex, "x");
	duk_push_int(context, y);
	duk_put_prop_string(context, arrayIndex, "y");
}
#endif
