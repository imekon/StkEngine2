#include "MIDIOutEngine.h"

MIDIOutEngine::MIDIOutEngine()
{
	handle = nullptr;
}

MIDIOutEngine::~MIDIOutEngine()
{
}

int MIDIOutEngine::getCount()
{
	return midiOutGetNumDevs();
}

std::string MIDIOutEngine::getName(int device)
{
	MIDIOUTCAPS caps;

	midiOutGetDevCaps(device, &caps, sizeof(MIDIOUTCAPS));

#ifdef _UNICODE
	size_t length;
	char buffer[256];

	wcstombs_s(&length, buffer, 256, caps.szPname, 256);

	return buffer;
#else
	return caps.szPname;
#endif
}

bool MIDIOutEngine::open(int device)
{
	if (midiOutOpen(&handle, device, NULL, 0, CALLBACK_NULL) == MMSYSERR_NOERROR)
		return true;

	return false;
}

void MIDIOutEngine::send(int data1, int data2, int data3) const
{
	DWORD data = (data1 & 0xff) | (data2 & 0xff) << 8 | (data3 & 0xff) << 16;
	midiOutShortMsg(handle, data);
}

void MIDIOutEngine::close() const
{
	midiOutClose(handle);
}

