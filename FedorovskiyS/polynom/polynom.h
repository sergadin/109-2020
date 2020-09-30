
class polynom{
private:
    int pow;
    double *pol;
    double SepDiff(double *x, double *y, double *dydx, int i, int j);
public:
    double hermit_res(double arg, double *x, double *y, double *dydx, int N);
};
