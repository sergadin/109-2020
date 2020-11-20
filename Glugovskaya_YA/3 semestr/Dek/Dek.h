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
				Node(T data, Node *Next = NULL, Node *Prev = NULL){ //конструктор узла  
					data_  = data;
					Next_ = Next;
					Prev_ = Prev;
				}
		};
		Node *Head_;
		Node *Tail_;
		int size_;
		
		
	public:
	
		class Iterator{
			private:
				const Deque<T>* OurIterDeque_;
				int step_;
				Node *CurrentIt_;
				Iterator(){
					OurIterDeque_ = NULL;
					step_=1;
					CurrentIt_ = NULL;
				}
					
				public:
				friend class Deque;

				void print(){
					cout << "----------Данные об итераторе----------" << endl;
					cout << "OurIterDeque _ " << OurIterDeque_ << endl;
					cout << "CrrentIt_ " << CurrentIt_ << endl;
					cout << "Step_" << step_ << endl;
				}
				void parametrs(int start, int step){
					step_ = step;		
					for (int i = 0; i < start; i++){
						CurrentIt_  = CurrentIt_ -> Next_;
					}
				}
				Iterator& operator=(const Iterator& right){
					CurrentIt_= right.CurrentIt_;
					step_=right.step_;
					return *this;
				} 	
				Iterator& operator+(int n){
					for (int i=0; i < n; i++){
						CurrentIt_ = CurrentIt_  -> Next_;
					}
					return *this;
				}	
				
				Iterator& operator-(int n){
					for (int i=0; i < n; i++){
						CurrentIt_ = CurrentIt_  -> Prev_;
					}
					return *this;
				}
	
				Iterator& operator++(int i){
					CurrentIt_ = CurrentIt_  -> Next_;
					return *this;
				}
	
				Iterator& operator--(int i){
					CurrentIt_ = CurrentIt_  -> Prev_;
					return *this;
				}
	
		};
		Iterator begin(){
			Iterator it;
			it.OurIterDeque_= this;
			it.CurrentIt_ = this -> Head_;
			cout << "--------Вывод итератора-------" << endl;
			cout <<   it.CurrentIt_ << endl;	
			return it;
		}
		Iterator end(){
			Iterator it;
			it.OurIterDeque_= this;
			it.CurrentIt_ = this -> Tail_;
			cout << "--------Вывод итератора-------" << endl;
			cout <<   it.CurrentIt_ << endl;	
			return it;
		}
		
					 
		Deque(); //конструктор
		~Deque(); //деструктор
		void pop_front(); //удаляем первый элемент из head
		void pop_back();
		void push_front(T data);
		void push_back(T data);
		void print(); //простите, у меня пока так и не получилось нормально оператор перегрузить
		void front();
		void back();
		void swap(Deque<T>::Node* First, Deque<T>::Node* Second);
		void copy(Deque<T>::Node* SydaCopy, Deque<T>::Node* OtsydaCopy);
		void sort();
		//Deque<T>& operator=(const Deque<T>& right);
		/*template <typename U> friend std::ostream& operator <<(std::ostream& os,const Deque<U>  & Deck){
			Node* current = Deck.Head_;
			for (int i = 0; i < Deck.size_; i++){
				cout << current -> current.data_ << endl;
				current = current -> Deck.Next_;
			}
		}*/
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




		