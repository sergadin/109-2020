#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ftw.h>

int main (int argc, const char **argv)
{
	if (argc != 3)
		return -1;
	dir1 = (char*)malloc((strlen("dir1") + 1) * sizeof(char));
	strcpy(dir1, argv[1]);
	dir2 = (char*)malloc((strlen("dir2") + 1) * sizeof(char));
	strcpy(dir2, argv[2]);
	
	List1 = (struct chain*)malloc(sizeof(struct chain));
	List1->name = (char*)malloc((strlen(dir1) + 1) * sizeof(char));
	strcpy(List1->name, dir1);
	List1->next = List1->prev = 0;
	
	List2 = (struct chain*)malloc(sizeof(struct chain));
	List2->name = (char*)malloc((strlen(dir2) + 1) * sizeof(char));
	strcpy(List2->name, dir2);
	List2->next = List2->prev = 0;
	
	ftw(dir1, func_for_ftw, 20);
	ftw(dir2, func_for_ftw, 20);
	
	printf("Файлы, присутствующие в %s, но отсутсвующие в %s:\n", dir1, dir2);
	for (struct chain *FL = List1->next; FL != 0; FL = FL->next)
	{
		if (find_file_in_list(FL->name, List2) == 0)
		    printf("%s\n", FL->name);
	}
	
	printf("Файлы, присутствующие в %s, но отсутсвующие в %s:\n", dir2, dir1);
	for (struct chain *FL = List2->next; FL != 0; FL = FL->next)
	{
		if (find_file_in_list(FL->name, List1) == 0)
		    printf("%s\n", FL->name);
	}
	
	while (List1 != 0)
	{
		struct chain *next;
		next = List1->next;
		free(List1->name);
		free(List1);
		List1 = next;
	}
	while (List2 != 0)
	{
		struct chain *next;
		next = List2->next;
		free(List2->name);
		free(List2);
		List2 = next;
	}

	free(dir1);
	free(dir2);
	return 0;
}