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

	auto osc = CreateSynth();
	auto echo = CreateEchoEffect();
	OscAddEffect(osc, echo);

	SetOscParam(osc, STK_FILTER_CUTOFF, 0.7f);

	NoteOn(osc, 60, 0.7f);
	Sleep(500);
	NoteOff(osc, 60, 0.3f);

	Sleep(5000);

	Stop();

	OscRemoveEffect(osc, echo);
	DestroyEffect(echo);
	DestroySynth(osc);
	Shutdown();

	return 0;
}