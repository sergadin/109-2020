typedef int(*RRF)(int x, int y);

int scalar(int *x, int *y, int n, RRF sum, RRF multipl);
