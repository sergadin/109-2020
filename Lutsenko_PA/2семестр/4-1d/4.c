
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "4.h"

void  gauss (int n, double *mas, double *otv)
{         
           
             
             double x[n];
             int i, j, k;
            
            
           
             //Сначала все корни по порядку
             for ( i = 0; i < n + 1; i++ )
               otv[i] = i;
             //Прямой ход метода Гаусса
             for ( k = 0; k < n; k++ )
             { //На какой позиции должен стоять главный элемент
               glavelem( k, n, mas, otv ); //Установка главного элемента
                
               for ( j = n; j >= k; j-- )
                 mas[k*(n+1)+j] /= mas[k*(n+1)+k];
               for ( i = k + 1; i < n; i++ )
                 for ( j = n; j >= k; j-- )
                   mas[i*(n+1)+j] -= mas[k*(n+1)+j] * mas[i*(n+1)+k];
             }
             //Обратный ход
             for ( i = 0; i < n; i++ )
               x[i] = mas[i*(n+1)+n];
             for ( i = n - 2; i >= 0; i-- )
               for ( j = i + 1; j < n; j++ )
                 x[i] -= x[j] * mas[i*(n+1)+j];
             //Вывод результата
             printf( "Ответ:\n" );
             for ( i = 0; i < n; i++ )
               for ( j = 0; j < n; j++ )
                 if ( i == otv[j] )
                 { //Расставляем корни по порядку
                   printf( "%f\n", x[j] );
                   break;
                 }
             
           }


void glavelem( int k,int n, double *mas, double *otv )
{
    
             int i, j, i_max = k, j_max = k;
             double temp;
             //Ищем максимальный по модулю элемент
             for ( i = k; i < n; i++ )
               for ( j = k; j < n; j++ )
                 if ( fabs( mas[i_max*(n+1)+j_max] ) < fabs( mas[i*(n+1)+j] ) )
                 {
                   i_max = i;
                   j_max = j;
                 }
             //Переставляем строки
             for ( j = k; j < n + 1; j++ )
             {
              temp = mas[k*(n+1)+j];
               mas[k*(n+1)+j] = mas[i_max*(n+1)+j];
               mas[i_max*(n+1)+j] = temp;
             }
             //Переставляем столбцы
             for ( i = 0; i < n; i++ )
             {
               temp = mas[i*(n+1)+k];
               mas[i*(n+1)+k] = mas[i*(n+1)+j_max];
               mas[i*(n+1)+j_max] = temp;
             }
             //Учитываем изменение порядка корней
             i = otv[k];
             otv[k] = otv[j_max];
             otv[j_max] = i;

}

