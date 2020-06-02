//5.Определить максимальную, минимальную и среднюю длину слов из данного файла а также частоту (процент) появления каждого символа.
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#define LEN 1024

#include"5.h"

/*
 * Функция получает на вход два файла input (входные данные) и output (для выходных данных)
 * Функция вычисляет значения максимальной минимальной и средней длины слов из файла, а также частоту каждого символа
 * Считываем построчно данные из файла, вычисляем значения максимальной и минимальной длины, а также считаем количество слов из файла для вычисления среднего значения
 * Затем через дополнительный массив символов и значений количества повторений этих букв вычисляем частоту  
*/
void solve_one (FILE *output, FILE *input) {
	int BUFF_SIZE = 256; // размер для массива частоты
   	int buff_sym_num[BUFF_SIZE]; // массив частоты
   	int	k; // счестчик в циклах
   	int	counter_len = 0; // текущая длина слова
   	int	counter_sym = 0; // количество символов
	char buff[LEN], c; // массив символов
	//
	int result_mid = 0, result_max = 0, result_min = 0, counter_words = 0; // выходные данные и количество слов
	int check = 2; // для различия пробелов
	
	// обнуляем массив повторения символов
	for(k = 0; k < BUFF_SIZE; k++)
		buff_sym_num[k] = 0;

	while(fgets(buff, LEN, input)) { // пока считывается строка 
		counter_len = 0;
		check = 2;
		// если символ существует и не новая строка
		for(int j = 0; buff[j] != 0 && buff[j] != '\n'; j++) { 
			c = buff[j]; //для удобства записали в с
			// если слово идет
			++buff_sym_num[(int)c]; // прибавляем по коду символа единичку 
			if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
				counter_len++; // считаем длину текущего слова
				check = 0; // слово идет
			}
		//если попали один раз в else --> слово закончилось
			else {
				check++;	//слово прервалось
				if(check == 1) { 
					if(counter_words == 0) {// изначально все максимумы равны длине первого слова
						result_min = result_max = result_mid = counter_len;
						++counter_words;
						continue;
					}
					++counter_words; // увеличиваем количество слов
					if(result_max < counter_len) 
						result_max = counter_len;
					// если длина текущего слова меньше минимума, то минимум равен длине текущего слова
					if(result_min > counter_len)
						result_min = counter_len;
					// считаем пока что в среднем значении просто сумму длин всех слов
					result_mid += counter_len;
				}
				// обнуляем длину текущего слова
				counter_len = 0; 
			}
		}
		// для поледних слов аналогично
			check++;	
			if( check == 1 ) { //оканчивается не на пробел
				if(counter_words == 0) {// изначально все максимумы равны длине первого слова
					result_min = result_max = result_mid = counter_len;
					++counter_words;
					continue;
				}
				++counter_words;
				if(result_max < counter_len)
					result_max = counter_len;
				if(result_min > counter_len)
					result_min = counter_len;
				result_mid += counter_len;
			}
	}
	fprintf(output, "result_max = %d\n", result_max);
	fprintf(output, "result_min = %d\n", result_min);
	fprintf(output, "result_mid = %d\n", result_mid / counter_words);
	fprintf(output, "counter_words = %d\n", counter_words);
	
	// считаем количество символов
	for(k = 0; k < BUFF_SIZE; k++)
		counter_sym += buff_sym_num[k];
	
	// определяем частоту символов
	for(k = 0; k < BUFF_SIZE; k++) {
		if( (char)k != '\0' && (char)k != '\n' && buff_sym_num[k] != 0)
//			printf("частота символа %c: %lf процентов \n", k, (double)buff_sym_num[k]*100/counter_sym);
			fprintf(output, "частота символа '%c': %lf процентов \n", k, (double)buff_sym_num[k]*100/counter_sym);
	}
}

