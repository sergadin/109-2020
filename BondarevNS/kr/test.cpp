#include "matrix.h"
#include <iostream>

using namespace std;
int main()
{
matrix A(3, 4);
matrix B(3, 4);
matrix C(3, 4);
for(int i = 1; i<5; ++i)
{
A.set_elem(1, 1, 2);
B.set_elem(2, 1, 1);
}
cout « A;
cout « B;
C = B+A;
cout « C;
cout « A+B+C;
submatrix D(A, 1,2,2,2);
return 0;
}
