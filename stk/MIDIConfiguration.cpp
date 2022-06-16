#include <Windows.h>

#include "MIDIConfiguration.h"
#include "Utilities.h"

using namespace std;

int MIDIConfiguration::GetNumInputDevices()
{
	return midiInGetNumDevs();
}

int MIDIConfiguration::GetNumOutputDevices()
{
	return midiOutGetNumDevs();
}

string MIDIConfiguration::GetInputDeviceName(int device)
{
	MIDIINCAPS caps;

	midiInGetDevCaps(device, &caps, sizeof(MIDIINCAPS));

	return Utilities::convert(caps.szPname);
}

string MIDIConfiguration::GetOutputDeviceName(int device)
{
	MIDIOUTCAPS caps;

	midiOutGetDevCaps(device, &caps, sizeof(MIDIOUTCAPS));

	return Utilities::convert(caps.szPname);
}
