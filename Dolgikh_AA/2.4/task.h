typedef double (*RRFUN)(double x);

double littlesegmentintegration(RRFUN f, double a, double b);
double gaussintegration(RRFUN f, double a, double b, int N);
