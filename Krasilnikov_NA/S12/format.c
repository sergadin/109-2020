#include <stdio.h>
#include <stdlib.h>

#include "format.h"
#include "../libs/mystring/mystring.h"

#define TAB 8

/**
** Форматироватние абзацев текста в заданных границах и с красной строкой (без переноса слов).
**
** Терминология:
**  	слово - элементы строки (не включающие знаки табуляции), разделенные пробелом или началом/концом файла
**  	нулевая строка - строка без слов
**
** Параметры:
**  	*fin: входной файл.
**  	*fout: выходной файл.
**  	mls: Максимально допустимая длинна строки в выходном файле
**
** Вспомогательные функции:
**		1. spw - печать слова из строки.
**
** Принцип работы:
** 		Из файла fin циклически считываются строки до той поры, пока не будет достигнут конец входного файла.
**		Если входной файл пуст, в выходной будет выведено соответсвуещее сообщение.
** 		Если конец файла не будет достигнут, в файл fout будет выведено сообщение об ошибке.
** 		Если mls меньше максимальной длинны слова в файле или в файле есть слово, стоящее в начале абазца, такое
** 		что его длинна плюс длинна горизонтальной табуляции больше mls (невозможно записать слово без переноса
** 		не нарушая рамок абзаца) будет выведено сообщение об ошибке.
**		ВАЖНО. Сообщения об ошибке печатаются в выходной файл, после того, как он был закрыт и заново открыт для
**		записи с тем же указателем. При его открытии тоже может возникнуть ошибка. Если она происходит, в консоль
**		выводится сообщение об ошибке.
**
**		Если же mls достаточно большое и конец фала был достигнут то функция отфарматирует абазцы текста
** 		следующим образом:
** 		1. Нулевые строки будут удалены
** 		2. Несколько пробелов подряд между словами будут заменены одним.
** 		3. Будут убраны все знаки табуляции, кроме тех, что начинают абзац.
** 		4. Каждая строчка абзаца не будет превышать длинну mls.
**
** Пример работы:
**		1 случай (mls не достаточно большой)
**
**		mls = 10
**
** 		Текст входного файла:
**		————————————————————————————————————
**		You shall not pass!
**		————————————————————————————————————
**
**		Текст выходного файла:
**		————————————————————————————————————
**		N is too short. Change input file or change N
**		————————————————————————————————————
**
**		2 случай (Цикл закончен, mls достаточно большой, конец файла не был достигнут,
**		входной файл не пуст)
**
**		mls = 30
**
** 		Текст входного файла:
**		————————————————————————————————————
**
**
** 		A wizard       is *TAB*	never late, Frodo Baggins.    Nor is he early.
**		He arrives precisely when he means to.
**
**
**		————————————————————————————————————
**
**		Текст выходного файла:
**		————————————————————————————————————
**			A wizard is never
**		late, Frodo Baggins. Nor is he
**		early. He arrives precisely
**		when he means to.
**		————————————————————————————————————
*/

void formatting(FILE *fin, FILE *fout, int mls)
{
	char *string;
	int ls, cls = 0, sc = 0, clw, wc, wbi, wei, pcis, ec = 0, pshlz = 0;
	/* ls = Length_of_String,
		cls = Current_Length_of_String,
		sc = String's_Count,
		clw = Current_Length_of_Word,
		wc = Word's_Count,
		wbi = Words_Beginning_Index,
		wei = Words_Ending_Index,
		pcis = Previous_Character_Is_Space,
		ec = Error_Code,
		pshlz = Previous_String_Has_Length_String
	*/
	while((string = sread(fin)) != NULL)
	{
		sct(string);
		sc++;
		ls = slength(string);
		wc = swc(string);
		if ((pshlz == 0) && (wc != 0))
		{
			cls = TAB;
			if (sc != 1)
			{
				fprintf(fout, "\n");
			}
			fprintf(fout, "\t");
		}
		pcis = 0;
		wbi = 0;
		wei = -1;
		for (int i = 0; i < wc; i++)
		{
			if (ec == -1)
			{
				break;
			}
			for (int j = (wei + 1); j < ls; j++)
			{
				switch(pcis)
				{
					case 0:
						if (string[j] != ' ')
						{
							wbi = j;
							pcis = 1;
							if (j == (ls - 1))
							{
								wei = j;
							}
						}
						break;
					case 1:
						if (string[j] == ' ')
						{
							wei = (j - 1);
							pcis = 0;
						}
						if ((string[j] != ' ') && (j == (ls - 1)))
						{
							wei = j;
						}
						break;
				}
				if (wei >= wbi)
				{
					break;
				}
			}
			clw = wei - wbi + 1;
			if ((clw > mls) || ((pshlz == 0) && (i == 0) && ((clw + cls) > mls)))
			{
				ec = -1;
			}
			else
			{
				if ((clw + 1) <= (mls - cls))
				{
					spw(wbi, wei, string, fout);
					fprintf(fout, " ");
					cls += (clw + 1);
				}
				else
				{
					if (clw == (mls - cls))
					{
						spw(wbi, wei, string, fout);
						if (i != wc)
						{
							fprintf(fout, "\n");
						}
						cls = 0;
					}
					else
					{
						fprintf(fout, "\n");
						spw(wbi, wei, string, fout);
						if (clw == mls)
						{
							if (i != wc)
							{
								fprintf(fout, "\n");
							}
							cls = 0;
						}
						else
						{
							fprintf(fout, " ");
							cls = clw + 1;
						}
					}
				}
			}
			wbi = ls;
		}
		free(string);
		if (wc != 0)
		{
			pshlz = 1;
		}
		else
		{
			sc--;
			pshlz = 0;
		}
		if (ec == -1)
		{
			break;
		}
	}
	if (sc == 0)
	{
		fprintf(fout, "Input file is empty");
	}
	if ((ec == -1) || (!feof(fin)))
	{
		fclose(fout);
		if ((fout = fopen("output.txt", "w")) == NULL)
		{
			if (ec == -1)
			{
				printf("Something went wrong\n");
		}
		else
		{
			if (ec == -1)
			{
				fprintf(fout, "N is too short. Chenge input file or change N\n");
			}
			else
			{
				fprintf(fout, "Input file reading error\n")
			}
			fclose(fout);
		}
		fclose(fin);

	}
	else
	{
		fclose(fin);
		fclose(fout);
	}
}


void spw(int wbi, int wei, char *string, FILE *fout)
{
	for (int i = wbi; i <= wei; i++)
	{
		fprintf(fout, "%c", string[i]);
	}
}
