#include <iostream>
#include <string>
//#include <cstdio>

class Matrix
{
        private:
                int m, n; //размеры матрицы
		int * array;
        public:
                Matrix (int m, int n);
                Matrix (const Matrix& v);
                ~Matrix();
//                void function (int i, int j, int m1, int n1);
		void registration (int i, int j, int a);
		int Rows();
		int Columns();
		int GetElement (int i, int j);
                Matrix operator = (const Matrix &other);
                Matrix operator + (const Matrix &other);
                void print () const;

};

class Exception
{
        private:
                int code_;
                std::string message_;
        public:
                Exception(int code, const std::string& message) : code_(code), message_(message){}
                const std::string& message() const { return message_; }
                int code() const { return code_; }
};


class Submatrix
{
	private:
		int m_, n_, i_, j_;
		Matrix *array_;

	public:
		Submatrix (Matrix *array,  int k, int l, int i, int j);
//		~Submatrix();
		int Get_Element (int row, int column);
};
