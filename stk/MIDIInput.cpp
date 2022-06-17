#include "MIDIInput.h"

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
