/* 
 * Нахождение файлов, присутствующих в одном каталоге и отсутствующих в другом
 *
 * Параметры:
 * output: файл, куда будет напечатана полученная информация;
 * dir1: массив имен файлов первого каталога;
 * dir2: массив имен файлов второго каталога;
 *
 * dir1_name, dir2_name: имя 1-го и 2-го каталогов соответственно;
 * dir2_len, dir2_len: длины соответствующих им массивов.
 *
 * Функция для каждого массива имен поочередно находит элементы, содержащиеся в нем, 
 * но отсутствующие в другом массиве имен и выводит два списка в алфавитном порядке в output.
 *
 * Пример:
 * dir1		dir2
 * a.c		a.c
 * b.c		b.c
 * c.c		c.h
 * in.txt	out.txt
 *
 * В output будет выведено
 * dir1: c.c in.txt
 * dir2: c.h out.txt
 */

void print_sym_difference(FILE *output, 
		char **dir1, char *dir1_name, int dir1_len, 
		char **dir2, char *dir2_name, int dir2_len);
