#include <iostream>

class finding_function
{
private:

    double* m_x;
    double* m_y;
    int m_n;

public:

    explicit finding_function(int number, double* arrayX, double* arrayY)
    {
        this -> m_n = number;
        this -> m_x = (double*)malloc((this -> m_n)* sizeof(double));
        setX(arrayX);
        this -> m_y = (double*)malloc((this -> m_n)* sizeof(double));
        setY(arrayY);
    }

    ~finding_function()
    {
        delete[] (this -> m_x);
        delete[] (this -> m_y);
    }

    ///////////////////////////////////

    double* getX() {return (this -> m_x);}
    double* getY() {return (this -> m_y);}
    int getN() {return (this -> m_n);}

    ///////////////////////////////////

    void setN(const int number) {this -> m_n = number;}
    void setX(const double* array)
    {
        for(int i = 0; i < (this -> m_n); i++)
            (this -> m_x)[i] = array[i];
    }
    void setY(const double* array)
    {
        for(int i = 0; i < (this -> m_n); i++)
            (this ->  m_y)[i] = array[i];
    }
   
    ///////////////////////////////////

    double lagrange_interpolation(const double _x)
    {
        double result = 0;
        for (int i = 0; i < (this -> m_n); i++)
        {
            double P = 1;
            for (int j = 0; j < (this -> m_n); j++)
                if (j != i)
                    P *= (_x - (this ->m_x)[j]) / ((this ->m_x)[i] - (this -> m_x)[j]);

            result += P * m_y[i];
        }
        return result;
    }

    void sort()
    {
        int size = (this -> m_n);
        double tempX, tempY;
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++)
            {
                if ((this ->m_x)[j] > (this ->m_x)[j + 1])
                {
                    tempX = (this ->m_x)[j];
                    (this ->m_x)[j] = (this ->m_x)[j + 1];
                    (this ->m_x)[j + 1] = tempX;

                    tempY = (this ->m_y)[j];
                    (this ->m_y)[j] = (this ->m_y)[j + 1];
                    (this ->m_y)[j + 1] = tempY;
                }
            }
        }
    }
};


int main()
{
    double x[3][4] = {
      {1, 2, 3, 4},
      {2, 25, 40, 100},
      {-2, -1, 1, 3}
    };

    double y[3][4] = {
      {1, 4, 9, 16}, // 57.76 x^2
      {0.5, 0.04, 0.025, 0.001}, // 0.05 1/x
      {-8, -1, 1, 27} // 8 x^3
    };

    int n = 4, test = 3;
    double point[] = {7.6, 20, 2}; 
    double value;
    for(int i = 0; i < test; i++)
    {
	finding_function data(n, x[i], y[i]);
	value = data.lagrange_interpolation(point[i]);

	std::cout << value << "\n";
    }
    return 0;
}