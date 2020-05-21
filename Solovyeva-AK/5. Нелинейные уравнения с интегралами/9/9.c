/** Нелинейные уравнения с интегралами. Задача 9.
**
** Программа решает уравнение, содержащее определенный интеграл, методом деления отрезка пополам. 
** Вычисление интегралла реализовано так, чтобы функция не вычисляла многократно интегралы
**      по одним и тем же отрезкам, использвуется свойство аддитивности определенного интеграла.
** В исходном уравнении содержится подкоренное выражение,обладающее следующим ОДЗ: x in (-1; +infinity);
** Так как интегрирование происходит на отрезке [-x; x], то на х накладывается ограничение: x in (-1, 0) and (0; 1);
** После этого замечания, можно оценить значения alpha, при которых уравнение имеет решение. 
**     При alpha in (3.0894; 9) решение содержится на интервале (0; 1). Выводится решение уравнения. 
**     При alpha in (9; 14.9105) решение содержится на интервале (-1; 0). Выводится решение уравнения. 
**     При всех остальных значениях alpha уравнение решения не имеет, и выводится сообщение об отсутствии корня.
** Значение alpha считывает со стандартного потока ввода. 
** 
*/

#include "libs.h"

double alpha;

// подынтегральныя функция заданного уравнения
double subintegral_f(double x){
    return pow(1 + pow(x, 5), 0.5);
}

// массив посчитанных значений интегралов 
value_integral_buf *integral_buf;

/**
** Оптимизированное вычисление определенного интеграла на отрезке [a, b] с заданной точностью EPS.
**
** Параметры:
**     FUN f: подынтегральная функция;
**     double a: начало отрезка;
**     double b: конец отрезка;
**     double eps: точность вычислений.
**
** Функция вычисляет определенный интеграл на отрезке [a, b], используя уже ранее посчитанные 
** значения интеграла на других отрезках, содержащихся в массиве integral_buf.
** 
** Возвращаемое значение: 
**      функция возвращает значение интеграла.
**
** Метод:
**     Использвуется свойство аддитивности определенного интеграла. 
**     Если отрезок [a, b] вложен в отрезок [c, d], и значени интеграла на отрезке [c, d] уже известно,
**         то значение интеграла на отрезке [a, b] = значение интеграла на [c, d] - на [c, a] - на [b, d].
**     Если отрезок [c, d] вложен в отрезок [a, b], и значени интеграла на отрезке [c, d] уже известно,
**         то значение интеграла на отрезке [a, b] = значение интеграла на [c, d] + на [a, c] + на [d, b].
**     Используя этот принцип вычисляется значение интеграла на отрезке [a, b].
**     Если же вложенных отрезков не найдено, то значение вычисляется с помощью функции integral(FUN f, double a, double b, double eps).
**
*/


