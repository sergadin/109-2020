#include "13.h"
#define LEN 1024
#define ERR -1

int solve (FILE *output, FILE *input) {
	char buf[LEN];
	int len = 0;
	int shift_min = 0;
	int	shift;
	if (fgets(buf, LEN, input) == NULL) {
		return ERR;
	}

	fprintf(output,"Была:	");	
	
	// считаем длину
	for(int i = 0; buf[i] != '\n' && buf[i]; i++) {
		len = i + 1;
		fprintf(output, "%c", buf[i]);	
	}

	// конец строки
	buf[len] = '\0';

	//функция сравнения	
	// расмматриваем элемент со сдвигом при котором строка минимальна на данный момент
	// и элемент с текущим рассматриваемым сдвигом 
	// (если вышли на нулевой символ, то вычитаем длину строки и попадает в нужный (почти как по модулю len если рассматривать, просто максимальный сдвиг это len * 1))
	// смотрим на разность кодов элементов и возвращаем это число
	// то есть пока равны идем дальше по строке, если нет, то 
	// если c < 0 элемент со сдвигом shift_now дальше по алфавиту  
	// если c > 0, то наоборот
	int str_comp(char buf[1024], int len, int shift_min, int shift_now) {
		int i, c;
		for(i = 0; i < len; ++i) {
			if(i + shift_min == len) {
				shift_min -= len;
			}	
			if(i + shift_now == len) {
				shift_now -= len;
			}

			c = buf[shift_min + i] - buf[shift_now + i];
			if(c != 0) return c;
		}
	return 0;
	}

	//пробегаемся по сдвигам с 1 до len - 1 и смотрим на знак c
	//если c > 0 то элемент со сдвигом shift_min дальше по алфавиту
	//то есть shift_now теперь становится искомым
	for(int shift_now = 1; shift_now < len; ++shift_now) {	
		if(str_comp(buf, len, shift_min, shift_now) > 0)
			shift_min = shift_now;
	}

	fprintf(output, "\nПолучилась:	");
	
	// выводим строку с найденным минимальным сдвигом
	shift = shift_min;
	for(int i = 0; i < len; ++i) {
		if(i + shift == len) 
			shift -= len;
		fprintf(output, "%c", buf[i + shift]);
	}
	return shift_min;
}
