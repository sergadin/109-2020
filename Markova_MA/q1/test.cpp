#include <iostream>
#include <cstdio>
#include <math.h>
#include <string>
#include "list.h"
using namespace std; 

int main() {
	try {
		/////Test1: (Добавляем 5 элементов = i от 1, затем удаляем 8 элементов)
		List<int> test;
		for(int i = 1; i <= 5; ++i)
			test.push_back(i);
		test.print();
		for(int i = 0; i <= 8; ++i)//тут взяли больше удалений, чем есть в списке!
			test.del_cur();
		test.print();
		cout << "___________________________\n";
		//// Test2: (тестируем оператор присваивания) лист test теперь пустой
		for(int i = 1; i <= 5; ++i)
			test.push_back(i);
		test.print();
		List<int> test2;
		test2 = test;
		test2.print();
		cout << "___________________________\n";
		//////Test3: (тестируем удаление всех элементов)
		test.del_all();
		test.print();
		cout << "___________________________\n";
		////Test4: (Попробуем-ка вывести пустой список)
		List<int> last;
		last.print();
	}
	catch(ListException &err) {
		cout << err.get_error() << endl;
	}
	return 0;
}