#pragma once
#include <string.h>

class MyException
{
    private:
        char message[256];
        int code;
    public:
        MyException(const char *msg, int c)
        {
            code = c;
            strncpy(message, msg, 255);
        }


   const char *Message() const{return message;}
   int Code(){return code;}
};

enum ErrorCodes
{
    EC_UNKNOWN = 0,
    EC_MEMORY = -1,
    EC_INDEX = -2,
    EC_ACCESS = -3
};
