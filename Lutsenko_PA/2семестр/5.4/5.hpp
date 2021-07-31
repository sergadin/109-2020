class hermit
{
private:
    double **Q;
    double *Z;
    int N;
public:
    hermit(double *a, double *b, double *c,  int n);
    double Y(double X);
    ~hermit();
};
