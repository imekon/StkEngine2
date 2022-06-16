#include "MIDIOutput.h"

MIDIOutput::MIDIOutput(int device)
{
	midiOutOpen(&handle, device, (DWORD_PTR)nullptr, (DWORD_PTR)nullptr, CALLBACK_NULL);
}

MIDIOutput::~MIDIOutput()
{
	midiOutClose(handle);
}

void MIDIOutput::send(int status, int param1, int param2)
{
	DWORD msg = (status & 0xff) + ((param1 & 0xff) << 8) + ((param2 & 0xff) << 16);
	midiOutShortMsg(handle, msg);
}
