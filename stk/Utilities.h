#ifndef _UTILITIES_H
#define _UTILITIES_H

#include <string>

class Utilities
{
public:
	static void trace(const char *message, ...);
	static double noteRatio(double offset, double frequency);
	static double midiToFreq(int note);
	static void panning(double mix, double &left, double &right);
	static std::string convert(std::wstring text);
};

#endif // _UTILITIES_H
