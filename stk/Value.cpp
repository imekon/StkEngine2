#include "Value.h"

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

bool Value::asBool() const
{
	switch (type)
	{
	case ValueType::Boolean:
		return data.bValue;

	case ValueType::Integer:
		return data.iValue != 0;

	case ValueType::Float:
		return data.fValue != 0.0f;
	}

	return false;
}

int Value::asInt() const
{
	switch (type)
	{
	case ValueType::Boolean:
		return data.bValue ? -1 : 0;

	case ValueType::Integer:
		return data.iValue;

	case ValueType::Float:
		return static_cast<int>(data.fValue);
	}
	return 0;
}

float Value::asFloat() const
{
	switch (type)
	{
	case ValueType::Boolean:
		return data.bValue ? -1.0f : 0.0f;

	case ValueType::Integer:
		return static_cast<float>(data.iValue);

	case ValueType::Float:
		return data.fValue;
	}

	return 0.0f;
}
