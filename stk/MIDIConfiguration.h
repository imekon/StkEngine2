#ifndef _MIDICONFIGURATION_H
#define _MIDICONFIGURATION_H

#include <string>

class MIDIConfiguration
{
public:
	static int GetNumInputDevices();
	static int GetNumOutputDevices();
	static std::string GetInputDeviceName(int device);
	static std::string GetOutputDeviceName(int device);
};

#endif // _MIDICONFIGURATION_H

