//12. Отформатировать абзацы текста в заданных границах и с красной строкой (без переноса слов). 
//Абзац — фрагмент текста между пустыми строками.

#include "12.h"
#define LEN 1024
#define ERR -1

void file_print_word(FILE *output, char buff[1024], int start_w, int finish_w) { //!!!!!!!!!!!!
	for(int i = start_w; i <= finish_w; i++) {
		fprintf(output, "%c", buff[i]);
		//		fprintf(output, "proverka\n");
	}
}

int if_letter(FILE *output, int word_len, int limit, int count_sym, char buff[1024] ,int start_w, int finish_w, char c) {
	//так как длину слова считали с нуля
	//word_len++;

	//так как слово не переносим, если его длина больше предельной --> ошибка
	if(word_len > limit) {
		return -1;
	}	

	// если пределы позволяют выводим слово в файл 
	// и увеличиваем количество занятых символов в строке на длину слова
	if( count_sym + word_len <= limit ) {
		file_print_word(output, buff, start_w, finish_w); //!!!!!!!!!!!!
		count_sym += word_len;
//		printf("\tcount_sym = %d\n", count_sym);
	}	
	// если больше нет места переходим на след строку
	// и печатаем сивол
	else if (count_sym == limit) { // else next str
		fprintf(output, "\n"); 
		count_sym = 0;
//		printf("\tcount_sym = %d\n", count_sym);
		file_print_word(output, buff, start_w, finish_w);
		count_sym = word_len;
//		printf("\tcount_sym = %d\n", count_sym);
	}	
	//обработали слово освобождаем переменную для нового
	//					word_len = 0;

	//теперь смотрим получится ли вывести текущий символ
	//!!!!!					
	count_sym = if_symbols(output, count_sym, limit, c);
	return count_sym;

}

int if_symbols(FILE * output, int count_sym, int limit, char c) {
	// если пределы позволяют вписываем его
	if( count_sym + 1 <= limit ) {
		fprintf(output,"%c", c); 
		count_sym += 1;
//		printf("\tcount_sym = %d\n", count_sym);
	}	

	//если пределы не позволяют и символ не пробел (пробелы не переносим)
	//то переходим на новую строку и печатаем символ
	else if(count_sym == limit && (c != ' ')) { 
		fprintf(output, "\n"); 
		count_sym = 0;
//		printf("\tcount_sym = %d\n", count_sym);
		fprintf(output, "%c", c);
		count_sym = 1;
//		printf("\tcount_sym = %d\n", count_sym);
	}
	return count_sym;
}

//}

int solve_one (FILE *output, FILE *input) {
	char buff[LEN], c;
	int limit;
	int start_w = 0, finish_w = 0;
	int word_len = 0;
	int count_sym = 0;
	char prev_s = '\0';
	//	int buff_size = 0;
	if (fscanf(input,"%d", &limit) != 1) 
		return ERR;
	while(fgets(buff, LEN, input)) { // пока считывается строка 
		//заполняем массив символов
		for(int j = 0; buff[j] != 0 && buff[j] != '\n'; j++) { 
			c = buff[j]; //для удобства записали в с
//			printf("prev_s = '%c'\t", prev_s);	
//			printf("c = '%c' \n",c);
			
			//если слово первое
			if (prev_s == '\0') {
				fprintf(output,"\t");
				count_sym = 3;
//				printf("\ncount_sym = %d\n", count_sym);
			}
			// если символ буква
			if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
				//идет слово
				word_len++;
				finish_w = j;
				start_w = j - word_len + 1;
//				printf("start_w = %d finish_w = %d\n", start_w, finish_w);
			}

			// иначе если слово закончилось (т е предыдущий символ это буква , а текущий не буква)
			else { 
				if ((prev_s >= 'a' && prev_s <= 'z') || (prev_s >= 'A' && prev_s <= 'Z')) {

					count_sym = if_letter(output, word_len, limit, count_sym, buff, start_w, finish_w, c) ;
					if( count_sym == -1 ) return -1;
					//обработали слово освобождаем переменную для нового
					word_len = 0;
				}

				// если слово закончилось и предыдущий символ не буква
				if ( !((prev_s >= 'a' && prev_s <= 'z') || (prev_s >= 'A' && prev_s <= 'Z')) ) {
					count_sym = if_symbols(output, count_sym, limit, c);
				}
			}
			prev_s = c;
			//		printf("prev_s = '%c'\n", prev_s);	
		}
	}		
	return 1;
}
