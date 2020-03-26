typedef double(*RRF) (double x);
double interpol(double x[], double y[], int n, double x0, RRF func);
