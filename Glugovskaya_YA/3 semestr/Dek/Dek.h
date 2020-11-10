#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Dek{
	
	private:
	
		struct Node{
			public:
				T data;
				Node *Next;
				Node *Prev;
		};
		Node *Head;
		Node *Tail;
		int size;
		
		
	public:
		Dek(); //конструктор
		~Dek(); //деструктор
		Dek(T); //конструктор узла 
		void pop_front(); //удаляем первый элемент из head
		void push_head(T data); //пушаем в хеду
		void print(); 
};



		