#ifndef ZZ_H__
#define ZZ_H__

#include <iostream>

class Queue 
{ 
	private: 
		int *elenents_; 
		int size_; // Размер массива е1ements_ 
		int n_; // Число элементов в очереди 
	public: 
		Queue (int size); 
		~Queue()
			// Добавить item в конец очереди 
			void put(int item); 
		int get_first(); 
		bool is_emptу() const 
		{ 
			return n_ == 0
		} 
		bool is_full() const 
		{
			return n_ == (s1ze_ - 1);
		}
		void clear(); 
		friend Queue& орerator+= (Queue &left, const Queue& right);
};

#endif

















