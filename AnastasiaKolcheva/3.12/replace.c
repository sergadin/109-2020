#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "replace.h"
#include "error.h"

int replace1(FILE* input, FILE* output, const char* search, const char* replace);
int format1(FILE* input, FILE* output, int width, int indent);

int format(const char* inputName, const char* outputName, int width, int indent)
{
	FILE* input;
	FILE* output;
	int error;

	if (inputName == NULL || outputName == NULL)
	{
		return E_INVALIDFILE;
	}
	if (width < 40 || indent > 10 || indent < 0)
	{
		return E_INVALIDARG;
	}
	input = fopen(inputName, "r");
	output = fopen(outputName, "w");

	if (input == NULL)
	{
		return E_CANNOTOPENFILE;
	}
	if (output == NULL)
	{
		fclose(input);
		return E_CANNOTOPENFILE;
	}

	error = format1(input, output, width, indent);

	fclose(input);
	fclose(output);

	return error;
}

int replace(const char* inputName, const char* outputName, const char* search, const char* replace)
{
	FILE* input;
	FILE* output;
	int error;

	if (inputName == NULL || outputName == NULL)
	{
		return E_INVALIDFILE;
	}
	if (search == NULL || replace == NULL)
	{
		return E_INVALIDARG;
	}
	input = fopen(inputName, "r");
	output = fopen(outputName, "w");

	if (input == NULL)
	{
		return E_CANNOTOPENFILE;
	}
	if (output == NULL)
	{
		fclose(input);
		return E_CANNOTOPENFILE;
	}

	error = replace1(input, output, search, replace);

	fclose(input);
	fclose(output);

	return error;
}

int replace1(FILE* input, FILE* output, const char* search, const char* replace)
{
	int i;
	int index = 0;
	int searchLength = strlen(search);
	if (searchLength == 0)
	{
		return E_INVALIDARG;
	}
	for (;;)
	{
		int ch = fgetc(input);
		if (ch == EOF)
		{
			for (i = 0; i < index; ++i)
			{
				fputc(search[i], output);
			}
			return S_OK;
		}
		else if (ch == search[index]) {
			++index;
			if (index == searchLength) {
				fprintf(output, replace);
				index = 0;
			}
			continue;
		}
		else if (index > 0)
		{
			for (i = 0; i < index; ++i)
			{
				fputc(search[i], output);
			}
			index = 0;
		}
		fputc(ch, output);
	}
}

void writeIndent(FILE* output, int indent)
{
	int index;
	for (index = 0; index < indent; ++index)
	{
		fputc(' ', output);
	}
}

int format1(FILE* input, FILE* output, int width, int indent)
{
	int ch;
	int index = 0;
	int paragraph = 1;
	int line = 0;
	char* buffer = (char*)malloc(width);

	for (;;)
	{
		if (paragraph)
		{
			writeIndent(output, indent);
			line += indent;
			paragraph = 0;
		}
		ch = fgetc(input);
		if (ch == EOF)
		{
			buffer[index] = '\0';
			if (line + index > width) {
				fputc('\n', output);
				line = 0;
			}
			fputs(buffer, output);
			return S_OK;
		}
		else if (ch == ' ')
		{
			if (index > 0)
			{
				buffer[index] = '\0';
				if (line + index + 1 >= width) {
					fputc('\n', output);
					line = 0;
				}
				else
				{
					fputc(' ', output);
					line++;
				}
				fputs(buffer, output);
				line += index;
				index = 0;
			}
		}
		else if (ch == '\n')
		{
			if (index > 0)
			{
				buffer[index] = '\0';
				if (line + index + 1 > width) {
					fputc('\n', output);
					line = 0;
				}
				else
				{
					fputc(' ', output);
					line++;
				}
				fputs(buffer, output);
				line += index;
				index = 0;
			}
			ch = fgetc(input);
			if (ch == '\n') {
				fputc('\n', output);
				paragraph = 1;
				line = 0;
			}
			else
			{
				ungetc(ch, input);
			}
		}
		else if (ch == '\r')
		{
		}
		else {
			buffer[index++] = ch;
		}
	}
}