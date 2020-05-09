#include <stdio.h>
#include <stdlib.h>

#include "format.h"
#include "../libs/mystring/mystring.h"

void formatting(FILE *fin, FILE *fout)
{
  char *string, pshlz = 0;
  /*pshlz = Previous_String_Has_Length_Zero*/
  while ((string = sread(fin)) != NULL)
  {
    switch(pshlz)
    {
      case 0:
      {
        if ((slength(string)) > 0)
        {
          fprintf(fout, "\t%s", string);
          pshlz = 1;
        }
      }
      case 1:
      {
        if ((slength(string)) > 0:)
        {
          fprintf(fout, " %s", string);
        }
        else
        {
          pshlz = 0;
        }
      }
    }
    free(string);
  }
}
