#ifndef _STKSCRIPT_H
#define _STKSCRIPT_H

#include <string>

#include <duktape.h>

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
	duk_context *context;

	int errorCode;
	std::string errorMessage;

	void push_file_as_string(const char *filename);
};

#endif // _STKSCRIPT_H
