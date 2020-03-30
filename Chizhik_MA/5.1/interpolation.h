typedef double (*dFUNC)(double x);
typedef enum {
	OK,
	NOT_A_FUNCTION,
	OUTSIDE_THE_SEGMENT,
	NOT_ENOUGH_DATA
} Status;

#define EPS 1e-7

class Point {
	private:
		double x, y;
	public:
		Point(double x, double y);
		
		static int compare(const void *a, const void *b);

		double getX();
		double getY();
};

class Interpolation {
	private:
		Point *points;
		double start, end, precision;
		int n;
	public:
		Interpolation(Point *pts, int n, double precision, Status *s);
		~Interpolation();

		double Lagrange(double x, Status *s);
};
