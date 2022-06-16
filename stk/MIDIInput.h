#ifndef _MIDIINPUT_H
#define _MIDIINPUT_H

#include <Windows.h>

class MIDIInput
{
public:
	MIDIInput(int device);
	virtual ~MIDIInput();

	int GetInput(int index);

private:
	HMIDIIN handle;
	CRITICAL_SECTION lock;
	byte grid[128];

	void Callback(int msg, int param1, int param2);

	static void CALLBACK InputCallback(HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2);
};
#endif // _MIDIINPUT_H

