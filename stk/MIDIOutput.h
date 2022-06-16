#ifndef _MIDIOUTPUT_H
#define _MIDIOUTPUT_H

#include <Windows.h>

class MIDIOutput
{
public:
	MIDIOutput(int device);
	virtual ~MIDIOutput();
	void send(int status, int param1, int param2);

private:
	HMIDIOUT handle;
};

#endif // _MIDIOUTPUT_H

