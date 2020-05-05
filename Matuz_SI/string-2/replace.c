#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_file(FILE *file, char **data, size_t bufsize, int *array_size)
{
    int i = 0;
    data[0] = NULL;
    while ((getline(&data[i], &bufsize, file)) != -1) {
        //printf("%s", data[i]);
        data[i + 1] = NULL;
        i++;
    }
    *array_size = i;
    return;
}
void ReplaceWord(const char *s, const char *old,
                  const char *new)
{
    char *result = NULL;
    int i, count = 0;
    int newlength = strlen(new);
    int oldlength = strlen(old);
    for (i = 0; s[i] != '\0'; i++)
    {
        if (strstr(&s[i], old) == &s[i])
        {
            count++;
            i += oldlength - 1;
        }
    }

    result = (char *)malloc(i + count * (newlength - oldlength) + 1);

    i = 0;
    while (*s)
    {
        if (strstr(s, old) == s)
        {
            strcpy(&result[i], new);
            i += newlength;
            s += oldlength;
        }
        else
            result[i++] = *s++;
    }
    result[i] = '\0';
    printf("%s", result);
    free(result);
}



int main(void) {
    FILE *input;//, *output;
    int size = 1000;
    size_t bufsize = 32;
    char **data;
    data = malloc(bufsize * sizeof(char *));

    char old[] = "bla";
    char new[] = "cool";


    if ((input = fopen("input.txt", "r")) == NULL) {
        printf("cannot open input file\n");
        return -1;
    }

    /*if ((output = fopen("output.txt", "r")) == NULL)
    {
        printf("cannot open output file\n");
        fclose(input);
        return -1;
    }*/

    read_file(input, data, bufsize, &size);

    if (size == 0)
    {
        printf("nothing to replace cuz empty file");
        return -1;
    }

    for (int i = 0; i < size; i++)
    {
        printf("%s", data[i]);
    }
    printf("\n////////////////\n");
    for (int i = 0; i < size; i++)
    {
        ReplaceWord(data[i], old, new);
    }

    printf("\n %d", size);
    fclose(input);
    //fclose(output);

    for (int i = 0; i < size; i++)
    {
	free(data[i]);
    }
    free(data);
    return 0;
}