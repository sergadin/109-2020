#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Deque{
	private:
		class Node{
			public:
			T data_;
				Node *Next_;
				Node *Prev_;
				Node(T data, Node *Next = NULL, Node *Prev = NULL){
					data_  = data;
					Next_ = Next;
					Prev_ = Prev;
				}
		};
		Node *Head_;
		Node *Tail_;
		int size_;
		
		
	public:
		Deque(); //конструктор
		~Deque(); //деструктор
	//	Deque(T); //конструктор узла 
		void pop_front(); //удаляем первый элемент из head
		void pop_back();
		void push_front(T data);
		void push_back(T data);
		void print(); //простите, у меня пока так и не получилось нормально оператор перегрузить
		void front();
		void back();
		
		/*template <typename U> friend std::ostream& operator <<(std::ostream& os,const Deque<U>  & Deck);
		{
				Node* current = Deck.Head_;
				for (int i = 0; i < Deck.size_; i++){
				cout << current -> current.data_ << endl;
				current = current -> Deck.Next_;
	 
};*/
};


class Error
{ 
	private: 
		int code_;
		std::string reason_;
	public:
		Error(int code, const std::string& reason)
		{
			code_ = code;
			reason_ = reason;
		}

		const std::string& get_reason() const 
		{ 
			return reason_; 
		}
};




		