#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Корректный ввод: " ./a.out name " (где name - это имя директории для старта поиска); при некорректном вводе будет выведено сообщение с просьюой повторить ввод.
 
Вывод: имена файлов, в которых найдется заданная строка (по одному имени в строке); строка, кторая должна содержаться в файле, задается внутри фунции main.

(для обхода дерева файлов, используется функция ftw из библиотеки <ftw.h>)
*/


static const char *s;
static const char *sym;

/**
 "callback function" static int proverka(const char *s, const struct stat *sb, int flag) - функция, вызымаемая для каждого элемента дерева файлов.
 Параметры:
 const char *s: полное имя элемента;

 const struct stat *sb: указатель на структуру stat, возвращаемую вызовом stat(2) для s;

 int flag: type s. 

Проверяет, что ftw подала именно файл,
считывает в цикле строки из файла и выводит те, которые подходят под условие 
*/



static int proverka(const char *s, const struct stat *sb, int flag)
{
    if (flag == FTW_F) 
    {
        char *str = NULL;
	size_t lenn = 0;
	int ind = 0;
	FILE * f;
	if((f = fopen(s, "r")) != NULL)
	{
		while((getline(&str, &lenn, f)) != -1)
		{
			if(strstr(str, sym) != NULL)
			{
				ind = 1;
			}
			if(ind == 1)
				break;	
		}
		if(str)
			free(str);
		if(ind == 1)
		{
			printf("%s\n", s);
		}
		ind = 0;
		fclose(f);
	 }
    }
    return 0;         
}

int main(int argc, char *argv[]) 
{
    if(argc == 2) 
    {
       s = argv[1];
       sym = " ";
       ftw(s, proverka, 36);
    }
    else
    {
	    printf("eshe_raz\n");
    }
    return 0;
}
