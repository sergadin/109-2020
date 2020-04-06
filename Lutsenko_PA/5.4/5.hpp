class hermit
{
private:
    double *x;
    double *y;
    double *z;
    int N;
public:
    
    hermit(double *a, double *b, double *c,  int n);
    ~hermit();
    double Y(double X);
    
};
