
class finding_function
{
private:

    double* x;
    double* y;
    int n;

public:

    explicit finding_function(int number)
    {
        n = number;
        x = (double*)malloc(n* sizeof(double));
        y = (double*)malloc(n* sizeof(double));
    }

    ~finding_function()
    {
        delete[] x;
        delete[] y;
    }

    ///////////////////////////////////

    double* getX(const finding_function&) {return x;}
    double* getY(const finding_function&) {return y;}
    int getN(const finding_function&) {return n;} //??

    ///////////////////////////////////

    void setN(int number) {n = number;}
    void setX(const double* array)
    {
        for(int i = 0; i < n; i++)
            x[i] = array[i];
    }
    void setY(const double* array)
    {
        for(int i = 0; i < n; i++)
            y[i] = array[i];
    }

    ///////////////////////////////////

    double lagrange_interpolation(const finding_function&, const double _x)
    {
        double result = 0;
        for (int i = 0; i < n; i++)
        {
            double P = 1;
            for (int j = 0; j < n; j++)
                if (j != i)
                    P *= (_x - x[j]) / (x[i] - x[j]);

            result += P * y[i];
        }
        return result;
    }
};
