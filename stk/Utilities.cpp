#include <windows.h>

#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <codecvt>

#define _USE_MATH_DEFINES
#include <math.h>

#include "Utilities.h"

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

void Utilities::trace(const char *message, ...)
{
#ifdef _DEBUG
	va_list args;
	char buffer[2048];

	va_start(args, message);
	vsprintf_s(buffer, message, args);
#ifdef _UNICODE
	size_t size = strlen(buffer) + 1;
	wchar_t *output = new wchar_t[size];
	mbstowcs(output, buffer, size);
	OutputDebugString(output);
	delete[] output;
#else
	OutputDebugString(buffer);
#endif
	va_end(args);
#endif
}

double Utilities::noteRatio(double offset, double frequency)
{
	double ratio = pow(2.0, offset / 12.0) * frequency;
	return ratio;
}

double Utilities::midiToFreq(int note)
{
	int offset = note - 69;
	double freq = noteRatio(offset, 440.0);
	return freq;
}

void Utilities::panning(double mix, double &left, double &right)
{
	left = cos(mix * M_PI / 2.0);
	right = sin(mix * M_PI / 2.0);
}

string Utilities::convert(wstring text)
{
	int size = WideCharToMultiByte(CP_ACP, 0, text.c_str(), -1, nullptr, 0, nullptr, nullptr);

	char *buffer = new char[size];

	WideCharToMultiByte(CP_ACP, 0, text.c_str(), -1, buffer, size, nullptr, nullptr);

	string result(buffer);
	delete buffer;
	return result;
}
