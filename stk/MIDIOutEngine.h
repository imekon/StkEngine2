#ifndef _MIDIENGINE_H
#define _MIDIENGINE_H

#include <windows.h>

#include <string>

class MIDIOutEngine
{
public:
	MIDIOutEngine();
	~MIDIOutEngine();

	static int getCount();
	static std::string getName(int device);

	bool open(int device);
	void send(int data1, int data2, int data3) const;
	void close() const;

private:
	HMIDIOUT handle;
};

#endif // _MIDIENGINE_H
