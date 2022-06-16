#include "MIDIInput.h"

MIDIInput::MIDIInput(int device)
{
	InitializeCriticalSection(&lock);

	for (int i = 0; i < 128; i++)
		grid[i] = -1;
	
	midiInOpen(&handle, device, (DWORD_PTR)InputCallback, (DWORD_PTR)this, CALLBACK_FUNCTION);
	midiInStart(handle);
}

MIDIInput::~MIDIInput()
{
	midiInStop(handle);
	midiInClose(handle);
	DeleteCriticalSection(&lock);
}

void MIDIInput::Callback(int msg, int param1, int param2)
{
	EnterCriticalSection(&lock);

	byte code = param1 & 0xff;
	byte p1 = (param1 >> 8) & 0xff;
	byte p2 = (param1 >> 16) & 0xff;

	if (code == 0xb0)
		grid[p1] = p2;
	else if (code == 0x90)
		grid[p1] = p2;
	else if (code == 0x80)
		grid[p1] = 0;

	LeaveCriticalSection(&lock);
}

int MIDIInput::GetInput(int index)
{
	if (index < 0 || index > 127)
		return -1;

	int value;

	EnterCriticalSection(&lock);
	value = (int)grid[index];
	LeaveCriticalSection(&lock);

	return value;
}

void MIDIInput::InputCallback(HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
	MIDIInput *input = (MIDIInput *)dwInstance;
	input->Callback(wMsg, dwParam1, dwParam2);
}
