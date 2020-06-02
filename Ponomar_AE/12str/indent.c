#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "indent.h"

void indent(FILE *input, FILE *output, int max_len)
{
	char *buf;
	int ind = 0, start, calc = 0, size_buffer; 	
	
	while((buf = read_string(input)) != NULL)
	{
		if (buf[0] == '\n' && strlen(buf) > 1 && (int)(buf[1]) == 13)
		{
			ind = 1;
			calc = 0;
		}

		else
		{
			if (ind == 1)
			{
				fprintf(output, "\n    ");
				ind = 0;
				calc = 4;
			}
			size_buffer = (int)(strlen(buf));

			for (int i = 0; i < size_buffer; i++)
			{
				calc++;
				start = i;

				while (buf[i] != ' ' && buf[i] != '\n' && buf[i] != 0 && (int)(buf[i]) != 13)
				{
					i++;
					calc++;
				}

				if (calc <= max_len)
				{
					for (int j = start; j < i; j++)
					{

						fprintf(output, "%c", buf[j]);

					}
					fprintf(output, " ");
				}
				
				else 
				{
					fprintf(output, "\n");
					i = start - 1;
					calc = 0;
				}
			}	
		}
		free(buf);
	}

	if(!feof(input))
	{
		free(buf);
		fclose(input);
		fclose(output);
		printf("ERROR indenting");
	}

	free(buf);
	fclose(input);
	fclose(output);
}


char *read_string(FILE *input)
{
	char buf[1024];
	buf[0] = 0;
	char *s = fgets(buf, 1024, input);
	if (s)
	{
		int len = strlen(s);
		char *result = malloc(len + 1);
		strcpy(result, s);
		return result;
	}
	return NULL;

}