double optimized_integral(FUN f, double a, double b, double eps) {
    static int n = 0, size_arr = 0;                                    // n - количество элементов в массиве, size_arr - количество выделенной памяти 
    if(!integral_buf) {
        integral_buf = malloc(10 * sizeof(value_integral_buf));
        integral_buf[1].a = a;
        integral_buf[1].b = b;
        integral_buf[1].value = integral(f, a, b, EPS);
        n++;
        size_arr = 10;
        return integral_buf[1].value;
    } else {
        int optimize_index = -1;                                        //индекс элемента, значение интеграла на котором будет  использоваься в дальнейшем
        double min_difference = b - a, tmp;
        for(int i = 0; i < n; i++) {
            if(a <= integral_buf[i].a && b >= integral_buf[i].b) {      // если отрезок [a, b] содержит отрезок [c, d]
                tmp = b - a - integral_buf[i].b + integral_buf[i].a;    
                if (tmp < min_difference) {
                    min_difference = tmp;
                    optimize_index = i;
                }
            } else if(a >= integral_buf[i].a && b <= integral_buf[i].b) {      // если отрезок [c, d] содержит отрезок [a, b]
                tmp = integral_buf[i].b - integral_buf[i].a - b + a;
                if (tmp < min_difference) {
                    min_difference = tmp;
                    optimize_index = i;
                }
            }
        }
        if (optimize_index == -1) {                                            //если вложенных отрезков не найдено
            if (n >= size_arr) {
                size_arr *= 2;
                integral_buf = realloc(integral_buf, size_arr * sizeof(value_integral_buf));
            }
            n++;
            integral_buf[n-1].a = a;
            integral_buf[n-1].b = b;
            integral_buf[n-1].value = integral(f, a, b, EPS);
            return integral_buf[n-1].value;
        } else {                                                                                                             
            double res = 0;
            if (a <= integral_buf[optimize_index].a && b >= integral_buf[optimize_index].b) {     // если отрезок [c, d] содержит отрезок [a, b]
                if(a != integral_buf[optimize_index].a) {
                    n++;
                    if (n >= size_arr) {
                        size_arr *= 2;
                        integral_buf = realloc(integral_buf, size_arr * sizeof(value_integral_buf));
                    }
                    integral_buf[n-1].a = a;
                    integral_buf[n-1].b = integral_buf[optimize_index].a;
                    integral_buf[n-1].value = integral(f, a, integral_buf[optimize_index].a, EPS);
                    res += integral_buf[n-1].value;
                }
                if(b != integral_buf[optimize_index].b) {
                    n++;
                    if (n >= size_arr) {
                        size_arr *= 2;
                        integral_buf = realloc(integral_buf, size_arr * sizeof(value_integral_buf));
                    }
                    integral_buf[n-1].a = integral_buf[optimize_index].b;
                    integral_buf[n-1].b = b;
                    integral_buf[n-1].value = integral(subintegral_f, integral_buf[optimize_index].b, b, EPS);
                    res += integral_buf[n-1].value;
                }
                res += integral_buf[optimize_index].value;
            } else {                                                            // если отрезок [a, b] содержит отрезок [c, d]
                if(a != integral_buf[optimize_index].a) {
                    n++;
                    if (n >= size_arr) {
                        size_arr *= 2;
                        integral_buf = realloc(integral_buf, size_arr * sizeof(value_integral_buf));
                    }
                    integral_buf[n-1].a = a;
                    integral_buf[n-1].b = integral_buf[optimize_index].a;
                    integral_buf[n-1].value = integral(subintegral_f, integral_buf[optimize_index].a, a, EPS);
                    res -= integral_buf[n-1].value;
                }
                if(b != integral_buf[optimize_index].b) {
                    if (n >= size_arr) {
                        size_arr *= 2;
                        integral_buf = realloc(integral_buf, size_arr * sizeof(value_integral_buf));
                    }
                    integral_buf[n-1].a = integral_buf[optimize_index].b;
                    integral_buf[n-1].b = b;
                    integral_buf[n-1].value = integral(subintegral_f, b, integral_buf[optimize_index].b, EPS);
                    res -= integral_buf[n-1].value;
                }
                res += integral_buf[optimize_index].value;
            }
            return res;
        }
    }
}

// заданная функция
double func(double x) {
    return optimized_integral(subintegral_f, -x, x, EPS) - 3 + alpha/3;
}

int main(void){
    double solution;
    integral_buf = NULL;
	if (!scanf("%lf", &alpha)){
		printf("ERROR::incorrect data entered\n");
		return -1;
	}
	
	if ((alpha < 9) && (alpha > 3.0894)) { 
        solution = root(func,0+EPS, 1-EPS, EPS);
	} else if ((alpha < 14.9105) && (alpha > 9)) {
		solution = root(func,-1+EPS, 0-EPS, EPS);
	} else {
		printf("There are no solutions for a given alpha");
		return 0;
	}
	
    printf("%.9lf\n", solution);
    free(integral_buf);
    return 0;
}
