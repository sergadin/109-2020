#include <string>
#define EPS 1e-7

using namespace std;

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
		Interpolation(Point *pts, int n, double precision);
		~Interpolation();

		double Lagrange(double x);
};

class UserException {
	private:
		int code_;
		string message_;
	public:
		UserException(int code, string message);
		string message() const;
		int code() const;
};
