//I am so sorry :(
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_file(FILE *file, char **data, size_t bufsize, int *array_size)
{
    int i = 0;
    data[0] = NULL;
    while ((getline(&data[i], &bufsize, file)) != -1)
    {
        //printf("%s", data[i]);
        data[i + 1] = NULL;
        i++;
    }
    *array_size = i;
    return;
}


int main(void)
{
    FILE *input, *output;
    int size_input = 0;
    size_t bufsize = 32;
    char **data_input;

    int filename_length = 0;
    char *include = "#include ";



    char *filename;
    char *buff;
    char **data_file;
    int size_file = 0;

    FILE *file;


    if ((input = fopen("input.txt", "r")) == NULL)
    {
        printf("cannot open input file\n");
        return -1;
    }
    //if ((output = fopen("output.txt", "a+t")) == NULL)
    if ((output = fopen("output.txt", "w")) == NULL)
    {
        printf("cannot open output file\n");
        fclose(input);
        return -1;
    }


    data_input = malloc(bufsize * sizeof(char *));
    read_file(input, data_input, bufsize, &size_input);


    for (int i = 0; i < size_input; i++)
    {

        if (strncmp(data_input[i], include, 9) == 0)
        {
            //printf("%s", data_input[i]);
            filename_length = strlen(data_input[i]) - 9;
            if (filename_length <= 0)
            {
                printf("smth wrong with file to include");
                return -1;
            }

            filename = malloc(filename_length * sizeof(char));
            // get filename
            buff = strstr(data_input[i], include);
            strncpy(filename, buff + 9, filename_length - 1);
            printf("%s \n", filename);


            if ((file = fopen(filename, "r")) == NULL)
            {
                printf("cannot open file to include\n");
                return -1;
            }


            data_file = malloc(bufsize * sizeof(char *));
            read_file(file, data_file, bufsize, &size_file);

            for (int j = 0; j<= size_file; j++)
                fprintf(output, "%s", data_file[j]);

            fclose(file);

            free(filename);
            for (int k = 0; k < size_file; k++)
                free(data_file[k]);
            free(data_file);
        }
        else
        {
            fprintf(output,"%s", data_input[i]);
        }

    }


    fclose(input);
    fclose(output);

    for (int i = 0; i <= size_input; i++)
        free(data_input[i]);
    free(data_input);
    return 0;
}