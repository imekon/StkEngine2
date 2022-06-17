#ifndef _STKGLOBALS_H
#define _STKGLOBALS_H

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

enum STK_GLOBALS
{
	STK_GLOBAL_STATUS,

	STK_GLOBAL_REVERB_MIX,
	STK_GLOBAL_REVERB_ROOMSIZE,
	STK_GLOBAL_REVERB_DAMPING,
	STK_GLOBAL_REVERB_WIDTH,
	STK_GLOBAL_REVERB_MODE,

	STK_GLOBAL_VU_LEFT,
	STK_GLOBAL_VU_RIGHT,

	STK_GLOBAL_VOLUME,

	STK_GLOBAL_MAX
};

#endif // _STKGLOBALS_H

