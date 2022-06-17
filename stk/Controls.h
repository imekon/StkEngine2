#ifndef _CONTROLS_H
#define _CONTROLS_H

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

#define MAX_FLAGS 4
#define MAX_VALUES 8

class Controls
{
public:
	Controls();

	bool getFlag(int index) const { return flags[index]; }
	void setFlag(int index, bool flag) { flags[index] = flag; }

	double getValue(int index) const { return values[index]; }
	void setValue(int index, double value) { values[index] = value; }

private:
	bool flags[MAX_FLAGS];
	double values[MAX_VALUES];
};

#endif // _CONTROLS_H
