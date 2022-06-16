#include <windows.h>

#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <codecvt>

#define _USE_MATH_DEFINES
#include <math.h>

#include "Utilities.h"

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
