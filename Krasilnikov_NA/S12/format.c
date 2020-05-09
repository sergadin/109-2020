#include <stdio.h>
#include <stdlib.h>

#include "format.h"
#include "../libs/mystring/mystring.h"

void formatting(FILE *fin, FILE *fout)
{
	char *string, pshlz = 0;
	int sc = 0;
	/*pshlz = Previous_String_Has_Length_Zero
	  sc = String_Count*/
	while ((string = sread(fin)) != NULL)
	{
		sc++;
		switch(pshlz)
		{
			case 0:

				if ((slength(string)) > 0)
				{
					if (sc != 1)
					{
						fprintf(fout, "\n");
					}
					fprintf(fout, "\t%s", string);
					pshlz = 1;
				}
				else
				{
					sc--;
				}
				break;

			case 1:

				if ((slength(string)) > 0)
				{
					fprintf(fout, " %s", string);
				}
				else
				{
					sc--;
					pshlz = 0;
				}
				break;

		}
		free(string);
	}
	if (sc == 0)
	{
		fprintf(fout, "Input file is empty");
	}
}
