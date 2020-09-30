#include "error.h"

const char* getErrorMessage(int error)
{
	switch (error)
	{
	case S_OK:
		return "OK";
	case E_INVALIDFILE:
		return "invalid file name";
	case E_CANNOTOPENFILE:
		return "cannot open file";
	case E_OUTOFRANGE:
		return "argument out of range";
	case E_OUTOFMEMORY:
		return "out of memory";
	case E_NULLREFERENCE:
		return "null reference";
	default:
		return "unknown error";
	}
}