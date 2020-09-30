#ifndef __ERROR_H___

#define __ERROR_H___

#define S_OK				 0
#define E_INVALIDFILE		-1
#define E_CANNOTOPENFILE	-2
#define E_OUTOFRANGE		-3
#define E_OUTOFMEMORY		-4
#define E_NULLREFERENCE		-5
#define E_INVALIDARG		-6

const char* getErrorMessage(int error);

#endif