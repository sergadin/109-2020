#include "iostream"
#include "math.h"

using namespace std;

сlass approximation
{
  private:
    int n;
    double *x;
    double *y;
  public:
    approximation (int N, double *A, double *B)
    {
      if (N < 2)
      {
        throw -1;
      }
      n = N;
      x = (double*) malloc (N * sizeof(double));
      y = (double*) malloc (N * sizeof(double));
      if ((x == NULL) || (y == NULL))
      {
        throw -1;
      }
      for (i = 0; i < N; i++)
      {
        x[i] = A[i];
        y[i] = B[i];
      }
    }
    double interpolation (double point)
    {
      int check = 0;
      double k;
      double b;
      for (i = 0; i < (N - 1); i++)
      {
        if (point == x[i])
        {
          answer = y[i];
          check = 1;
        }
        else if ((x[i] < point) && (point < x[i + 1]))
        {
          k = (y[i + 1] - y[i])/([x[i  + 1] - x[i]);
          b = y[i + 1] - k * x[i + 1];
          answer = k * point + b;
          check = 1;
        }
      }
      if (check == 0)
      {
        rhrow -1;
      }
      return answer;
      ~approximation()
      {
        free(x);
        free(y);
      }
    }
};
