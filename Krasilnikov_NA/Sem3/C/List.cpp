#include "List.h"

Exc::Exc(int code, const string& reason)
{
	code_of_error = code;
	error = reason;
}

const string& Exc::get_error() const
{
	return error;
}

