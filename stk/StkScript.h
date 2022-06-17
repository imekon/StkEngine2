#ifndef _STKSCRIPT_H
#define _STKSCRIPT_H

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

#include <string>

#ifdef DUKTAPE_ENABLE
#include <duktape.h>
#endif

class StkScript
{
public:
	StkScript();

	void initialise();
	void shutdown();

	std::string evaluate(const char *text) const;
	void readfile(const char *filename);
	void invokeTick();

	int getErrorCode() const { return errorCode; }
	std::string getErrorMessage() const { return errorMessage; }

private:
#ifdef DUKTAPE_ENABLE
	duk_context *context;
#endif

	int errorCode;
	std::string errorMessage;

	void push_file_as_string(const char *filename);
};

#endif // _STKSCRIPT_H
