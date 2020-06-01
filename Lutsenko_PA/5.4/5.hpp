

class hermit
{
private:
    double *a;
    double *b;
    double *c;
    double *d;
    
    int N;
public:
    
    hermit(double *a1, double *b1, double *c1,double *d1,  int n);
    ~hermit();
    double Y(double X);
    
};
