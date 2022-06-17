#ifndef _VALUE_H
#define _VALUE_H

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

class Value
{
public:
	enum ValueType
	{
		Unknown,
		Boolean,
		Integer,
		Float
	};

	Value() { type = ValueType::Unknown; }
	explicit Value(bool value) { type = ValueType::Boolean; data.bValue = value; }
	explicit Value(int value) { type = ValueType::Integer; data.iValue = value; }
	explicit Value(float value) { type = ValueType::Float; data.fValue = value; }

	bool asBool() const;
	int asInt() const;
	float asFloat() const;

	void set(bool value) { type = ValueType::Boolean; data.bValue = value; }
	void set(int value) { type = ValueType::Integer; data.iValue = value; }
	void set(float value) { type = ValueType::Float; data.fValue = value; }

private:
	ValueType type;
	union
	{
		bool bValue;
		int iValue;
		float fValue;
	} data;
};

#endif

