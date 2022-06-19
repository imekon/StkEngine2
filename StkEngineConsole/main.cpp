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

#include <iostream>

#include <windows.h>

#include "Synth.h"

int main(int argc, char* argv[])
{
	std::cout << "STK Engine Console" << std::endl;

	Initialise();
	Start();

	std::cout << "Mono synth" << std::endl;

	auto mono = CreateMonoSynth();
	auto echo = CreateEchoEffect();
	OscAddEffect(mono, echo);

	SetOscParam(mono, STK_FILTER_CUTOFF, 0.7);

	NoteOn(mono, 60, 0.7);
	Sleep(500);
	NoteOff(mono, 60, 0.3);

	Sleep(5000);

	std::cout << "Poly synth" << std::endl;

	auto poly = CreatePolySynth(4);
	SetOscParam(poly, STK_FILTER_CUTOFF, 0.7);

	NoteOn(poly, 60, 0.7);
	Sleep(500);
	NoteOff(poly, 60, 0.3);

	Sleep(5000);

	Stop();

	OscRemoveEffect(mono, echo);
	DestroyEffect(echo);
	DestroySynth(mono);
	DestroySynth(poly);
	Shutdown();

	return 0;
}