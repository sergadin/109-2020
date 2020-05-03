//All functions in library have prefix s- suggesting string"
#include <stdio.h>
#include <stdlib.h>

#include "mystring.h"

int slength(char *string)
{
  int length = 0;
  while (string[length] != '\0')
  {
    length ++;
  }
  return length;
}
