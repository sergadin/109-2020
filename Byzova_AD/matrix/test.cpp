#include <iostream>
#include <string>
#include "matrix.h"

using namespace std;

int main()
{
	/*
	void create(int n, int m); 
	void get_value(const Matrix &m); 
	int get_element(const Matrix &m, int i, int j); 
	void print(); 
	 */

    try{
		Matrix m1(2,2);
		for(int i = 0; i < m1.getval_n(); i++) {
			for(int j = 0; j < m1.getval_m(); j++) {
				int new_el;
				cout << "введите элемент" << endl;
				cin >> new_el;
				m1.change_element(i, j, new_el);
			}
		}
		cout << "m1 : " << m1 << endl;
		
		Matrix m2(2,2);

		for(int i = 0; i < m2.getval_n(); i++) {
			for(int j = 0; j < m2.getval_m(); j++) {
				int new_el;
				cout << "введите элемент" << endl;
				cin >> new_el;
				m2.change_element(i, j, new_el);
			}
		}
		cout << "m2 : " << m2 << endl;
		
		Matrix m3(2,2);

		//m3 = m1 + m2;
		cout << "m3 : " << m3 << endl;
		cout << "m2+m1" << endl << m1 + m2 << endl;

		//SubM m4(&m1, 1, 1, 2, 2);
		m1.get_submatrix(1, 1, 2, 2); // взятие подматрицы
/*		for (int i = 1 ; i <= 2; i++) {
			for (int j = 1 ; j <= 2; j++) {
				cout << m4.GetElem(i, j) << " ";
			}
			cout << endl;
		}
*/
		return 0;
    }
    
	catch(matrixError &err){
        cout << "Ошибка: " << err.get_reason() << endl;
    }
}
