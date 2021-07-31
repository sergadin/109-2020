#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Deque{
	private:
	
		//template <typename T>
		class Node{
			public:
				Node(T data, Node *Next = NULL, Node *Prev = NULL){
					data_  = data;
					Next_ = Next;
					Prev_ = Prev;
				}
				T data_;
				Node *Next_;
				Node *Prev_;
		};
		Node *Head_;
		Node *Tail_;
		int size_;
		
		
	public:
		Deque(); //конструктор
		~Deque(); //деструктор
	//	Deque(T); //конструктор узла 
		void pop_front(); //удаляем первый элемент из head
		void push_front(T data);
		friend std::ostream& operator<<(std::ostream& os, const Deque<T>& Deck);
	//	void push_head(T data); //пушаем в хеду
	//	void print(); 
};



		