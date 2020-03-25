typedef double (*RRFUN)(double x);

double newton(RRFUN f, double a, double b, double eps); //функция для поиска корня на отрезке
double deriv(RRFUN f, double a, double h); //функция для вычисления производной
double secderiv(RRFUN f, double a, double h); //функция для вычисления второй производной
