#include "task.h"
#include "math.h"

double minimum(RRFUN f, double a, double b, double eps)
{
	int N = 10;
	int i, imin;
	double A, B, C, xmin, min;

	while(fabs(b - a) > eps)
	{
		min = f(a);
		imin = 0;
		//делим отрезок на N частей, ищем узел с минимальным значением
		for(i = 1; i <= N; i++)
		{
			if(f(a + i * (b - a) / N) < min)
			{
				min = f(a + i * (b - a) / N);
				imin = i;
			}
		}

		//выбираем отрезок с минимальным значением
		if(imin == 0)
		{
			a = a;
			b = a + (b - a) / N;
		}
		else if(imin == N)
		{
			b = b;
			a = b - (b - a) / N;
		}
		else
		{
			a = a + (imin - 1) * (b - a) / N;
			b = a + (imin + 1) * (b - a) / N;
		}
	} //делаем это до тех пор, пока не достигнем нужной точности, а после...
	
	//проводим параболу через концы и середину финального отрезка
	A = 4 * ((f(a) + f(b)) / 2 - f((a + b) / 2)) / (a - b) / (a - b);
	B = (4 * (a + b) * f((a + b) / 2) - (a + 3 * b) * f(a) - (3 * a + b) * f(b)) / (a - b) / (a - b);
	C = f(a) - A * a * a - B * a;
	//и ищем её вершину
	xmin = -B / (4 * A);
	if(xmin < a || xmin > b)
	{
		if(f(a) > f(b))
			return f(b);
		else
			return f(a);
	}
	return f(xmin);
}
